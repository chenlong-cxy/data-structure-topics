#include "DStack.h"

//˫ջ��ʼ��
void DblStackInit(DblStack* pds)
{
	assert(pds);//���ԣ��ж�ָ����Ч��

	pds->m = 10;//ջ��������Ԫ�ظ���
	SElemType* tmp = (SElemType*)malloc(sizeof(SElemType)*pds->m);
	if (tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	pds->V = tmp;
	pds->bot[0] = -1;//��һ��ջ��Ϊ-1
	pds->bot[1] = pds->m;//�ڶ���ջ��Ϊm
	pds->top[0] = -1;//��һ��ջ����ʼΪ-1
	pds->top[1] = pds->m;//�ڶ���ջ����ʼΪm
}

//�ж�ջ��
void DblStackEmpty(DblStack* pds)
{
	assert(pds);//���ԣ��ж�ָ����Ч��

	if (pds->top[0] == -1)
	{
		printf("��ջ1��\n");
	}
	if (pds->top[1] == pds->m)
	{
		printf("��ջ2��\n");
	}
}

//�ж�ջ��
bool DblStackFull(DblStack* pds)
{
	assert(pds);//���ԣ��ж�ָ����Ч��

	return pds->top[1] - pds->top[0] == 1;
}

//��ջ
void DblStackPush(DblStack* pds, int tag, SElemType x)
{
	assert(pds);//���ԣ��ж�ָ����Ч��
	assert(!DblStackFull(pds));//ջ�����޷���ջ

	if (tag == 1)//���һ��ջ
	{
		pds->top[0]++;
		pds->V[pds->top[0]] = x;
	}
	else//��ڶ���ջ
	{
		pds->top[1]--;
		pds->V[pds->top[1]] = x;
	}
}

//��ջ
SElemType DblStackPop(DblStack*pds, int tag)
{
	assert(pds);//���ԣ��ж�ָ����Ч��

	if (tag == 1)//��һ��ջ������
	{
		if (pds->top[0] == -1)
		{
			printf("��ջ1��\n");
			exit(-1);
		}
		return pds->V[pds->top[0]--];
	}
	else//�ڶ���ջ������
	{
		if (pds->top[1] == pds->m)
		{
			printf("��ջ2��\n");
			exit(-1);
		}
		return pds->V[pds->top[1]++];
	}
}

//��ӡ
void DblStackPrint(DblStack* pds)
{
	assert(pds);

	int i = 0;
	for (i = 0; i < pds->m; i++)
	{
		printf("%d ", pds->V[i]);
	}
	printf("\n");
}