#include "project.h"

int main()
{
	SListNode* P1 = NULL;//存放第一个表达式数据的链表
	SListNode* P2 = NULL;//存放第二个表达式数据的链表
	char expr[MAX];
	int coef;
	int expon;
	gets(expr);
	while (sscanf(expr, "%dx^%d", &coef, &expon) != EOF)
	{
		printf("%d %d", coef, expon);
	}
	return 0;
}