// test1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"Compress.h"  
using namespace std;

int main()//程序入口
{
	char filename[256];//压缩文件名
	cout << "==========Huffman文件压缩==========" << endl;
	cout << "请输入文件名：";
	cin >> filename;
	Compress(filename);//压缩文件

	return 0;
}

