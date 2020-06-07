
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"Graph.h"

#pragma warning(disable:4996) 

using namespace std;



//对图进行初始化
void CGraph::Init()
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			m_aAdjMatrix[i][j] = 0;
			m_aAdjMatrix[j][i] = 0;
		}
			
	m_nVexNum = 0;
}

//插入点
bool CGraph::InsertVex(Vex sVex)
{
	if (m_nVexNum == 20)
		return false;//顶点已满
	m_aVexs[m_nVexNum++] = sVex;
	return true;
}

//插入边
bool CGraph::InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_nVexNum)
	{
		return false;
	}
	//插入边的信息
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}

//顶点编号查找顶点
Vex CGraph::GetVex(int v)
{
	return m_aVexs[v];
}


//查找顶点相连边,数组返回边
int CGraph::FindEdge(int v, Edge aEdge[])
{
	int k = 0;//返回邻接点数
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_aAdjMatrix[i][v] !=0 )//判断收否为相邻点
		{
			aEdge[k].vex1 = i;
			aEdge[k].vex2 = v;
			aEdge[k].weight = m_aAdjMatrix[i][v];
			k++;

		}
	}
	return k;
}

//深度优先搜索（查询此点，寻找相邻是否有点是否被访问）
void CGraph::DSF(int nVex, bool bVisited[], int& nIndex, PathList& pList)
{
	
	bVisited[nVex] = true;//此点已经访问了
	pList->vexs[nIndex++] = nVex;//将这个点存入，深度加1
	

	if (nIndex == m_nVexNum)//所有顶点已被访问，访一条保一条
	{
		pList->next =  (PathList)malloc(sizeof(Path));
		if (!(pList->next))
		{
			cout << "异常错误" << endl;
			exit(0);
		}
		for (int i = 0; i < m_nVexNum; i++)
		{
			pList->next->vexs[i] = pList->vexs[i];
		}
		pList = pList->next;
		pList->next = NULL;
		
	}
	else
	{
		for (int i = 0; i < m_nVexNum; i++)//搜索V的所有邻接点
		{
			if (m_aAdjMatrix[i][nVex] != 0 && !bVisited[i])//寻找相邻是否有点是否被访问
			{
				DSF(i, bVisited, nIndex, pList);//递归调用DFS
  				bVisited[i] = false;
				nIndex--;//深度减,返回到路口
			}
		}
	}
}

//调用dsf()得到结果
void CGraph::DFSTraverse(int nVex, PathList& pList)
{
	//初始化变量
	int nIndex = 0;//深度
	bool aVisited[MAX] = { false };//访问状态
	DSF(nVex,aVisited,nIndex,pList);//通过传入的参数点，和链表
}


//输入起始，获得最短路径
int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int s[MAX] = { INT_MAX };//保存开始点到所有点的权值和，最短路径
	int p[MAX] = {-1};//保存选出所有终点最短距离的父节点位置
	for (int i = 0; i < m_nVexNum; i++)
	{
		s[i] = INT_MAX;
		p[i] = { -1 };
	}

	bool aVisited[MAX] = { false };//判断是否已加入最短路径
	aVisited[nVexStart] = true;

	int a = nVexStart;//记录路径最短点的新开始点
	int minw = 0;//临时累计路径长度
	for (int j = 0; j < m_nVexNum-1; j++)
	{

		int minm = INT_MAX;//判断同层次中最小值,及下标
		int minnum = nVexStart;
		for (int i = 0; i < m_nVexNum; i++)
		{
			if (m_aAdjMatrix[a][i] != 0 && !aVisited[i] && (m_aAdjMatrix[a][i]+minw) < s[i])
			{
				s[i] = m_aAdjMatrix[a][i]+minw;//起始点到此点的最短路径
				p[i] = a;//保存父点
				if (s[i] < minm)//新指向的点的路径中找最小的值
				{
					minm = s[i];
					minnum = i;//又一新始点
					
				}

			}
		
		}
		for (int m = 0; m < m_nVexNum; m++)//新指向的点的路径中找最小的值与原来的最短路径比较，从而判定新始点从那儿开始
		{
			if (minm > s[m]&&!aVisited[m])
			{
				minm = s[m];
				minnum = m;//又一新始点
			}
		}
		if (minm != INT_MAX)//有找到新始点
			minw = minm;
		a = minnum;
		aVisited[a] = true;
	}
	int i = nVexEnd,n=0;
	while (i!=nVexStart)//从终点依据p[]父节点，一步步找回起始点，逆序保存到边数组中
	{
		aPath[n].vex1 = p[i];
		aPath[n].vex2 = i;
		aPath[n].weight = m_aAdjMatrix[aPath[n].vex1][aPath[n].vex2];
		i = p[i];
		n++;
	}

	return n;
}

//最小生成树，prim算法（从图中找到与树中所有顶点距离最小的点，然后加入树，循环）
int CGraph::FindMinTree(Edge aPath[])
{
	bool aVisited[MAX] = { false };//判断是否已加入到树
	int length = 0;//累计总长度

	int k=0;//当前起始点下标,定义从0点开始
	aVisited[k] = true;

	for (int i = 0; i < m_nVexNum - 1; i++)
	{

		int minweight = INT_MAX;//寻找与所有树点相关边最小的权值
		int m = 0;//暂时记录最小值下标
		for (int j = 0; j < m_nVexNum; j++)
		{
			//j代表树中的的点下标,/////!aVisited图中找，aVsited树中找点
			if (aVisited[j])
			{
				for (int n = 0; n < m_nVexNum; n++)
				{
					//n代表图中的的点下标，从图中找与j点相连的最小边
					if ((!aVisited[n]) && (m_aAdjMatrix[j][n] != 0) && (m_aAdjMatrix[j][n]) < minweight)
					{
						minweight = m_aAdjMatrix[j][n];//取小值
						k = j;//边两点vex1，vex2,（赋值k时，循环几次，浪费时间）
						m = n;
					}
				}
			}
		}//找到树中接下来添加的点了
		aVisited[m] = true;//将找到的点加入树中
		length += minweight;
		aPath[i].vex1 = k;
		aPath[i].vex2 = m;
		aPath[i].weight = minweight;
	}
	return length;
}
