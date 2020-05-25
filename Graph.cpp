
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"Graph.h"

#pragma warning(disable:4996) 

using namespace std;






//�����
bool CGraph::InsertVex(Vex sVex)
{
	if (m_nVexNum == 20)
		return false;//��������
	m_aVexs[m_nVexNum++] = sVex;
	return true;
}

//�����
bool CGraph::InsertEdge(Edge sEdge)
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

//�����Ų��Ҷ���
Vex CGraph::GetVex(int v)
{
	return m_aVexs[v];
}


//���Ҷ���������,���鷵�ر�
int CGraph::FindEdge(int v, Edge aEdge[])
{
	int k = 0;//�����ڽӵ���
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_aAdjMatrix[i][v] !=0 )//�ж��շ�Ϊ���ڵ�
		{
			aEdge[k].vex1 = i;
			aEdge[k].vex2 = v;
			aEdge[k].weight = m_aAdjMatrix[i][v];
			k++;

		}
	}
	return k;
}

//���������������ѯ�˵㣬Ѱ�������Ƿ��е��Ƿ񱻷��ʣ�
void CGraph::DSF(int nVex, bool bVisited[], int& nIndex, PathList& pList)
{
	
	bVisited[nVex] = true;//�˵��Ѿ�������
	pList->vexs[nIndex++] = nVex;//���������룬��ȼ�1
	int n = 0;
	for (int i = 0; i < m_nVexNum; i++)
		if (bVisited[i] == true)
			n++;

	if (n == m_nVexNum)//���ж����ѱ����ʣ���һ����һ��
	{
		pList->next =  (PathList)malloc(sizeof(Path));
		if (!(pList->next))
		{
			cout << "�쳣����" << endl;
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
		for (int i = 0; i < m_nVexNum; i++)//����V�������ڽӵ�
		{
			if (m_aAdjMatrix[i][nVex] != 0 && !bVisited[i])//Ѱ�������Ƿ��е��Ƿ񱻷���
			{
				DSF(i, bVisited, nIndex, pList);//�ݹ����DFS
  				bVisited[i] = false;
				nIndex--;//��ȼ�,���ص�·��
			}
		}
	}
}

//����dsf()�õ����
void CGraph::DFSTraverse(int nVex, PathList& pList)
{
	//��ʼ������
	int nIndex = 0;//���
	bool aVisited[MVN] = { false };//����״̬
	DSF(nVex,aVisited,nIndex,pList);//ͨ������Ĳ����㣬������
}


