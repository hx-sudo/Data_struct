
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"Tourism.h"
#include"Graph.h"
#pragma warning(disable:4996)

using namespace std;

const string EFILE = "D:\\桌面\\codes\\test2\\Edge.txt";
const string VFILE = "D:\\桌面\\codes\\test2\\Vex.txt";

CGraph m_Graph;

//功能一。读文件，保存信息。获取景点信息和道路信息
int CreatGraph()
{
	cout << "****创建景区景点图" << endl;
	if (m_Graph.m_nVexNum != 0)
	{
		cout << "图已存在" << endl;
		return 0;
	}


	//顶点
	ifstream vin(VFILE);
	if (!vin)
	{
		cout << "点文件打开失败！" << endl;
		exit(0);
	}
	int nums;//图的顶点数
	Vex vx;//点
	Edge eg = {0,0,0};//边
	string a1;
	getline(vin, a1);
	stringstream ss; ss << a1;  ss >> nums;//将读取的第一行个数,图的顶点数
	cout << "顶点数目" << nums<<endl;
	cout << "....顶点...." << endl;

	for (int i = 0; i < nums; i++)//读取顶点信息
	{
		getline(vin, a1); vx.num = stoi(a1);
		getline(vin, a1); strcpy(vx.name, a1.data());
		getline(vin, a1); strcpy(vx.desc, a1.data());
		m_Graph.InsertVex( vx);//插入点
		cout << vx.num << "-" << vx.name << "-" << vx.desc << endl;
	}
	vin.close();


	bool InsertEdge(Edge sEdge);//插入边

	//边
	ifstream ein(EFILE);
	if (!ein)
	{
		cout << "边文件打开失败！" << endl;
		exit(0);
	}

	cout << "....边...." << endl;
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
		m_Graph.InsertEdge(eg);//插入边
		cout << "<v" << eg.vex1 << ",v" << eg.vex2 << ">  " << eg.weight << endl;
	}
	ein.close();

	return 0;
}

//功能二，查询景点输出所有信息
int GetSpotInfo()
{
	Edge aEdge[20];//响铃边
	if (m_Graph.m_nVexNum == 0)
	{
		cout << "没有构造图！" << endl;
		return 0;
	}
	else
	{
		cout << "****查询景点编号" << endl;

	}
	int choice;//选择编号
	Vex vx;//查找到的点
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		cout << m_Graph.m_aVexs[i].num << "-" << m_Graph.m_aVexs[i].name<<endl;
	}

	cout << "请输入要查询的景点编号："; cin >> choice;
	if (choice < 0 || choice >= m_Graph.m_nVexNum)
	{
		cout << "输入错误，不存在此点！" << endl;
		return 0;
	}
	vx = m_Graph.GetVex(choice);//找点
	cout << vx.name << "    " << vx.desc<<endl;
	cout << "....周边信息...." << endl;

	int n = m_Graph.FindEdge(choice, aEdge);

		if (n == 0)
			cout << "没有邻边" << endl;
		else
		{
			for (int i = 0; i < n; i++)
			{
				int x = aEdge[i].vex1;
				int y = aEdge[i].vex2;
				
				cout << m_Graph.GetVex(x).name << "-" << m_Graph.GetVex(y).name << "——" << aEdge[i].weight <<"米"<< endl;
			}
		}

	return 0;

}

//功能三，调用dfstraverse(),实现景点导航
void TravelPath()
{
	
	if (m_Graph.m_nVexNum == 0)
	{
		cout << "没有构造图！" << endl;
		return;
	}
	else
	{
		cout << "****旅游景点导航*****" << endl;

	}
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		cout << m_Graph.m_aVexs[i].num << "-" << m_Graph.m_aVexs[i].name << endl;
	}

	int choice;////输入景点编号
	cout << "输入起始点编号:"; cin >> choice;
	if (choice >= m_Graph.m_nVexNum)
	{
		cout << "输入错误" << endl;
		return;
	}
	
	//遍历景区景点图
	PathList List= new Path;
	PathList head = List;//保存头节点
	m_Graph.DFSTraverse(choice, List);
	
	
	//输出遍历结果
	int i = 1;//路线条数,序号
	cout << "导航路线：" << endl;
	while (head != NULL)//此处head和head->next结果差一会有一个错误结果
	{
		cout << "路线" << i << ":  ";
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
	




