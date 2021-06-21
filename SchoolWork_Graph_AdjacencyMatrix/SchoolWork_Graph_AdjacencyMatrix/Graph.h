#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 8  //最大顶点数(矩阵的阶数)
#define MaxSize 100
int visited1[MaxSize]; //用于DFS
int visited2[MaxSize]; //用于BFS

typedef int WeightType;
typedef char DataType;

//图结点的定义
typedef struct GNode
{
	int Nv;  //顶点数
	int Ne;  //边数
	WeightType G[MaxVertexNum][MaxVertexNum];  //邻接矩阵
	DataType Data[MaxVertexNum];  //存储顶点的数据
}GNode;

typedef int Vertex;

//边的定义
typedef struct ENode
{
	Vertex V1, V2;  //边的起始位置和终止位置
	WeightType Weight;  //权重
}ENode;

//初始化一个有VertexNum个顶点但没有边的图
GNode* CreateGraph(int VertexNum);

//插入边
void InsertEdge(GNode* Graph, ENode* Edge);

//创建一个图
GNode* BuildGraph();

//打印邻接矩阵
void Print(GNode** pg);

//深度优先搜索
void DFS(GNode** pg, Vertex v);

//广度优先搜索
void BFS(GNode** pg, Vertex v);