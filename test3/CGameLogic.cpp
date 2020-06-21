//逻辑层，数值运算

#include "pch.h"
#include "CGameLogic.h"




CGameLogic::CGameLogic()
{
	m_nVexNum=0;//顶点数
}
CGameLogic::~CGameLogic() {

}

//初始化游戏地图
void CGameLogic::InitMap(int anMap[][10]) {
	//初始化地图数组
	int manMap[10][10] = {
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,1,4,5,3,5,3,6,0,-1,
		-1,2,3,6,3,2,2,0,5,-1,
		-1,2,4,5,1,5,2,4,1,-1,
		-1,3,3,4,5,3,3,5,3,-1,
		-1,6,5,6,6,4,2,5,1,-1,
		-1,5,6,3,4,5,6,0,0,-1,
		-1,2,1,1,5,6,4,4,3,-1,
		-1,0,4,6,3,0,4,6,2,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

	};
	for (int i = 0; i < 10; i++)//行
	{
		for (int j = 0; j < 10; j++)//列
		{
			anMap[i][j] = manMap[i][j];
		}
	}
}
//连接判断
bool CGameLogic::IsLink(int anMap[][10], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	AddVertex(v1);//将第一个点加入路径中
	if (anMap[v1.row][v1.col] != anMap[v2.row][v2.col])//两次选中的为同一种
	{
		return false;
	}
	//一条直线连通
	if (v1.row==v2.row)//行号相同
	{
		if (LinkInRow(anMap, v1, v2))//横向连通判断
		{
			AddVertex(v2);
			return true;
		}

	}
	if (v1.col==v2.col)//列号相同
	{
		if (LinkInCol(anMap, v1, v2))//纵向连通判断
		{
			AddVertex(v2);
			return true;
		}
	}

	//两条直线连通
	if (OneCornerLink( anMap,  v1,  v2))
	{
		AddVertex(v2);
		return true;
	}

	//三条直线连通
	if (TwoCornerLink(anMap, v1, v2))
	{
		AddVertex(v2);
		return true;
	}

	DeleteVertex();//对应加点的++
	return false;
}


//消子标记函数，枚举法三种联通方式
void CGameLogic::Clear(int anMap[][10], Vertex v1, Vertex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;

}

//判断横向连通，判断直线上是否都为空白-1
bool CGameLogic::LinkInRow(int anMap[][10], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	if (v1.col>v2.col)//1点小于2点
	{
		 nCol1 = v2.col;
		 nCol2 = v1.col;
	}
	int nRow = v1.row;


	for (int  i = nCol1+1; i <= nCol2; i++)
	{
		if (i==nCol2)//两个点相邻
		{
				return true;
		

				
			
		}
		if (anMap[nRow][i]!=BLANK)//两点间有图
		{
			break;
		}
	}
	return false;
}
//判断纵向连通
bool CGameLogic::LinkInCol(int anMap[][10], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	if (v1.row > v2.row)//1点小于2点
	{
		nRow1 = v2.row;
		nRow2 = v1.row;
	}
	int nCol = v1.col;


	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)//两个点相邻
		{
			
				return true;
			
		}
		if (anMap[i][nCol] != BLANK)//两点间有图
		{
			break;
		}
	}
	return false;

}

//判断一个拐角连通,两条路径判断,拐点为空
bool CGameLogic::OneCornerLink(int anMap[][10], Vertex v1, Vertex v2)
{
	Vertex vex1, vex2;
	Vertex vex;//中间点
	vex1.col = v1.col;
	vex2.col= v2.col;
	vex1.row = v1.row;
	vex2.row = v2.row;
	if (v1.row > v2.row)//1点row小于2点
	{
		vex1.col = v1.col;
		vex2.col = v2.col;
		vex1.row = v1.row;
		vex2.row = v2.row;
	}
	if (vex2.col > vex1.col)//左上对右下
	{
		//先右在下
		vex.row = vex1.row; vex.col = vex2.col;
		if (LineX(anMap, vex1, vex) && LineY(anMap, vex2, vex))
		{
			AddVertex(vex);//加入拐点
			return true;
		}
		//先下在右
		vex.row = vex2.row; vex.col = vex1.col;
		if (LineY(anMap, vex1, vex) && LineX(anMap, vex2, vex))
		{
			AddVertex(vex);
			return true;
		}
	}
	else//左下对右上
	{
		//先左在下
		vex.row = vex1.row; vex.col = vex2.col;
		if (LineX(anMap, vex1, vex) && LineY(anMap, vex2, vex))
		{
			AddVertex(vex);
			return true;
		}
		//先下在左
		vex.row = vex2.row; vex.col = vex1.col;
		if (LineY(anMap, vex1, vex) && LineX(anMap, vex2, vex))
		{
			AddVertex(vex);
			return true;
		}
	}
	return false;
}

//判断两个拐角连通,两个拐点为空-1，6种连线
bool CGameLogic::TwoCornerLink(int anMap[][10], Vertex v1, Vertex v2)
{
	
	//拐点间线平行y轴，拐点列坐标相同
	for (int i = 0; i < 10; i++)//包含边界判断
	{
		if (anMap[v1.row][i]==BLANK&& anMap[v2.row][i]==BLANK)//找到为空的两拐点
		{
			Vertex vexO, vexT;//中间点
			vexO.row = v1.row; vexO.col = i;//同行v1
			vexT.row = v2.row; vexT.col = i;//同行v2
			if (LineX(anMap, v1, vexO)&& LineX(anMap, v2, vexT))//同行拐点与自己连通
			{
				if (LinkInCol(anMap, vexO, vexT))//拐点间通判断
				{
					AddVertex(vexO);
					AddVertex(vexT);
					return true;
				}

			}
		}
	}

	//拐点间线平行x轴，拐点行坐标相同
	for (int i = 0; i < 10; i++)//包含边界判断
	{
		if (anMap[i][v1.col] == BLANK && anMap[i][v2.col] == BLANK)//找到为空的两拐点
		{
			Vertex vexO, vexT;//中间点
			vexO.row = i; vexO.col = v1.col;//同列v1
			vexT.row = i; vexT.col = v2.col;//同列v2
			if (LineY(anMap, v1, vexO) && LineY(anMap, v2, vexT))//同列拐点与自己连通
			{
				if (LinkInRow(anMap, vexO, vexT))//拐点间通判断
				{
					AddVertex(vexO);
					AddVertex(vexT);
					return true;
				}
			}
		}
	}

	return false;
}

//直线连通平行y轴，拐角连通辅助,拐点为空
bool CGameLogic::LineY(int anMap[][10], Vertex v1, Vertex v2)
{

	int nRow1 = v1.row;
	int nRow2 = v2.row;
	if (v1.row > v2.row)//1点小于2点
	{
		nRow1 = v2.row;
		nRow2 = v1.row;
	}
	int nCol = v1.col;


	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)//两个点相邻
		{
			
			if (anMap[v2.row][v2.col] == BLANK)//用于拐角判断是否为相同元素
			{
				return true;
			}
		}
		if (anMap[i][nCol] != BLANK)//两点间有图
		{
			break;
		}
	}
	return false;

}
//x轴，拐点为空
bool CGameLogic::LineX(int anMap[][10], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	if (v1.col > v2.col)//1点小于2点
	{
		nCol1 = v2.col;
		nCol2 = v1.col;
	}
	int nRow = v1.row;


	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2)//两个点相邻
		{
			if (anMap[v2.row][v2.col] == BLANK)//一条线无用，用于拐角判断
			{
				return true;

			}
		}
		if (anMap[nRow][i] != BLANK)//两点间有图
		{
			break;
		}
		
	}
		return false;

}

//参数获取得到路径avPath[8],返回顶点个数
int CGameLogic::GetVexPath(Vertex avPath[8])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;//返回路径顶点个数
}


//添加路径顶点
void CGameLogic::AddVertex(Vertex v)
{
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}

//取出一个顶点
void CGameLogic::DeleteVertex()
{
	m_nVexNum--;
}