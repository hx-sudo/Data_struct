//逻辑层，游戏控制类，对游戏各逻辑类统一管理调度


#include "pch.h"
#include "CGameControl.h"


CGameControl::CGameControl()
{


}
CGameControl::~CGameControl()
{

}
//创建开始游戏函数，调用CGameLogic的initmap函数
void CGameControl::StartGame()
{
	CGameLogic gameLogic;//创建ligic对象
	gameLogic.InitMap(m_anMap);//初始化二维数组
}

//创建获得某行某列的图片编号函数
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_anMap[nRow][nCol];
}

//创建设置第一个点函数
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row= nRow;
	m_ptSelFirst.col = nCol;
}
//创建设置第二个点函数
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col= nCol;
}

//连接判断函数，调用logic中函数，实现判断链接和消子，参数返回路径和顶点数
bool CGameControl::Link(Vertex avPath[8],int &nVexnum)
{
	//选择的两个点为同一个点
	if (m_ptSelFirst.row== m_ptSelSec.row&& m_ptSelFirst.col== m_ptSelSec.col)
	{
		return false;
	}

	//链接的两个点值不同
	if (m_anMap[m_ptSelFirst.row][m_ptSelFirst.col]!=m_anMap[m_ptSelSec.row][m_ptSelSec.col])
	{
		return false;
	}
	CGameLogic gameLogic;
	//调用logic函数判断是否可以连通
	if (gameLogic.IsLink(m_anMap,m_ptSelFirst,m_ptSelSec))
	{
		//调用logic的函数，记录连通路径和顶点
		nVexnum = gameLogic.GetVexPath(avPath);
		//消子标记
		gameLogic.Clear(m_anMap, m_ptSelFirst, m_ptSelSec);
	}
	else
	{
		return false;
	}

	return true;
}
