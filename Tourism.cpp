
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"Tourism.h"
#include"Graph.h"
#pragma warning(disable:4996)

using namespace std;

const string EFILE = "D:\\����\\codes\\test2\\Edge.txt";
const string VFILE = "D:\\����\\codes\\test2\\Vex.txt";

CGraph m_Graph;

//����һ�����ļ���������Ϣ����ȡ������Ϣ�͵�·��Ϣ
int CreatGraph()
{
	cout << "****������������ͼ" << endl;
	if (m_Graph.m_nVexNum != 0)
	{
		cout << "ͼ�Ѵ���" << endl;
		return 0;
	}


	//����
	ifstream vin(VFILE);
	if (!vin)
	{
		cout << "���ļ���ʧ�ܣ�" << endl;
		exit(0);
	}
	int nums;//ͼ�Ķ�����
	Vex vx;//��
	Edge eg = {0,0,0};//��
	string a1;
	getline(vin, a1);
	stringstream ss; ss << a1;  ss >> nums;//����ȡ�ĵ�һ�и���,ͼ�Ķ�����
	cout << "������Ŀ" << nums<<endl;
	cout << "....����...." << endl;

	for (int i = 0; i < nums; i++)//��ȡ������Ϣ
	{
		getline(vin, a1); vx.num = stoi(a1);
		getline(vin, a1); strcpy(vx.name, a1.data());
		getline(vin, a1); strcpy(vx.desc, a1.data());
		m_Graph.InsertVex( vx);//�����
		cout << vx.num << "-" << vx.name << "-" << vx.desc << endl;
	}
	vin.close();


	bool InsertEdge(Edge sEdge);//�����

	//��
	ifstream ein(EFILE);
	if (!ein)
	{
		cout << "���ļ���ʧ�ܣ�" << endl;
		exit(0);
	}

	cout << "....��...." << endl;
	while (getline(ein, a1))
	{
		int b[3] = { 0 };
		stringstream ss(a1);
		int i = 0;
		string a2;
		while (getline(ss, a2, ' '))
		{
			b[i] = atoi(a2.c_str());
			i++;
		}
		eg.vex1 = b[0]; eg.vex2 = b[1]; eg.weight = b[2];
		m_Graph.InsertEdge(eg);//�����
		cout << "<v" << eg.vex1 << ",v" << eg.vex2 << ">  " << eg.weight << endl;
	}
	ein.close();

	return 0;
}

//���ܶ�����ѯ�������������Ϣ
int GetSpotInfo()
{
	Edge aEdge[20];//�����
	if (m_Graph.m_nVexNum == 0)
	{
		cout << "û�й���ͼ��" << endl;
		return 0;
	}
	else
	{
		cout << "****��ѯ������" << endl;

	}
	int choice;//ѡ����
	Vex vx;//���ҵ��ĵ�
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		cout << m_Graph.m_aVexs[i].num << "-" << m_Graph.m_aVexs[i].name<<endl;
	}

	cout << "������Ҫ��ѯ�ľ����ţ�"; cin >> choice;
	if (choice < 0 || choice >= m_Graph.m_nVexNum)
	{
		cout << "������󣬲����ڴ˵㣡" << endl;
		return 0;
	}
	vx = m_Graph.GetVex(choice);//�ҵ�
	cout << vx.name << "    " << vx.desc<<endl;
	cout << "....�ܱ���Ϣ...." << endl;

	int n = m_Graph.FindEdge(choice, aEdge);

		if (n == 0)
			cout << "û���ڱ�" << endl;
		else
		{
			for (int i = 0; i < n; i++)
			{
				int x = aEdge[i].vex1;
				int y = aEdge[i].vex2;
				
				cout << m_Graph.GetVex(x).name << "-" << m_Graph.GetVex(y).name << "����" << aEdge[i].weight <<"��"<< endl;
			}
		}

	return 0;

}

//������������dfstraverse(),ʵ�־��㵼��
void TravelPath()
{
	
	if (m_Graph.m_nVexNum == 0)
	{
		cout << "û�й���ͼ��" << endl;
		return;
	}
	else
	{
		cout << "****���ξ��㵼��*****" << endl;

	}
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		cout << m_Graph.m_aVexs[i].num << "-" << m_Graph.m_aVexs[i].name << endl;
	}

	int choice;////���뾰����
	cout << "������ʼ����:"; cin >> choice;
	if (choice >= m_Graph.m_nVexNum)
	{
		cout << "�������" << endl;
		return;
	}
	
	//������������ͼ
	PathList List= new Path;
	PathList head = List;//����ͷ�ڵ�
	m_Graph.DFSTraverse(choice, List);
	
	
	//����������
	int i = 1;//·������,���
	cout << "����·�ߣ�" << endl;
	while (head != NULL)//�˴�head��head->next�����һ����һ��������
	{
		cout << "·��" << i << ":  ";
		for (int j = 0; j < m_Graph.m_nVexNum;j++)
		{
			cout << m_Graph.m_aVexs[head->vexs[j]].name;

			if (j + 1 == m_Graph.m_nVexNum)
				cout << endl;
			else
				cout << " -> ";
		}
		head = head->next;
		i++;
		
	}
}
	




