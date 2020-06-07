
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"Graph.h"

#pragma warning(disable:4996) 

using namespace std;



//��ͼ���г�ʼ��
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
	

	if (nIndex == m_nVexNum)//���ж����ѱ����ʣ���һ����һ��
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
	bool aVisited[MAX] = { false };//����״̬
	DSF(nVex,aVisited,nIndex,pList);//ͨ������Ĳ����㣬������
}


//������ʼ��������·��
int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int s[MAX] = { INT_MAX };//���濪ʼ�㵽���е��Ȩֵ�ͣ����·��
	int p[MAX] = {-1};//����ѡ�������յ���̾���ĸ��ڵ�λ��
	for (int i = 0; i < m_nVexNum; i++)
	{
		s[i] = INT_MAX;
		p[i] = { -1 };
	}

	bool aVisited[MAX] = { false };//�ж��Ƿ��Ѽ������·��
	aVisited[nVexStart] = true;

	int a = nVexStart;//��¼·����̵���¿�ʼ��
	int minw = 0;//��ʱ�ۼ�·������
	for (int j = 0; j < m_nVexNum-1; j++)
	{

		int minm = INT_MAX;//�ж�ͬ�������Сֵ,���±�
		int minnum = nVexStart;
		for (int i = 0; i < m_nVexNum; i++)
		{
			if (m_aAdjMatrix[a][i] != 0 && !aVisited[i] && (m_aAdjMatrix[a][i]+minw) < s[i])
			{
				s[i] = m_aAdjMatrix[a][i]+minw;//��ʼ�㵽�˵�����·��
				p[i] = a;//���游��
				if (s[i] < minm)//��ָ��ĵ��·��������С��ֵ
				{
					minm = s[i];
					minnum = i;//��һ��ʼ��
					
				}

			}
		
		}
		for (int m = 0; m < m_nVexNum; m++)//��ָ��ĵ��·��������С��ֵ��ԭ�������·���Ƚϣ��Ӷ��ж���ʼ����Ƕ���ʼ
		{
			if (minm > s[m]&&!aVisited[m])
			{
				minm = s[m];
				minnum = m;//��һ��ʼ��
			}
		}
		if (minm != INT_MAX)//���ҵ���ʼ��
			minw = minm;
		a = minnum;
		aVisited[a] = true;
	}
	int i = nVexEnd,n=0;
	while (i!=nVexStart)//���յ�����p[]���ڵ㣬һ�����һ���ʼ�㣬���򱣴浽��������
	{
		aPath[n].vex1 = p[i];
		aPath[n].vex2 = i;
		aPath[n].weight = m_aAdjMatrix[aPath[n].vex1][aPath[n].vex2];
		i = p[i];
		n++;
	}

	return n;
}

//��С��������prim�㷨����ͼ���ҵ����������ж��������С�ĵ㣬Ȼ���������ѭ����
int CGraph::FindMinTree(Edge aPath[])
{
	bool aVisited[MAX] = { false };//�ж��Ƿ��Ѽ��뵽��
	int length = 0;//�ۼ��ܳ���

	int k=0;//��ǰ��ʼ���±�,�����0�㿪ʼ
	aVisited[k] = true;

	for (int i = 0; i < m_nVexNum - 1; i++)
	{

		int minweight = INT_MAX;//Ѱ��������������ر���С��Ȩֵ
		int m = 0;//��ʱ��¼��Сֵ�±�
		for (int j = 0; j < m_nVexNum; j++)
		{
			//j�������еĵĵ��±�,/////!aVisitedͼ���ң�aVsited�����ҵ�
			if (aVisited[j])
			{
				for (int n = 0; n < m_nVexNum; n++)
				{
					//n����ͼ�еĵĵ��±꣬��ͼ������j����������С��
					if ((!aVisited[n]) && (m_aAdjMatrix[j][n] != 0) && (m_aAdjMatrix[j][n]) < minweight)
					{
						minweight = m_aAdjMatrix[j][n];//ȡСֵ
						k = j;//������vex1��vex2,����ֵkʱ��ѭ�����Σ��˷�ʱ�䣩
						m = n;
					}
				}
			}
		}//�ҵ����н�������ӵĵ���
		aVisited[m] = true;//���ҵ��ĵ��������
		length += minweight;
		aPath[i].vex1 = k;
		aPath[i].vex2 = m;
		aPath[i].weight = minweight;
	}
	return length;
}
