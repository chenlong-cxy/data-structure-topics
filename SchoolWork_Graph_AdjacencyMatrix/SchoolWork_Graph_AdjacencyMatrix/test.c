#include "Graph.h"

int main()
{
	GNode* pg;
	pg = BuildGraph();
	printf("�ڽӾ���Ϊ:>\n");
	Print(&pg);
	printf("��������������Ϊ:>\n");
	DFS(&pg, 4);
	printf("��������������Ϊ:>\n");
	BFS(&pg, 4);
	return 0;
}