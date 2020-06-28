#pragma once

#include "global.h"
#include"CGraph.h"

class CGameLogic
{

public:
	CGameLogic();
	~CGameLogic();

public:
	void InitMap(CGraph &g);//��ʼ����Ϸ��ͼ,ͨ��ͼ���洢��Ϸ��ͼ��Ϣ
	bool IsLink(CGraph& g, Vertex v1, Vertex v2);//�����ж�
	void Clear(CGraph& g, Vertex v1, Vertex v2);//���ӱ�Ǻ������սǳ���������������,���������Ϊ�գ�����������������ͼ�����ඥ��ı�
	int GetVexPath(Vertex avPath[PICNUM]);//������ȡ�õ�·����,���ض������,����Ʋ㴫��
	void PushVertex(int v);//��·����������·����������
	void PopVetex();//�ͳ�����
	bool SearchPath(CGraph& g, int nV0, int nV1);//������������������ж��������Ƿ���ͨ
	bool IsExsit(int nVi);//�ж�nVi�����Ƿ񱣴浽��ͨ����m_anPath��
	bool IsCornor();//�жϹյ�
	bool IsBlank(CGraph& g);//�ж�ͼ�ö����Ƿ�Ϊ��
	bool SerachVaildPath(CGraph& g);//��ʾ�㷨


protected:
	Vertex m_avPath[PICNUM];//�����������ʱ��������ʼ���յ㣬�յ㶥�㣬
	int m_anPath[PICNUM];//������ͨ·�������ж�������
	int m_nVexNum;//����·�����ж�����
	int m_num;//�յ�����������2��

	void UpdateArc(CGraph& g, int nRow, int nCol);//�жϴ˵����������Ƿ��бߣ��������ͼ������


	


public:
	void ResetGraph(CGraph& g);
};

