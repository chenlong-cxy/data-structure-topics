#include "project.h"

int main()
{
	SListNode* P1 = NULL;//��ŵ�һ�����ʽ���ݵ�����
	SListNode* P2 = NULL;//��ŵڶ������ʽ���ݵ�����
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