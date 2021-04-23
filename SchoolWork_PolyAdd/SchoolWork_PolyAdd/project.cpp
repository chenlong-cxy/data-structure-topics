#include "project.h"
//��ӡ����
//void SListPrint(SListNode* plist)
//{
//	SListNode* cur = plist;//����ͷָ��
//	while (cur != NULL)//�ж������Ƿ��ӡ���
//	{
//		printf("%d->", cur->data);//��ӡ����
//		cur = cur->next;//ָ��ָ����һ�����
//	}
//	printf("NULL\n");//��ӡNULL�������������һ�����ָ��NULL
//}

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