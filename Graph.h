#pragma once
#ifndef GRAPG_H
#define GRAPG_H




typedef struct {//顶点
	int num;//景点编号
	char name[20];//经典名字
	char desc[1024];//景点介绍
} Vex;

typedef struct {//边
	int vex1;//边点一
	int vex2;//二
	int weight;//权值
}Edge;

class CGraph
{
public:
	bool InsertVex(Vex sVex);//插入点
	bool InsertEdge(Edge sEdge);//插入边
	Vex GetVex(int v);//查找顶点
	int FindEdge(int v, Edge aEdge[]);//查找顶点相连边
public:
	int m_aAdjMatrix[20][20];//邻接矩阵
	Vex m_aVexs[20];//顶点信息数组
	int m_nVexNum;//图的顶点个数
};





#endif // !GRAPG_H

