#include "project.h"

int main()
{
	SListNode* P1 = NULL;//��ŵ�һ�����ʽ���ݵ�����
	SListNode* P2 = NULL;//��ŵڶ������ʽ���ݵ�����
	SLTDataType coef, expon;
	int count = 0;
	printf("�������һ������ʽ������:>");
	scanf("%d", &count);
	printf("�������һ������ʽ:>");
	int i = 0;
	for (i = 0; i < count; i++)
	{
		fscanf(stdin, "%dx^%d", &coef, &expon);
		SListPushBack(&P1, coef, expon);
	}

	printf("������ڶ�������ʽ������:>");
	scanf("%d", &count);
	printf("������ڶ�������ʽ:>");
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