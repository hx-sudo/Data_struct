// test1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//

#include <iostream>
#include"Compress.h"  
using namespace std;

int main()//程序入口
{
	char choice;
	char filename[256];//压缩文件名
	cout << "########Huffman文件压缩########" << endl;
	while (true)
	{
		cout << "1.压缩————2.退出" << endl;
		cout << "请输入对应序号:"; cin >> choice;
		switch (choice)
		{
		case '1':
		{
			cout << "请输入文件名：";
			cin >> filename;
			if (Compress(filename) == 1)//压缩文件
			{
				cout << "请重试！" << endl;
			}
			else
			{
				cout << "压缩成功！（文件已经保存，注意查看）" << endl;
			}
			break;
		}
		case '2':
		{
			exit(0);
			break;
		}
		default:
		{
			cout << "输入错误，请重新输入" << endl;
			break;
		}
		}
	}
	


	cout << "请输入文件名：";
	cin >> filename;
	if (Compress(filename) == 1)//压缩文件
	{
		cout << "请重试！" << endl;
	}

	return 0;
}

