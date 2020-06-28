//逻辑层，数值运算

#include "pch.h"
#include "CGameLogic.h"




CGameLogic::CGameLogic()
{
	m_nVexNum=0;//连通顶点数
	m_num = 0;//拐点数
}
CGameLogic::~CGameLogic() {

}

//初始化游戏地图
void CGameLogic::InitMap(CGraph& g) {//-1为边框,false二维数组表示边框
	//初始化地图数组
	int manMap[NUMELEMENT][NUMELEMENT];
		/*= {
		
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
		
		2,0,1,3,
		2,2,1,3,
		2,1,0,0,
		1,3,0,3,
	};*/
	int anTemp[PNUM* PENUM];//保存生成的随机顶点数组
	for (int i = 0; i < PNUM; i++)//花色数
	{
		for (int j = 0; j < PENUM; j++)//重复数
		{
			anTemp[i * PNUM + j] = i;
		}

	}
	srand((int)time(NULL));//设置随机数种子
	for (int i = 0; i < 100; i++)//随机交换两个数字100次
	{
		//随机得到两个坐标
		int nIndex1 = rand() %(PNUM * PENUM);
		int nIndex2= rand() %(PNUM * PENUM);

		//交换两个数值
		int nTmp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTmp;

	}
	for (int i = 0; i < NUMELEMENT; i++)//此二重循环为构造数组-1边界
	{
		for (int j = 0; j < NUMELEMENT; j++)
		{
			if (i==0||i== NUMELEMENT-1||j==0||j== NUMELEMENT-1)
			{
				manMap[i][j] = BLANK;
			}
			else
			{
				manMap[i][j] = anTemp[(i  * NUMELEMENT + j)-(NUMELEMENT+2*i-1)];

			}
		}
	}

	for (int i = 0; i < NUMELEMENT; i++)
	{
		for (int j = 0; j < NUMELEMENT; j++)
		{
				g.AddVertex(manMap[i][j]);//初始化顶点数组
		}
		
	}

	for (int i = 0; i < NUMELEMENT; i++)//必须先初始化顶点数组初始化边有用到顶点数组
	{
		for (int j = 0; j < NUMELEMENT; j++)
		{
			UpdateArc(g, i, j);//添加边
		}
	}

}
//连接判断
bool CGameLogic::IsLink(CGraph& g, Vertex v1, Vertex v2)
{
	int nV1Index = v1.row * NUMELEMENT + v1.col;//顶点数组索引
	int nV2Index = v2.row * NUMELEMENT + v2.col;


	//第一个点入栈
	PushVertex(nV1Index);
	//if (g.GetArc(nV1Index,nV2Index)==true)//相同两个点相邻
	//{
		//第二个点入栈
	//	PushVertex(nV2Index);
	//	return true;
	//}
	if (SearchPath( g, nV1Index, nV2Index))
	{
		
		return true;
	}


	
	//栈顶元素出栈
	PopVetex();
	return false;
}


//将路径顶点送入路径顶点数组
void CGameLogic::PushVertex(int v)
{
	m_anPath[m_nVexNum] = v;
	m_nVexNum++;
	
	if (IsCornor())//判断是否形成新的拐点
	{
		m_num++;
	}
}

void CGameLogic::PopVetex()
{

	if (IsCornor())//判断是否形成新的拐点
	{
		m_num--;
	}
	m_nVexNum--;
}

//消子标记函数，拐角超过两个不能消除,两个点更新为空，并更新两个顶点与图中其余顶点的边
void CGameLogic::Clear(CGraph& g, Vertex v1, Vertex v2)
{
	int nV1Index = v1.row * NUMELEMENT + v1.col;//顶点数组索引
	int nV2Index = v2.row * NUMELEMENT + v2.col;
	//跟新顶点数组,两个数组顶点置为-1，空
	g.UpdataVertex(nV2Index, BLANK);
	g.UpdataVertex(nV1Index, BLANK);
	//更新边数组
	UpdateArc(g, v1.row, v1.col);
	UpdateArc(g, v2.row, v2.col);

}

//参数获取得到路径点,返回顶点个数，向控制层传递
int CGameLogic ::GetVexPath(Vertex avPath[PICNUM])
{
	Vertex v;
	for (int i = 0; i < m_nVexNum ; i++)
	{
		for (v.col = 0; v.col < NUMELEMENT; v.col++)
		{
			for (v.row = 0; v.row < NUMELEMENT; v.row++)
			{
				if (v.row * NUMELEMENT + v.col == m_anPath[i])
				{
					avPath[i] = v;//通过路径顶点查找到拐点，存入拐点数组
				}
			}
		}
	}
	return m_nVexNum;
}


//判断拐点，连续三个点不能形成等差数列，则存在拐点
bool CGameLogic::IsCornor()
{
	if (m_nVexNum >= 3)//顶点大于三则判断拐点
	{
		//最后三个顶点
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2])
		{
			return true;
		}
	}
	return false;
}



//通过坐标判断此点上下左右是否有边，有则更新图并返回，相邻为空也表示有边
void CGameLogic::UpdateArc(CGraph& g, int nRow, int nCol)
{

	
	int nV1Index = nRow  * NUMELEMENT +nCol;//当前点数组角标
	if (nCol > 0)//左边有点
	{
		int nV2Index = nV1Index - 1;//左边点数组第角标
		if (g.GetVertex(nV1Index) == g.GetVertex(nV2Index)|| g.GetVertex(nV1Index)==BLANK|| g.GetVertex(nV2Index) == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);//两个点间有联系，则添加到关系数组中
		}

	}
	if (nCol < NUMELEMENT-1)//右边有点
	{
		int nV2Index = nV1Index +1;//右边点
		if (g.GetVertex(nV1Index) == g.GetVertex(nV2Index) || g.GetVertex(nV1Index) == BLANK || g.GetVertex(nV2Index) == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}

	}
	if (nRow>0)
	{
		int nV2Index = nV1Index - NUMELEMENT;//上点
		if (g.GetVertex(nV1Index) == g.GetVertex(nV2Index) || g.GetVertex(nV1Index) == BLANK || g.GetVertex(nV2Index) == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow< NUMELEMENT-1)//下边点
	{
		int nV2Index = nV1Index + NUMELEMENT;//下点
		if (g.GetVertex(nV1Index) == g.GetVertex(nV2Index) || g.GetVertex(nV1Index) == BLANK || g.GetVertex(nV2Index) == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
}


//采用深度优先搜索，判断两顶点是否连通
bool CGameLogic::SearchPath(CGraph& g, int nV0, int nV1)
{
	int nVernum = g.GetVexnum();//顶点数
	for (int  i = 0; i < nVernum; i++)
	{
		if (g.GetArc(nV0,i)&&!IsExsit(i))//两点有连接，且没有被存到数组中
		{
			PushVertex(i);//入栈
			if (m_num>2)//拐点大于2，直接放弃
			{
				PopVetex();//出栈
				continue;//换路径
			}
			if (i!=nV1)//判断是否到终点
			{
				if (g.GetVertex(i)!=BLANK)//中间顶点不为空，路径不能连通
				{
					PopVetex();//出栈
					continue;
				}
				if (SearchPath(g,i,nV1))//递归
				{
					return true;//找到联通路
				}
			}
			else
			{
				return true;
			}
			PopVetex();
		}
	}
	return false;

}

//判断nVi顶点是否保存到连通数组m_anPath中
bool CGameLogic::IsExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_anPath[i]== nVi)//已存入路径数组中
		{
			return true;
		}
	}
	return false;
	
}

//判断图的顶点是否为空
bool CGameLogic::IsBlank(CGraph& g)
{
	int vnum = g.GetVexnum();
	for (int i = 0; i < vnum; i++)
	{
		if (g.GetVertex(i)!=BLANK)
		{
			return false;
		}
	}
	return true;
}

//提示算法
bool CGameLogic::SerachVaildPath(CGraph &g)
{
	int vnum = g.GetVexnum();
	for (int i = 0; i < vnum; i++)
	{
		//得到第一个非空顶点
		if (g.GetVertex(i) != BLANK)
		{
			//便利后得到第二个同色顶点
			for (int j = 0; j < vnum; j++)
			{
				//判断两个点是否连通
				if (i != j)
				{
					if (g.GetVertex(i) == g.GetVertex(j))
					{
						PushVertex(i);
						if (SearchPath(g, i, j))//两点连通
						{
							return true;
						}
						PopVetex();
					}
				}
			}
		}
	}

	return false;
}


//对图结构的顶点重排，并更新顶点关系
void CGameLogic::ResetGraph(CGraph& g)
{
	
}
