#include "Graph.h"

int main()
{
	GNode* pg;
	pg = BuildGraph();
	printf("�ڽӾ���Ϊ:>\n");
	Print(&pg);
	printf("��������������Ϊ:>\n");
	DFS(&pg, 0);
	printf("��������������Ϊ:>\n");
	BFS(&pg, 0);
	return 0;
}