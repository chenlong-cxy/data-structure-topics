#include "project.h"

int main()
{
	SListNode* P1 = NULL;//存放第一个表达式数据的链表
	SListNode* P2 = NULL;//存放第二个表达式数据的链表
	SLTDataType coef, expon;
	//1.输入两个多项式
	int count = 0;
	printf("请输入第一个多项式的项数:>");
	scanf("%d", &count);
	printf("请输入第一个多项式:>");
	int i = 0;
	for (i = 0; i < count; i++)
	{
		/*fscanf(stdin, "%dx^%d", &coef, &expon);*/
		scanf("%dx^%d", &coef, &expon);
		SListPushBack(&P1, coef, expon);
	}

	printf("请输入第二个多项式的项数:>");
	scanf("%d", &count);
	printf("请输入第二个多项式:>");
	for (i = 0; i < count; i++)
	{
		scanf("%dx^%d", &coef, &expon);
		SListPushBack(&P2, coef, expon);
	}

	//2.分别将两个多项式按指数降序排列
	SListNode* SortP1 = InsertSortList(P1);//按指数排序第一个多项式
	SListNode* SortP2 = InsertSortList(P2);//按指数排序第二个多项式
	printf("第一个多项式按指数降序排列为:>");
	SListPrint(SortP1);
	printf("第二个多项式按指数降序排列为:>");
	SListPrint(SortP2);

	//3.将两个多项式相加
	SListNode* PolyAddHead = PolyAdd(SortP1, SortP2);//将两个多项式相加
	printf("将两个多项式相加之后的结果为:>");
	SListPrint(PolyAddHead);
	return 0;
}