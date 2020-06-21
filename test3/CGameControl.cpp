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
	gameLogic.InitMap(m_anMap);//��ʼ����ά����
}

//�������ĳ��ĳ�е�ͼƬ��ź���
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_anMap[nRow][nCol];
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

//�����жϺ���������logic�к�����ʵ���ж����Ӻ����ӣ���������·���Ͷ�����
bool CGameControl::Link(Vertex avPath[8],int &nVexnum)
{
	//ѡ���������Ϊͬһ����
	if (m_ptSelFirst.row== m_ptSelSec.row&& m_ptSelFirst.col== m_ptSelSec.col)
	{
		return false;
	}

	//���ӵ�������ֵ��ͬ
	if (m_anMap[m_ptSelFirst.row][m_ptSelFirst.col]!=m_anMap[m_ptSelSec.row][m_ptSelSec.col])
	{
		return false;
	}
	CGameLogic gameLogic;
	//����logic�����ж��Ƿ������ͨ
	if (gameLogic.IsLink(m_anMap,m_ptSelFirst,m_ptSelSec))
	{
		//����logic�ĺ�������¼��ͨ·���Ͷ���
		nVexnum = gameLogic.GetVexPath(avPath);
		//���ӱ��
		gameLogic.Clear(m_anMap, m_ptSelFirst, m_ptSelSec);
	}
	else
	{
		return false;
	}

	return true;
}
