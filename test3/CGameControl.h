#pragma once
#include"global.h"
#include "CGameLogic.h"


class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	void StartGame();//创建开始游戏函数，调用CGameLogic的initmap函数初始化数组
	int GetElement(int nRow, int nCol);//创建获得某行某列的图片编号函数
	void SetFirstPoint(int nRow, int nCol);//创建设置第一个点函数
	void SetSecPoint(int nRow, int nCol);//创建设置第er个点函数
	bool Link(Vertex avPath[8], int& nVexnum);//连接判断函数,成功参数返回路径和顶点




protected:
	int m_anMap[10][10];//以坐标表示二维数组，对应图片，-1则无图
	Vertex m_ptSelFirst;//两次选中图片的坐标
	Vertex m_ptSelSec;





};

