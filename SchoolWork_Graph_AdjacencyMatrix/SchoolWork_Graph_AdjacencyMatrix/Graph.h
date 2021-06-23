#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100  //��󶥵���
int visited1[MaxVertexNum]; //����DFS
int visited2[MaxVertexNum]; //����BFS

typedef int WeightType; //Ȩ�ص�����
typedef char DataType; //�������������

//ͼ���Ķ���
typedef struct GNode
{
	int Nv;  //������
	int Ne;  //����
	WeightType G[MaxVertexNum][MaxVertexNum];  //�ڽӾ���
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

//��ӡ�ڽӾ���
void Print(GNode** pg);

//�����������
void DFS(GNode** pg, Vertex v);

//�����������
void BFS(GNode** pg, Vertex v);