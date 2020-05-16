#pragma once
#include <cstdio>
#include"Compress.h"
#ifndef HUFFMAN_H
#define HUFFMAN_H

//huffman树节点
typedef struct 
{
	int weight;//节点权值
	int parent;//父节点
	int lchild;//左孩子
	int rchild;//右孩子
}HTNode,*Huffmantree;

//huffman编码
typedef struct
{
	char* code;


}HCNode,*Huffmancode;



int select(Huffmantree pHT, int nSize);//选择数组中权值最小的节点

int creattree(Huffmantree pHT,int weight[],int n);//生成哈夫曼树

int creatcoding(Huffmantree pHT,Huffmancode pHC,int n);//生成哈夫曼编码

int Str2byte();//将字符串转化为字节，得到最终编码，保存到*.buf文件中



#endif // !HUFFMAN_H
