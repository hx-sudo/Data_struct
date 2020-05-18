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
			<< "2.查询景点编号" << endl
			<< "3." << endl
			<< "4." << endl
			<< "5.退出" << endl
			<< "请输入操作编号（1-5）:" ;
		cin >> choice;
		if(53<choice||choice<49)
			cout << "输入错误，重新输入" << endl;
		else
		switch (choice)
		{
		case '1':
			cout << "****创建景区景点图" << endl;
			CreatGraph();
			break;
		case '2':
			GetSpotInfo();//输出所有信息
			break;


		case '3':
			cout << "****" << endl;
			break;


		case '4':
			cout << "****" << endl;
			break;


		case '5':
			cout << "****退出" << endl;
			exit(0);
			break;

		}
	}
	

}

