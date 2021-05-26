#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 5  //��󶥵���(����Ľ���)
//#define INFINITY 

typedef int WeightType;
typedef int DataType;

//ͼ���Ķ���
typedef struct GNode
{
	int Nv;  //������
	int Ne;  //����
	WeightType Graph[MaxVertexNum][MaxVertexNum];  //�ڽӾ���
	DataType Data[MaxVertexNum];  //�洢���������
}GNode;

typedef int Vertex;

//�ߵĶ���
typedef struct ENode
{
	Vertex V1, V2;  //�ߵ���ʼλ�ú���ֹλ��
	WeightType Weight;  //Ȩ��
}ENode;

//��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ
GNode* CreateGraph(int VertexNum);

//�����
void InsertEdge(GNode* Graph, ENode* Edge);

//����һ��ͼ
GNode* BuildGraph();

void Print(WeightType arr[5][5]);