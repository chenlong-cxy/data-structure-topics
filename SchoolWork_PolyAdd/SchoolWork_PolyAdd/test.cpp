#include "project.h"

int main()
{
	SListNode* P1 = NULL;//��ŵ�һ�����ʽ���ݵ�����
	SListNode* P2 = NULL;//��ŵڶ������ʽ���ݵ�����
	SLTDataType coef, expon;
	//1.������������ʽ
	int count = 0;
	printf("�������һ������ʽ������:>");
	scanf("%d", &count);
	printf("�������һ������ʽ:>");
	int i = 0;
	for (i = 0; i < count; i++)
	{
		/*fscanf(stdin, "%dx^%d", &coef, &expon);*/
		scanf("%dx^%d", &coef, &expon);
		SListPushBack(&P1, coef, expon);
	}

	printf("������ڶ�������ʽ������:>");
	scanf("%d", &count);
	printf("������ڶ�������ʽ:>");
	for (i = 0; i < count; i++)
	{
		scanf("%dx^%d", &coef, &expon);
		SListPushBack(&P2, coef, expon);
	}

	//2.�ֱ���������ʽ��ָ����������
	SListNode* SortP1 = InsertSortList(P1);//��ָ�������һ������ʽ
	SListNode* SortP2 = InsertSortList(P2);//��ָ������ڶ�������ʽ
	printf("��һ������ʽ��ָ����������Ϊ:>");
	SListPrint(SortP1);
	printf("�ڶ�������ʽ��ָ����������Ϊ:>");
	SListPrint(SortP2);

	//3.����������ʽ���
	SListNode* PolyAddHead = PolyAdd(SortP1, SortP2);//����������ʽ���
	printf("����������ʽ���֮��Ľ��Ϊ:>");
	SListPrint(PolyAddHead);
	return 0;
}