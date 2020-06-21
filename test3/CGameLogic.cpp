//�߼��㣬��ֵ����

#include "pch.h"
#include "CGameLogic.h"




CGameLogic::CGameLogic()
{
	m_nVexNum=0;//������
}
CGameLogic::~CGameLogic() {

}

//��ʼ����Ϸ��ͼ
void CGameLogic::InitMap(int anMap[][10]) {
	//��ʼ����ͼ����
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
	for (int i = 0; i < 10; i++)//��
	{
		for (int j = 0; j < 10; j++)//��
		{
			anMap[i][j] = manMap[i][j];
		}
	}
}
//�����ж�
bool CGameLogic::IsLink(int anMap[][10], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	AddVertex(v1);//����һ�������·����
	if (anMap[v1.row][v1.col] != anMap[v2.row][v2.col])//����ѡ�е�Ϊͬһ��
	{
		return false;
	}
	//һ��ֱ����ͨ
	if (v1.row==v2.row)//�к���ͬ
	{
		if (LinkInRow(anMap, v1, v2))//������ͨ�ж�
		{
			AddVertex(v2);
			return true;
		}

	}
	if (v1.col==v2.col)//�к���ͬ
	{
		if (LinkInCol(anMap, v1, v2))//������ͨ�ж�
		{
			AddVertex(v2);
			return true;
		}
	}

	//����ֱ����ͨ
	if (OneCornerLink( anMap,  v1,  v2))
	{
		AddVertex(v2);
		return true;
	}

	//����ֱ����ͨ
	if (TwoCornerLink(anMap, v1, v2))
	{
		AddVertex(v2);
		return true;
	}

	DeleteVertex();//��Ӧ�ӵ��++
	return false;
}


//���ӱ�Ǻ�����ö�ٷ�������ͨ��ʽ
void CGameLogic::Clear(int anMap[][10], Vertex v1, Vertex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;

}

//�жϺ�����ͨ���ж�ֱ�����Ƿ�Ϊ�հ�-1
bool CGameLogic::LinkInRow(int anMap[][10], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	if (v1.col>v2.col)//1��С��2��
	{
		 nCol1 = v2.col;
		 nCol2 = v1.col;
	}
	int nRow = v1.row;


	for (int  i = nCol1+1; i <= nCol2; i++)
	{
		if (i==nCol2)//����������
		{
				return true;
		

				
			
		}
		if (anMap[nRow][i]!=BLANK)//�������ͼ
		{
			break;
		}
	}
	return false;
}
//�ж�������ͨ
bool CGameLogic::LinkInCol(int anMap[][10], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	if (v1.row > v2.row)//1��С��2��
	{
		nRow1 = v2.row;
		nRow2 = v1.row;
	}
	int nCol = v1.col;


	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)//����������
		{
			
				return true;
			
		}
		if (anMap[i][nCol] != BLANK)//�������ͼ
		{
			break;
		}
	}
	return false;

}

//�ж�һ���ս���ͨ,����·���ж�,�յ�Ϊ��
bool CGameLogic::OneCornerLink(int anMap[][10], Vertex v1, Vertex v2)
{
	Vertex vex1, vex2;
	Vertex vex;//�м��
	vex1.col = v1.col;
	vex2.col= v2.col;
	vex1.row = v1.row;
	vex2.row = v2.row;
	if (v1.row > v2.row)//1��rowС��2��
	{
		vex1.col = v1.col;
		vex2.col = v2.col;
		vex1.row = v1.row;
		vex2.row = v2.row;
	}
	if (vex2.col > vex1.col)//���϶�����
	{
		//��������
		vex.row = vex1.row; vex.col = vex2.col;
		if (LineX(anMap, vex1, vex) && LineY(anMap, vex2, vex))
		{
			AddVertex(vex);//����յ�
			return true;
		}
		//��������
		vex.row = vex2.row; vex.col = vex1.col;
		if (LineY(anMap, vex1, vex) && LineX(anMap, vex2, vex))
		{
			AddVertex(vex);
			return true;
		}
	}
	else//���¶�����
	{
		//��������
		vex.row = vex1.row; vex.col = vex2.col;
		if (LineX(anMap, vex1, vex) && LineY(anMap, vex2, vex))
		{
			AddVertex(vex);
			return true;
		}
		//��������
		vex.row = vex2.row; vex.col = vex1.col;
		if (LineY(anMap, vex1, vex) && LineX(anMap, vex2, vex))
		{
			AddVertex(vex);
			return true;
		}
	}
	return false;
}

//�ж������ս���ͨ,�����յ�Ϊ��-1��6������
bool CGameLogic::TwoCornerLink(int anMap[][10], Vertex v1, Vertex v2)
{
	
	//�յ����ƽ��y�ᣬ�յ���������ͬ
	for (int i = 0; i < 10; i++)//�����߽��ж�
	{
		if (anMap[v1.row][i]==BLANK&& anMap[v2.row][i]==BLANK)//�ҵ�Ϊ�յ����յ�
		{
			Vertex vexO, vexT;//�м��
			vexO.row = v1.row; vexO.col = i;//ͬ��v1
			vexT.row = v2.row; vexT.col = i;//ͬ��v2
			if (LineX(anMap, v1, vexO)&& LineX(anMap, v2, vexT))//ͬ�йյ����Լ���ͨ
			{
				if (LinkInCol(anMap, vexO, vexT))//�յ��ͨ�ж�
				{
					AddVertex(vexO);
					AddVertex(vexT);
					return true;
				}

			}
		}
	}

	//�յ����ƽ��x�ᣬ�յ���������ͬ
	for (int i = 0; i < 10; i++)//�����߽��ж�
	{
		if (anMap[i][v1.col] == BLANK && anMap[i][v2.col] == BLANK)//�ҵ�Ϊ�յ����յ�
		{
			Vertex vexO, vexT;//�м��
			vexO.row = i; vexO.col = v1.col;//ͬ��v1
			vexT.row = i; vexT.col = v2.col;//ͬ��v2
			if (LineY(anMap, v1, vexO) && LineY(anMap, v2, vexT))//ͬ�йյ����Լ���ͨ
			{
				if (LinkInRow(anMap, vexO, vexT))//�յ��ͨ�ж�
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

//ֱ����ͨƽ��y�ᣬ�ս���ͨ����,�յ�Ϊ��
bool CGameLogic::LineY(int anMap[][10], Vertex v1, Vertex v2)
{

	int nRow1 = v1.row;
	int nRow2 = v2.row;
	if (v1.row > v2.row)//1��С��2��
	{
		nRow1 = v2.row;
		nRow2 = v1.row;
	}
	int nCol = v1.col;


	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)//����������
		{
			
			if (anMap[v2.row][v2.col] == BLANK)//���ڹս��ж��Ƿ�Ϊ��ͬԪ��
			{
				return true;
			}
		}
		if (anMap[i][nCol] != BLANK)//�������ͼ
		{
			break;
		}
	}
	return false;

}
//x�ᣬ�յ�Ϊ��
bool CGameLogic::LineX(int anMap[][10], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	if (v1.col > v2.col)//1��С��2��
	{
		nCol1 = v2.col;
		nCol2 = v1.col;
	}
	int nRow = v1.row;


	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2)//����������
		{
			if (anMap[v2.row][v2.col] == BLANK)//һ�������ã����ڹս��ж�
			{
				return true;

			}
		}
		if (anMap[nRow][i] != BLANK)//�������ͼ
		{
			break;
		}
		
	}
		return false;

}

//������ȡ�õ�·��avPath[8],���ض������
int CGameLogic::GetVexPath(Vertex avPath[8])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;//����·���������
}


//���·������
void CGameLogic::AddVertex(Vertex v)
{
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}

//ȡ��һ������
void CGameLogic::DeleteVertex()
{
	m_nVexNum--;
}