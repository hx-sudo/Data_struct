#pragma once

#include "global.h"

class CGameLogic
{

public:
	CGameLogic();
	~CGameLogic();

public:
	void InitMap(int anMap[][10]);//��ʼ����Ϸ��ͼ
	bool IsLink(int anMap[][10], Vertex v1, Vertex v2);//�����ж�
	void Clear(int anMap[][10], Vertex v1, Vertex v2);//���Ӻ���
	int GetVexPath(Vertex avPath[8]);//������ȡ�õ�·����,���ض������
	
	
protected:
	Vertex m_avPath[4];//�����������ʱ�����ĵ㣬��������ͨ·����ĸ��㣩
	int m_nVexNum;//���Ӷ�����


	void AddVertex(Vertex v);//���·������
	void DeleteVertex();//ȡ��һ������

	bool LinkInRow(int anMap[][10], Vertex v1, Vertex v2);//�жϺ�����ͨ
	bool LinkInCol(int anMap[][10], Vertex v1, Vertex v2);//�ж�������ͨ
	bool OneCornerLink(int anMap[][10], Vertex v1, Vertex v2);//�ж�һ���ս���ͨ
	bool TwoCornerLink(int anMap[][10], Vertex v1, Vertex v2);//�ж������ս���ͨ
	bool LineY(int anMap[][10], Vertex v1, Vertex v2);//ֱ����ͨy�ᣬ�ս���ͨ����
	bool LineX(int anMap[][10], Vertex v1, Vertex v2);

};

