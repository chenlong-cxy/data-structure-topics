#include "project.h"

int main()
{
	SListNode* P1 = NULL;//存放第一个表达式数据的链表
	SListNode* P2 = NULL;//存放第二个表达式数据的链表
	SLTDataType coef, expon;
	int count = 0;
	printf("请输入第一个多项式的项数:>");
	scanf("%d", &count);
	printf("请输入第一个多项式:>");
	int i = 0;
	for (i = 0; i < count; i++)
	{
		fscanf(stdin, "%dx^%d", &coef, &expon);
		SListPushBack(&P1, coef, expon);
	}

	printf("请输入第二个多项式的项数:>");
	scanf("%d", &count);
	printf("请输入第二个多项式:>");
	for (i = 0; i < count; i++)
	{
		fscanf(stdin, "%dx^%d", &coef, &expon);
		SListPushBack(&P2, coef, expon);
	}

	SListNode* PolyAddHead = PolyAdd(P1, P2);


	//SListPrint(P1);
	//SListPrint(P2);
	return 0;
}