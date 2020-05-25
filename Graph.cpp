
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"Graph.h"

#pragma warning(disable:4996) 

using namespace std;






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
	int n = 0;
	for (int i = 0; i < m_nVexNum; i++)
		if (bVisited[i] == true)
			n++;

	if (n == m_nVexNum)//所有顶点已被访问，访一条保一条
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
	bool aVisited[MVN] = { false };//访问状态
	DSF(nVex,aVisited,nIndex,pList);//通过传入的参数点，和链表
}


