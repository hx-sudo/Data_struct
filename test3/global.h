#pragma once
//防止头文件被重复包含编译

#define BLANK -1
#define SIZEELEMENT 40//单个水果图片大小
#define GAMETOP 100 //游戏地图起点到边框距离xy
#define PLAY_TIMER_ID 1//计数器编号
#define NUMELEMENT 6//游戏地图行，列游戏小块数量（可以通过修改它而修改游戏地图大小，为简化正方形）
#define PICNUM NUMELEMENT*NUMELEMENT//总的图片数
#define PNUM 4//图片花色数（正方形，比实际少2）(多余的为游戏图-1边框)
#define PENUM 4//每种花色的图片数


typedef struct tagVertex
{
	int row;//行
	int col;//列
	int info;//信息
}Vertex;//保存游戏地图中一个点的行号，列表，值信息
