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
	gameLogic.InitMap(m_graph);//初始化二维数组



	//调用CTest::OutPut()函数，测试查看图结构
	//CTest t;
	//t.OutPut(m_graph);

}

//创建获得某行某列的图片编号函数
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow* NUMELEMENT +nCol);//从顶点数组中取值
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

//连接判断函数，调用logic中函数，实现判断链接和消子，参数返回路径和顶点数到表示层
bool CGameControl::Link(Vertex avPath[PICNUM],int &nVexnum)
{
	//选择的两个点为同一个点
	if (m_ptSelFirst.row== m_ptSelSec.row&& m_ptSelFirst.col== m_ptSelSec.col)
	{
		return false;
	}
	
	//链接的两个点值不同
	if (m_graph.GetVertex(m_ptSelFirst.row* NUMELEMENT + m_ptSelFirst.col)!= m_graph.GetVertex(m_ptSelSec.row * NUMELEMENT + m_ptSelSec.col)
		|| m_graph.GetVertex(m_ptSelSec.row * NUMELEMENT + m_ptSelSec.col) ==BLANK
		|| m_graph.GetVertex(m_ptSelFirst.row * NUMELEMENT + m_ptSelFirst.col)==BLANK)
	{
		return false;
	}
	CGameLogic gameLogic;
	//调用logic函数判断是否可以连通
	if (gameLogic.IsLink(m_graph,m_ptSelFirst,m_ptSelSec))
	{
		//调用logic的函数，记录连通路径和顶点
		nVexnum = gameLogic.GetVexPath(avPath);//连接判断，将顶点压栈后返回
		//消子标记，更新
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);
	}
	else
	{
		return false;
	}

	return true;
}


//通过判断顶点数组是否全部为-1即空，y清理图结构，调用逻辑层函数
bool CGameControl::IsWin()
{
	CGameLogic clg;
	if (clg.IsBlank(m_graph)==true)
	{
		m_graph.ClearGrapg();//清理图结构
		return true;
	}
	return false;
}

//提示可消除的一对，返回连接路径及顶点数,调用逻辑层提示方法
bool CGameControl::Help(Vertex anPath[PICNUM], int& nVexnum)
{
	CGameLogic clg;
	if (clg.IsBlank(m_graph))//判断图顶点数组是否为空
	{
		return false;
	}
	//查找一条有效提示路径
	if (clg.SerachVaildPath(m_graph))
	{
		nVexnum=clg.GetVexPath(anPath);//获取连接路径及顶点数
		return true;
	}
	return false;
}

//重排地图函数，对m_graph数据重排
void CGameControl::ResetGraph()
{
	
}
