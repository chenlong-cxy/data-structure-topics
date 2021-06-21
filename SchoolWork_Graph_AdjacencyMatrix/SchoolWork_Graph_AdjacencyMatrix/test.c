#include "Graph.h"

int main()
{
	GNode* pg;
	pg = BuildGraph();
	printf("邻接矩阵为:>\n");
	Print(&pg);
	printf("深度优先搜索结果为:>\n");
	DFS(&pg, 0);
	printf("广度优先搜索结果为:>\n");
	BFS(&pg, 0);
	return 0;
}