#pragma once

#include "global.h"

class CGameLogic
{

public:
	CGameLogic();
	~CGameLogic();

public:
	void InitMap(int anMap[][10]);//初始化游戏地图
	bool IsLink(int anMap[][10], Vertex v1, Vertex v2);//连接判断
	void Clear(int anMap[][10], Vertex v1, Vertex v2);//消子函数
	int GetVexPath(Vertex avPath[8]);//参数获取得到路径点,返回顶点个数
	
	
protected:
	Vertex m_avPath[4];//保存进行连接时经过的点，（三条的通路最多四个点）
	int m_nVexNum;//链接顶点数


	void AddVertex(Vertex v);//添加路径顶点
	void DeleteVertex();//取出一个顶点

	bool LinkInRow(int anMap[][10], Vertex v1, Vertex v2);//判断横向连通
	bool LinkInCol(int anMap[][10], Vertex v1, Vertex v2);//判断纵向连通
	bool OneCornerLink(int anMap[][10], Vertex v1, Vertex v2);//判断一个拐角连通
	bool TwoCornerLink(int anMap[][10], Vertex v1, Vertex v2);//判断两个拐角连通
	bool LineY(int anMap[][10], Vertex v1, Vertex v2);//直线连通y轴，拐角连通辅助
	bool LineX(int anMap[][10], Vertex v1, Vertex v2);

};

