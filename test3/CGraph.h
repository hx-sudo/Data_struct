#pragma once
#include"global.h"
typedef int Vertices[PICNUM];//������������
typedef bool AdjMatrix[PICNUM][PICNUM];//�ߵ���������

class CGraph
{
protected:
	Vertices m_Vertices;//��������,-1��ʾ��ͼ
	AdjMatrix m_AdjMatrix;//��ϵ�������飬Ԫ����ͬ�����б�Ϊtrue������Ϊ��Ҳ��ʾ�б߷�֮��
	int m_nVernum;//��������
	int m_nArcnum;//�ߵ�����


	void InitGraph();//��ʼ��ͼ�ö���͹�ϵ

public:
	CGraph();
	~CGraph();

	int AddVertex(int info);//��Ӷ��㵽����
	int GetVertex(int nlndex);//�ڶ��������ȡ����Ϊnlndex�Ķ���
	void AddArc(int nV1Index, int nV2Index);//���������Ĺ�ϵ��ӹ�ϵ������
	int GetVexnum();//��ȡ���������еĶ�����
	void UpdataVertex(int nIndex, int info);//���¶���ֵ������������������Ϊnindex�Ķ���ֵ�޸�
	void ClearGrapg();//��ͼ�Ķ���ͱ߻�ԭΪ��ʼ״̬

	bool GetArc(int n1,int n2);//��ȡ��ֵ
};

