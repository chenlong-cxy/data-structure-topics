#include "Graph.h"

//��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ
GNode* CreateGraph(int VertexNum)
{
	GNode* Graph = (GNode*)malloc(sizeof(GNode));
	if (Graph == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	int i = 0;
	for (i = 0; i < Graph->Nv; i++)
	{
		int j = 0;
		for (j = 0; j < Graph->Nv; j++)
		{
			Graph->Graph[i][j] = 0;
		}
	}
	return Graph;
}

//�����
void InsertEdge(GNode* Graph, ENode* Edge)
{
	Graph->Graph[Edge->V1][Edge->V2] = Edge->Weight;
	//Graph->Graph[Edge->V2][Edge->V1] = Edge->Weight;
}

//����һ��ͼ
GNode* BuildGraph()
{
	GNode* Graph;
	int Nv;
	printf("�����������Ķ������:>");
	scanf("%d", &Nv);
	Graph = CreateGraph(Nv);
	printf("�����������ı���:>");
	scanf("%d", &(Graph->Ne));
	if (Graph->Ne != 0)
	{
		ENode* Edge = (ENode*)malloc(sizeof(ENode));
		if (Edge == NULL)
		{
			printf("malloc fail\n");
			exit(-1);
		}
		printf("����������ߣ���ʽΪ����� �յ� Ȩ��:>��");
		int i = 0;
		for (i = 0; i < Graph->Ne; i++)
		{
			scanf("%d %d %d", &(Edge->V1), &(Edge->V2), &(Edge->Weight));
			InsertEdge(Graph, Edge);
		}
	}
	printf("�����붥�������:>");
	int i = 0;
	for (i = 0; i < Graph->Nv; i++)
	{
		scanf("%d", &(Graph->Data[i]));
	}
	return Graph;
}

void Print(WeightType arr[5][5])
{
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		int j = 0;
		for (j = 0; j < 5; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}