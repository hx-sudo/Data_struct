#pragma once
//��ֹͷ�ļ����ظ���������

#define BLANK -1
#define SIZEELEMENT 40//����ˮ��ͼƬ��С
#define GAMETOP 100//��Ϸ��ͼ��㵽�߿����xy
#define NUMELEMENT 12//��Ϸ��ͼ�У�����ϷС������(�����Ϊ��Ϸͼ-1�߿�)
#define PICNUM NUMELEMENT*NUMELEMENT//�ܵ�ͼƬ��
#define PNUM 10//ͼƬ��ɫ���������Σ���ʵ����2��
#define PENUM 10//ÿ�ֻ�ɫ��ͼƬ��


typedef struct tagVertex
{
	int row;//��
	int col;//��
	int info;//��Ϣ
}Vertex;//������Ϸ��ͼ��һ������кţ��б�ֵ��Ϣ
