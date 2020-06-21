#pragma once
#include"global.h"
#include "CGameLogic.h"


class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	void StartGame();//������ʼ��Ϸ����������CGameLogic��initmap������ʼ������
	int GetElement(int nRow, int nCol);//�������ĳ��ĳ�е�ͼƬ��ź���
	void SetFirstPoint(int nRow, int nCol);//�������õ�һ���㺯��
	void SetSecPoint(int nRow, int nCol);//�������õ�er���㺯��
	bool Link(Vertex avPath[8], int& nVexnum);//�����жϺ���,�ɹ���������·���Ͷ���




protected:
	int m_anMap[10][10];//�������ʾ��ά���飬��ӦͼƬ��-1����ͼ
	Vertex m_ptSelFirst;//����ѡ��ͼƬ������
	Vertex m_ptSelSec;





};

