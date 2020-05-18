#pragma once
#ifndef GRAPG_H
#define GRAPG_H




typedef struct {//����
	int num;//������
	char name[20];//��������
	char desc[1024];//�������
} Vex;

typedef struct {//��
	int vex1;//�ߵ�һ
	int vex2;//��
	int weight;//Ȩֵ
}Edge;

class CGraph
{
public:
	bool InsertVex(Vex sVex);//�����
	bool InsertEdge(Edge sEdge);//�����
	Vex GetVex(int v);//���Ҷ���
	int FindEdge(int v, Edge aEdge[]);//���Ҷ���������
public:
	int m_aAdjMatrix[20][20];//�ڽӾ���
	Vex m_aVexs[20];//������Ϣ����
	int m_nVexNum;//ͼ�Ķ������
};





#endif // !GRAPG_H

