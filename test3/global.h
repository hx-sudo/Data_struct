#pragma once
//防止头文件被重复包含编译

#define BLANK -1

typedef struct tagVertex
{
	int row;//行
	int col;//列
	int info;//信息
}Vertex;//保存游戏地图中一个点的行号，列表，值信息
