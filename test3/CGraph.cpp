#include "pch.h"
#include "CGraph.h"


CGraph::CGraph()
{
	InitGraph();//ͼ��ʼ��
	 m_nVernum=0;//��������
	 m_nArcnum=0;//�ߵ�����
}
CGraph::~CGraph(){}

void CGraph::InitGraph()//��ʼ��ͼ�ö���͹�ϵ
{
	m_nVernum = 0;//��������
	m_nArcnum = 0;//�ߵ�����
	for (int i = 0; i < PICNUM; i++)//����-1Ϊ�߿�,false��ά�����ʾ�߿�
	{
		m_Vertices[i] = -1;//��ʼ����������
		for (int  j= 0; j < PICNUM; j++)
		{

			m_AdjMatrix[i][j] = false;//��ʼ��������
		}
	}
}

//��Ӷ��㵽����
int CGraph::AddVertex(int info)
{
	if (m_nVernum >= PICNUM)//ͼƬ��������
	{
		return m_nVernum;
	}
	m_Vertices[m_nVernum] = info;
	m_nVernum++;

	return m_nVernum;//���ض�����
}


//��ȡ����Ϊnlndex�Ķ���
int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

//���������Ĺ�ϵ��ӹ�ϵ������
void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;//�й�ϵ��Ϊtrue
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

//��ȡ���������еĶ�����
int CGraph::GetVexnum()
{
	return m_nVernum;
}


//����������������Ϊnindex�Ķ���ֵ�޸�
void CGraph::UpdataVertex(int nIndex, int info)
{
	m_Vertices[nIndex] = info;
}

//��ȡ��ֵ
bool CGraph::GetArc(int n1,int n2)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	return m_AdjMatrix[n1][n2];
}

//��ͼ�Ķ���ͱ߻�ԭΪ��ʼ״̬
void CGraph::ClearGrapg()
{
	InitGraph();
}
