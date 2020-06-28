#pragma once
#include"global.h"
#include "CGameLogic.h"
#include"CGraph.h"
#include "CTest.h"


class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	void StartGame();//������ʼ��Ϸ����������CGameLogic��initmap������ʼ�����飬����ͼ�ṹ
	int GetElement(int nRow, int nCol);//��ͼ���ĳ��ĳ�е�ͼƬ��ź��������ڽ�����ʾԪ��
	void SetFirstPoint(int nRow, int nCol);//���õ���ĵ�һ���㺯��
	void SetSecPoint(int nRow, int nCol);//er���㺯��
	bool Link(Vertex avPath[PICNUM], int& nVexnum);//�����жϺ���,�ɹ���������·���Ͷ���
	bool IsWin();//ͨ���ж϶��������Ƿ�ȫ��Ϊ-1���գ�y����ͼ�ṹ
	bool Help(Vertex anPath[PICNUM],int &nVexnum);//��ʾ��������һ�ԣ���������·����������


protected:
	CGraph m_graph;//��Ϸ��ͼ����ʾ��ά���飬��ӦͼƬ��ţ�-1����ͼ
	Vertex m_ptSelFirst;//����ѡ��ͼƬ������
	Vertex m_ptSelSec;





public:
	void ResetGraph();
};

