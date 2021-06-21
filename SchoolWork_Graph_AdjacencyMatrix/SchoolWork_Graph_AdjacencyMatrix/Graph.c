#include "Graph.h"
#include "queue.h"

//��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ
GNode* CreateGraph(int VertexNum)
{
	GNode* Graph = (GNode*)malloc(sizeof(GNode)); //���ٴ洢ͼ�Ŀռ�
	if (Graph == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	Graph->Nv = VertexNum; //���������ֵ
	Graph->Ne = 0; //������ʼ��Ϊ0
	int i = 0;
	//�ڽӾ����ʼ��Ϊ0
	for (i = 0; i < Graph->Nv; i++)
	{
		int j = 0;
		for (j = 0; j < Graph->Nv; j++)
		{
			Graph->G[i][j] = 0;
		}
	}
	for (i = 0; i < Graph->Nv; i++)
	{
		Graph->Data[i] = '0';
	}
	return Graph; //����ͼ
}

//�����
void InsertEdge(GNode* Graph, ENode* Edge)
{
	Graph->G[Edge->V1][Edge->V2] = Edge->Weight;
	Graph->G[Edge->V2][Edge->V1] = Edge->Weight; //����ͼ
}

//����һ��ͼ
GNode* BuildGraph()
{
	GNode* Graph;
	int Nv; //�������
	printf("�����������Ķ������:>");
	scanf("%d", &Nv);
	Graph = CreateGraph(Nv); //���ݶ������Nv������һ����Nv�����㵫û�бߵ�ͼ
	printf("�����������ı���:>");
	scanf("%d", &(Graph->Ne));
	if (Graph->Ne != 0)
	{
		ENode* Edge = (ENode*)malloc(sizeof(ENode)); //���ٸ����ռ�������ʱ�洢�ߵ�����
		if (Edge == NULL)
		{
			printf("malloc fail\n");
			exit(-1);
		}
		printf("����������ߣ���ʽΪ����� �յ� Ȩ�ء�:>\n");
		int i = 0;
		for (i = 0; i < Graph->Ne; i++)
		{
			scanf("%d %d %d", &(Edge->V1), &(Edge->V2), &(Edge->Weight));
			InsertEdge(Graph, Edge);
		}
		free(Edge); //�ͷŸ����ռ�
	}
	printf("�����붥�������:>");
	getchar();
	int i = 0;
	for (i = 0; i < Graph->Nv; i++)
	{
		scanf("%c", &(Graph->Data[i]));
	}
	return Graph; //����ͼ
}

//��ӡ�ڽӾ���
void Print(GNode** pg)
{
	int i = 0;
	for (i = 0; i < (*pg)->Nv; i++)
	{
		int j = 0;
		for (j = 0; j < (*pg)->Nv; j++)
		{
			printf("%d ", (*pg)->G[i][j]);
		}
		printf("\n");
	}
}

//�����������
void DFS(GNode** pg, Vertex v) //�Ӷ���v��ʼ���������������
{
	if (v < 0 || v >= (*pg)->Nv)
	{
		printf("λ�ó���\n");
		exit(-1);
	}
	printf("��%c���ڱ�����...\n", (*pg)->Data[v]);
	visited1[v] = 1;
	for (int j = 0; j < (*pg)->Nv; j++)
	{
		if (visited1[j] == 0 && (*pg)->G[v][j] != 0)
		{
			DFS(pg, j);
		}
	}
}

//�����������
void BFS(GNode** pg, Vertex v)
{
	if (v < 0 || v >= (*pg)->Nv)
	{
		printf("λ�ó���\n");
		exit(-1);
	}
	Queue q;
	QueueInit(&q);
	printf("��%c���ڱ�����...\n", (*pg)->Data[v]);
	visited2[v] = 1;
	QueuePush(&q, v);
	while (!QueueEmpty(&q))
	{
		Vertex front = QueueFront(&q);
		QueuePop(&q);
		for (int j = 0; j < (*pg)->Nv; j++)
		{
			if (visited2[j] == 0 && (*pg)->G[front][j] != 0)
			{
				printf("��%c���ڱ�����...\n", (*pg)->Data[j]);
				visited2[j] = 1;
				QueuePush(&q, j);
			}
		}
	}
	QueueDestroy(&q);
}