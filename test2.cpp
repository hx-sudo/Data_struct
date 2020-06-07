//程序入口

#include <iostream>
#include<stdlib.h>
#include"Tourism.h"


using namespace std;

int main()
{
	char choice;
	
	while (true)
	{
		cout <<endl<< "######景区信息管理系统######" << endl
			<< "1.创建景区景点图" << endl
			<< "2.查询景点信息" << endl
			<< "3.旅游景点导航" << endl
			<< "4.搜索最短路径" << endl
			<< "5.铺设电路规划"<<endl
			<< "6.退出" << endl
			<< "请输入操作编号（1-6）:" ;
		cin >> choice;
		if(54<choice||choice<49)
			cout << "输入错误，重新输入" << endl;
		else
		switch (choice)
		{
		case '1':
			
			CreatGraph();//创建图
			break;
		case '2':
			GetSpotInfo();//查询，输出景点所有信息
			break;


		case '3':
			TravelPath();//景点导航
			break;


		case '4':
			FindShotPath();//最短路径
			break;

		case '5':
			DesignPath();//铺设电路规划图
			break;

		case '6':
			cout << "****退出****" << endl;
			exit(0);
			break;

		}
	}
	

}

