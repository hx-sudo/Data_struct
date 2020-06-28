//�߼��㣬��Ϸ�����࣬����Ϸ���߼���ͳһ�������


#include "pch.h"
#include "CGameControl.h"


CGameControl::CGameControl()
{


}
CGameControl::~CGameControl()
{

}
//������ʼ��Ϸ����������CGameLogic��initmap����
void CGameControl::StartGame()
{
	CGameLogic gameLogic;//����ligic����
	gameLogic.InitMap(m_graph);//��ʼ����ά����



	//����CTest::OutPut()���������Բ鿴ͼ�ṹ
	//CTest t;
	//t.OutPut(m_graph);

}

//�������ĳ��ĳ�е�ͼƬ��ź���
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow* NUMELEMENT +nCol);//�Ӷ���������ȡֵ
}

//�������õ�һ���㺯��
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row= nRow;
	m_ptSelFirst.col = nCol;
}
//�������õڶ����㺯��
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col= nCol;
}

//�����жϺ���������logic�к�����ʵ���ж����Ӻ����ӣ���������·���Ͷ���������ʾ��
bool CGameControl::Link(Vertex avPath[PICNUM],int &nVexnum)
{
	//ѡ���������Ϊͬһ����
	if (m_ptSelFirst.row== m_ptSelSec.row&& m_ptSelFirst.col== m_ptSelSec.col)
	{
		return false;
	}
	
	//���ӵ�������ֵ��ͬ
	if (m_graph.GetVertex(m_ptSelFirst.row* NUMELEMENT + m_ptSelFirst.col)!= m_graph.GetVertex(m_ptSelSec.row * NUMELEMENT + m_ptSelSec.col)
		|| m_graph.GetVertex(m_ptSelSec.row * NUMELEMENT + m_ptSelSec.col) ==BLANK
		|| m_graph.GetVertex(m_ptSelFirst.row * NUMELEMENT + m_ptSelFirst.col)==BLANK)
	{
		return false;
	}
	CGameLogic gameLogic;
	//����logic�����ж��Ƿ������ͨ
	if (gameLogic.IsLink(m_graph,m_ptSelFirst,m_ptSelSec))
	{
		//����logic�ĺ�������¼��ͨ·���Ͷ���
		nVexnum = gameLogic.GetVexPath(avPath);//�����жϣ�������ѹջ�󷵻�
		//���ӱ�ǣ�����
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);
	}
	else
	{
		return false;
	}

	return true;
}


//ͨ���ж϶��������Ƿ�ȫ��Ϊ-1���գ�y����ͼ�ṹ�������߼��㺯��
bool CGameControl::IsWin()
{
	CGameLogic clg;
	if (clg.IsBlank(m_graph)==true)
	{
		m_graph.ClearGrapg();//����ͼ�ṹ
		return true;
	}
	return false;
}

//��ʾ��������һ�ԣ���������·����������,�����߼�����ʾ����
bool CGameControl::Help(Vertex anPath[PICNUM], int& nVexnum)
{
	CGameLogic clg;
	if (clg.IsBlank(m_graph))//�ж�ͼ���������Ƿ�Ϊ��
	{
		return false;
	}
	//����һ����Ч��ʾ·��
	if (clg.SerachVaildPath(m_graph))
	{
		nVexnum=clg.GetVexPath(anPath);//��ȡ����·����������
		return true;
	}
	return false;
}

//���ŵ�ͼ��������m_graph��������
void CGameControl::ResetGraph()
{
	
}
