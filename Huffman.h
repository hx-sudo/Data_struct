#pragma once
#include <cstdio>
#include"Compress.h"
#ifndef HUFFMAN_H
#define HUFFMAN_H

//huffman���ڵ�
typedef struct 
{
	int weight;//�ڵ�Ȩֵ
	int parent;//���ڵ�
	int lchild;//����
	int rchild;//�Һ���
}HTNode,*Huffmantree;

//huffman����
typedef struct
{
	char* code;


}HCNode,*Huffmancode;



int select(Huffmantree pHT, int nSize);//ѡ��������Ȩֵ��С�Ľڵ�

int creattree(Huffmantree pHT,int weight[],int n);//���ɹ�������

int creatcoding(Huffmantree pHT,Huffmancode pHC);//���ɹ���������


int Showcode(Huffmancode pHC);//չʾHuffman����

int Encode(const char* pFilename, const Huffmancode pHC, char* pBuffer, const int nSize);//���ù���������ʵ���ļ�ѹ��

#endif // !HUFFMAN_H
