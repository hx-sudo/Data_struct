#pragma once
//��ֹͷ�ļ����ظ���������

#define BLANK -1
#define SIZEELEMENT 40//����ˮ��ͼƬ��С
#define GAMETOP 100 //��Ϸ��ͼ��㵽�߿����xy
#define PLAY_TIMER_ID 1//���������
#define NUMELEMENT 6//��Ϸ��ͼ�У�����ϷС������������ͨ���޸������޸���Ϸ��ͼ��С��Ϊ�������Σ�
#define PICNUM NUMELEMENT*NUMELEMENT//�ܵ�ͼƬ��
#define PNUM 4//ͼƬ��ɫ���������Σ���ʵ����2��(�����Ϊ��Ϸͼ-1�߿�)
#define PENUM 4//ÿ�ֻ�ɫ��ͼƬ��


typedef struct tagVertex
{
	int row;//��
	int col;//��
	int info;//��Ϣ
}Vertex;//������Ϸ��ͼ��һ������кţ��б�ֵ��Ϣ
