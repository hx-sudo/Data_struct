
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"Graph.h"

#pragma warning(disable:4996) 

using namespace std;







bool CGraph::InsertVex(Vex sVex)//�����
{
	if (m_nVexNum == 20)
		return false;//��������
	m_aVexs[m_nVexNum++] = sVex;
	return true;
}


bool CGraph::InsertEdge(Edge sEdge)//�����
{
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_nVexNum)
	{
		return false;
	}
	//����ߵ���Ϣ
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}

Vex CGraph::GetVex(int v)//�����Ų��Ҷ���
{
	return m_aVexs[v];
}



int CGraph::FindEdge(int v, Edge aEdge[])//���Ҷ���������,���鷵�ر�
{
	int k = 0;//�����ڽӵ���
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_aAdjMatrix[i][v] !=0 )
		{
			aEdge[k].vex1 = i;
			aEdge[k].vex2 = v;
			aEdge[k].weight = m_aAdjMatrix[i][v];
			k++;

		}
	}
	return k;
}