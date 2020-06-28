#include "pch.h"
#include "CGraph.h"


CGraph::CGraph()
{
	InitGraph();//图初始化
	 m_nVernum=0;//定点数量
	 m_nArcnum=0;//边得数量
}
CGraph::~CGraph(){}

void CGraph::InitGraph()//初始化图得顶点和关系
{
	m_nVernum = 0;//定点数量
	m_nArcnum = 0;//边得数量
	for (int i = 0; i < PICNUM; i++)//矩形-1为边框,false二维数组表示边框
	{
		m_Vertices[i] = -1;//初始化顶点数组
		for (int  j= 0; j < PICNUM; j++)
		{

			m_AdjMatrix[i][j] = false;//初始化边数组
		}
	}
}

//添加顶点到数组
int CGraph::AddVertex(int info)
{
	if (m_nVernum >= PICNUM)//图片数组满了
	{
		return m_nVernum;
	}
	m_Vertices[m_nVernum] = info;
	m_nVernum++;

	return m_nVernum;//返回顶点数
}


//获取索引为nlndex的顶点
int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

//将两个点间的关系添加关系数组中
void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;//有关系则为true
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

//获取顶点数组中的顶点数
int CGraph::GetVexnum()
{
	return m_nVernum;
}


//将顶点数组索引号为nindex的顶点值修改
void CGraph::UpdataVertex(int nIndex, int info)
{
	m_Vertices[nIndex] = info;
}

//获取边值
bool CGraph::GetArc(int n1,int n2)
{
	// TODO: 在此处添加实现代码.
	return m_AdjMatrix[n1][n2];
}

//将图的顶点和边还原为初始状态
void CGraph::ClearGrapg()
{
	InitGraph();
}
