#include "Graph.h"
#include "queue.h"

//初始化一个有VertexNum个顶点但没有边的图
GNode* CreateGraph(int VertexNum)
{
	GNode* Graph = (GNode*)malloc(sizeof(GNode)); //开辟存储图的空间
	if (Graph == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	Graph->Nv = VertexNum; //顶点个数赋值
	Graph->Ne = 0; //边数初始化为0
	int i = 0;
	//邻接矩阵初始化为0
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
	return Graph; //返回图
}

//插入边
void InsertEdge(GNode* Graph, ENode* Edge)
{
	Graph->G[Edge->V1][Edge->V2] = Edge->Weight;
	Graph->G[Edge->V2][Edge->V1] = Edge->Weight; //无向图
}

//创建一个图
GNode* BuildGraph()
{
	GNode* Graph;
	int Nv; //顶点个数
	printf("请输入需读入的顶点个数:>");
	scanf("%d", &Nv);
	Graph = CreateGraph(Nv); //根据顶点个数Nv，创建一个有Nv个顶点但没有边的图
	printf("请输入需读入的边数:>");
	scanf("%d", &(Graph->Ne));
	if (Graph->Ne != 0)
	{
		ENode* Edge = (ENode*)malloc(sizeof(ENode)); //开辟辅助空间用于暂时存储边的数据
		if (Edge == NULL)
		{
			printf("malloc fail\n");
			exit(-1);
		}
		printf("请依次输入边，格式为“起点 终点 权重”:>\n");
		int i = 0;
		for (i = 0; i < Graph->Ne; i++)
		{
			scanf("%d %d %d", &(Edge->V1), &(Edge->V2), &(Edge->Weight));
			InsertEdge(Graph, Edge);
		}
		free(Edge); //释放辅助空间
	}
	printf("请输入顶点的数据:>");
	getchar();
	int i = 0;
	for (i = 0; i < Graph->Nv; i++)
	{
		scanf("%c", &(Graph->Data[i]));
	}
	return Graph; //返回图
}

//打印邻接矩阵
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

//深度优先搜索
void DFS(GNode** pg, Vertex v) //从顶点v开始进行深度优先搜索
{
	if (v < 0 || v >= (*pg)->Nv)
	{
		printf("位置出错\n");
		exit(-1);
	}
	printf("点%c正在被访问...\n", (*pg)->Data[v]);
	visited1[v] = 1;
	for (int j = 0; j < (*pg)->Nv; j++)
	{
		if (visited1[j] == 0 && (*pg)->G[v][j] != 0)
		{
			DFS(pg, j);
		}
	}
}

//广度优先搜索
void BFS(GNode** pg, Vertex v)
{
	if (v < 0 || v >= (*pg)->Nv)
	{
		printf("位置出错\n");
		exit(-1);
	}
	Queue q;
	QueueInit(&q);
	printf("点%c正在被访问...\n", (*pg)->Data[v]);
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
				printf("点%c正在被访问...\n", (*pg)->Data[j]);
				visited2[j] = 1;
				QueuePush(&q, j);
			}
		}
	}
	QueueDestroy(&q);
}