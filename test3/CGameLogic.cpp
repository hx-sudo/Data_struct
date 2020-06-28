//�߼��㣬��ֵ����

#include "pch.h"
#include "CGameLogic.h"




CGameLogic::CGameLogic()
{
	m_nVexNum=0;//��ͨ������
	m_num = 0;//�յ���
}
CGameLogic::~CGameLogic() {

}

//��ʼ����Ϸ��ͼ
void CGameLogic::InitMap(CGraph& g) {//-1Ϊ�߿�,false��ά�����ʾ�߿�
	//��ʼ����ͼ����
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
	int anTemp[PNUM* PENUM];//�������ɵ������������
	for (int i = 0; i < PNUM; i++)//��ɫ��
	{
		for (int j = 0; j < PENUM; j++)//�ظ���
		{
			anTemp[i * PNUM + j] = i;
		}

	}
	srand((int)time(NULL));//�������������
	for (int i = 0; i < 100; i++)//���������������100��
	{
		//����õ���������
		int nIndex1 = rand() %(PNUM * PENUM);
		int nIndex2= rand() %(PNUM * PENUM);

		//����������ֵ
		int nTmp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTmp;

	}
	for (int i = 0; i < NUMELEMENT; i++)//�˶���ѭ��Ϊ��������-1�߽�
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
				g.AddVertex(manMap[i][j]);//��ʼ����������
		}
		
	}

	for (int i = 0; i < NUMELEMENT; i++)//�����ȳ�ʼ�����������ʼ�������õ���������
	{
		for (int j = 0; j < NUMELEMENT; j++)
		{
			UpdateArc(g, i, j);//��ӱ�
		}
	}

}
//�����ж�
bool CGameLogic::IsLink(CGraph& g, Vertex v1, Vertex v2)
{
	int nV1Index = v1.row * NUMELEMENT + v1.col;//������������
	int nV2Index = v2.row * NUMELEMENT + v2.col;


	//��һ������ջ
	PushVertex(nV1Index);
	//if (g.GetArc(nV1Index,nV2Index)==true)//��ͬ����������
	//{
		//�ڶ�������ջ
	//	PushVertex(nV2Index);
	//	return true;
	//}
	if (SearchPath( g, nV1Index, nV2Index))
	{
		
		return true;
	}


	
	//ջ��Ԫ�س�ջ
	PopVetex();
	return false;
}


//��·����������·����������
void CGameLogic::PushVertex(int v)
{
	m_anPath[m_nVexNum] = v;
	m_nVexNum++;
	
	if (IsCornor())//�ж��Ƿ��γ��µĹյ�
	{
		m_num++;
	}
}

void CGameLogic::PopVetex()
{

	if (IsCornor())//�ж��Ƿ��γ��µĹյ�
	{
		m_num--;
	}
	m_nVexNum--;
}

//���ӱ�Ǻ������սǳ���������������,���������Ϊ�գ�����������������ͼ�����ඥ��ı�
void CGameLogic::Clear(CGraph& g, Vertex v1, Vertex v2)
{
	int nV1Index = v1.row * NUMELEMENT + v1.col;//������������
	int nV2Index = v2.row * NUMELEMENT + v2.col;
	//���¶�������,�������鶥����Ϊ-1����
	g.UpdataVertex(nV2Index, BLANK);
	g.UpdataVertex(nV1Index, BLANK);
	//���±�����
	UpdateArc(g, v1.row, v1.col);
	UpdateArc(g, v2.row, v2.col);

}

//������ȡ�õ�·����,���ض������������Ʋ㴫��
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
					avPath[i] = v;//ͨ��·��������ҵ��յ㣬����յ�����
				}
			}
		}
	}
	return m_nVexNum;
}


//�жϹյ㣬���������㲻���γɵȲ����У�����ڹյ�
bool CGameLogic::IsCornor()
{
	if (m_nVexNum >= 3)//������������жϹյ�
	{
		//�����������
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2])
		{
			return true;
		}
	}
	return false;
}



//ͨ�������жϴ˵����������Ƿ��бߣ��������ͼ�����أ�����Ϊ��Ҳ��ʾ�б�
void CGameLogic::UpdateArc(CGraph& g, int nRow, int nCol)
{

	
	int nV1Index = nRow  * NUMELEMENT +nCol;//��ǰ������Ǳ�
	if (nCol > 0)//����е�
	{
		int nV2Index = nV1Index - 1;//��ߵ�����ڽǱ�
		if (g.GetVertex(nV1Index) == g.GetVertex(nV2Index)|| g.GetVertex(nV1Index)==BLANK|| g.GetVertex(nV2Index) == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);//�����������ϵ������ӵ���ϵ������
		}

	}
	if (nCol < NUMELEMENT-1)//�ұ��е�
	{
		int nV2Index = nV1Index +1;//�ұߵ�
		if (g.GetVertex(nV1Index) == g.GetVertex(nV2Index) || g.GetVertex(nV1Index) == BLANK || g.GetVertex(nV2Index) == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}

	}
	if (nRow>0)
	{
		int nV2Index = nV1Index - NUMELEMENT;//�ϵ�
		if (g.GetVertex(nV1Index) == g.GetVertex(nV2Index) || g.GetVertex(nV1Index) == BLANK || g.GetVertex(nV2Index) == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow< NUMELEMENT-1)//�±ߵ�
	{
		int nV2Index = nV1Index + NUMELEMENT;//�µ�
		if (g.GetVertex(nV1Index) == g.GetVertex(nV2Index) || g.GetVertex(nV1Index) == BLANK || g.GetVertex(nV2Index) == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
}


//������������������ж��������Ƿ���ͨ
bool CGameLogic::SearchPath(CGraph& g, int nV0, int nV1)
{
	int nVernum = g.GetVexnum();//������
	for (int  i = 0; i < nVernum; i++)
	{
		if (g.GetArc(nV0,i)&&!IsExsit(i))//���������ӣ���û�б��浽������
		{
			PushVertex(i);//��ջ
			if (m_num>2)//�յ����2��ֱ�ӷ���
			{
				PopVetex();//��ջ
				continue;//��·��
			}
			if (i!=nV1)//�ж��Ƿ��յ�
			{
				if (g.GetVertex(i)!=BLANK)//�м䶥�㲻Ϊ�գ�·��������ͨ
				{
					PopVetex();//��ջ
					continue;
				}
				if (SearchPath(g,i,nV1))//�ݹ�
				{
					return true;//�ҵ���ͨ·
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

//�ж�nVi�����Ƿ񱣴浽��ͨ����m_anPath��
bool CGameLogic::IsExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_anPath[i]== nVi)//�Ѵ���·��������
		{
			return true;
		}
	}
	return false;
	
}

//�ж�ͼ�Ķ����Ƿ�Ϊ��
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

//��ʾ�㷨
bool CGameLogic::SerachVaildPath(CGraph &g)
{
	int vnum = g.GetVexnum();
	for (int i = 0; i < vnum; i++)
	{
		//�õ���һ���ǿն���
		if (g.GetVertex(i) != BLANK)
		{
			//������õ��ڶ���ͬɫ����
			for (int j = 0; j < vnum; j++)
			{
				//�ж��������Ƿ���ͨ
				if (i != j)
				{
					if (g.GetVertex(i) == g.GetVertex(j))
					{
						PushVertex(i);
						if (SearchPath(g, i, j))//������ͨ
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


//��ͼ�ṹ�Ķ������ţ������¶����ϵ
void CGameLogic::ResetGraph(CGraph& g)
{
	
}
