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
	void StartGame();//创建开始游戏函数，调用CGameLogic的initmap函数初始化数组，生成图结构
	int GetElement(int nRow, int nCol);//从图获得某行某列的图片编号函数，用于界面显示元素
	void SetFirstPoint(int nRow, int nCol);//设置点击的第一个点函数
	void SetSecPoint(int nRow, int nCol);//er个点函数
	bool Link(Vertex avPath[PICNUM], int& nVexnum);//连接判断函数,成功参数返回路径和顶点
	bool IsWin();//通过判断顶点数组是否全部为-1即空，y清理图结构
	bool Help(Vertex anPath[PICNUM],int &nVexnum);//提示可消除的一对，返回连接路径及顶点数


protected:
	CGraph m_graph;//游戏地图，表示二维数组，对应图片编号，-1则无图
	Vertex m_ptSelFirst;//两次选中图片的坐标
	Vertex m_ptSelSec;





public:
	void ResetGraph();
};

