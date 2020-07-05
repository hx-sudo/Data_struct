#pragma once
#include"global.h"
typedef int Vertices[PICNUM];//顶点数据类型
typedef bool AdjMatrix[PICNUM][PICNUM];//边得数据类型

class CGraph
{
protected:
	Vertices m_Vertices;//顶点数组,-1表示无图
	AdjMatrix m_AdjMatrix;//关系矩阵数组，元素相同相邻有边为true，相邻为空也表示有边反之，
	int m_nVernum;//定点数量
	int m_nArcnum;//边得数量


	void InitGraph();//初始化图得顶点和关系

public:
	CGraph();
	~CGraph();

	int AddVertex(int info);//添加顶点到数组
	int GetVertex(int nlndex);//在顶点数组获取索引为nlndex的顶点
	void AddArc(int nV1Index, int nV2Index);//将两个点间的关系添加关系数组中
	int GetVexnum();//获取顶点数组中的顶点数
	void UpdataVertex(int nIndex, int info);//更新顶点值，将顶点数组索引号为nindex的顶点值修改
	void ClearGrapg();//将图的顶点和边还原为初始状态

	bool GetArc(int n1,int n2);//获取边值
};

