#pragma once

#include "global.h"
#include"CGraph.h"

class CGameLogic
{

public:
	CGameLogic();
	~CGameLogic();

public:
	void InitMap(CGraph &g);//初始化游戏地图,通过图来存储游戏地图信息
	bool IsLink(CGraph& g, Vertex v1, Vertex v2);//连接判断
	void Clear(CGraph& g, Vertex v1, Vertex v2);//消子标记函数，拐角超过两个不能消除,两个点更新为空，并更新两个顶点与图中其余顶点的边
	int GetVexPath(Vertex avPath[PICNUM]);//参数获取得到路径点,返回顶点个数,向控制层传递
	void PushVertex(int v);//将路径顶点送入路径顶点数组
	void PopVetex();//送出数组
	bool SearchPath(CGraph& g, int nV0, int nV1);//采用深度优先搜索，判断两顶点是否连通
	bool IsExsit(int nVi);//判断nVi顶点是否保存到连通数组m_anPath中
	bool IsCornor();//判断拐点
	bool IsBlank(CGraph& g);//判断图得顶点是否为空
	bool SerachVaildPath(CGraph& g);//提示算法


protected:
	Vertex m_avPath[PICNUM];//保存进行连接时经过的起始，拐点，终点顶点，
	int m_anPath[PICNUM];//保存连通路径的所有顶点索引
	int m_nVexNum;//链接路径所有顶点数
	int m_num;//拐点数（不超过2）

	void UpdateArc(CGraph& g, int nRow, int nCol);//判断此点上下左右是否有边，有则更新图并返回


	


public:
	void ResetGraph(CGraph& g);
};

