#include "project.h"
//��ӡ����
void SListPrint(SListNode* plist)
{
	SListNode* cur = plist;
	if (cur)
	{
		printf("%dx^%d", cur->coef, cur->expon);//��ӡ��һ��
		cur = cur->next;
	}
	while (cur)
	{
		printf("%+dx^%d", cur->coef, cur->expon);
		cur = cur->next;
	}
	printf("\n");
}

//����һ���½�㣬�����½���ַ
SListNode* BuySLTNode(SLTDataType coef, SLTDataType expon)
{
	SListNode* node = (SListNode*)malloc(sizeof(SListNode));//���½������ռ�
	if (node == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	node->coef = coef;//ϵ����ֵ
	node->expon = expon;//ָ����ֵ
	node->next = NULL;//���½���ָ�����ÿ�
	return node;//�����½���ַ
}

//β��
void SListPushBack(SListNode** pplist, SLTDataType coef, SLTDataType expon)
{
	SListNode* newnode = BuySLTNode(coef, expon);//����һ���½��
	if (*pplist == NULL)//�ж��Ƿ�Ϊ�ձ�
	{
		*pplist = newnode;//ͷָ��ֱ��ָ���½��
	}
	else
	{
		SListNode* tail = *pplist;//����ͷָ��
		while (tail->next != NULL)//��ĳ����ָ����ΪNULL��˵���������һ�����
		{
			tail = tail->next;////ָ��ָ����һ�����
		}
		tail->next = newnode;//�����һ������ָ����ָ���½��
	}
}

//ѡ������
SListNode* InsertSortList(SListNode* head)
{
	if (head == NULL || head->next == NULL)//������Ϊ�ջ�����ֻ��һ����㣬��������
		return head;

	SListNode* sortHead = head;//��¼�����ĵ�һ������λ��
	SListNode* cur = head->next;
	sortHead->next = NULL;
	while (cur)
	{
		SListNode* next = cur->next;
		SListNode* p = NULL;
		SListNode* c = sortHead;
		while (c)
		{
			if (cur->expon < c->expon)
			{
				break;
			}
			else
			{
				p = c;
				c = c->next;
			}
		}
		if (p == NULL)
		{
			cur->next = sortHead;
			sortHead = cur;
		}
		else
		{
			cur->next = c;
			p->next = cur;
		}
		cur = next;
	}
	return sortHead;
}

int Compare(SLTDataType e1, SLTDataType e2)
{
	if (e1 > e2)
		return 1;
	else if (e1 < e2)
		return -1;
	else
		return 0;
}

SListNode* PolyAdd(SListNode* P1, SListNode* P2)
{
	//SListNode* front = (SListNode*)malloc(sizeof(SListNode));
	//SListNode* tail = front;
	SListNode* front = NULL;
	while (P1&&P2)
	{
		switch (Compare(P1->expon, P2->expon))
		{
		case 1:
			SListPushBack(&front, P1->coef, P1->expon);
			P1 = P1->next;
			break;
		case -1:
			SListPushBack(&front, P2->coef, P2->expon);
			P2 = P2->next;
			break;
		case 0:
			SLTDataType sum = P1->coef + P2->coef;
			if (sum)
				SListPushBack(&front, sum, P1->expon);
			P1 = P1->next;
			P2 = P2->next;
			break;
		}
	}
	while (P1)
	{
		SListPushBack(&front, P1->coef, P1->expon);
		P1 = P1->next;
	}
	while (P2)
	{
		SListPushBack(&front, P2->coef, P2->expon);
		P2 = P2->next;
	}
	return front;
}