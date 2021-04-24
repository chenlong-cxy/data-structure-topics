#include "project.h"
//打印链表
void SListPrint(SListNode* plist)
{
	SListNode* cur = plist;
	if (cur)
	{
		printf("%dx^%d", cur->coef, cur->expon);//打印第一项
		cur = cur->next;
	}
	while (cur)
	{
		printf("%+dx^%d", cur->coef, cur->expon);
		cur = cur->next;
	}
	printf("\n");
}

//创建一个新结点，返回新结点地址
SListNode* BuySLTNode(SLTDataType coef, SLTDataType expon)
{
	SListNode* node = (SListNode*)malloc(sizeof(SListNode));//向新结点申请空间
	if (node == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	node->coef = coef;//系数赋值
	node->expon = expon;//指数赋值
	node->next = NULL;//将新结点的指针域置空
	return node;//返回新结点地址
}

//尾插
void SListPushBack(SListNode** pplist, SLTDataType coef, SLTDataType expon)
{
	SListNode* newnode = BuySLTNode(coef, expon);//申请一个新结点
	if (*pplist == NULL)//判断是否为空表
	{
		*pplist = newnode;//头指针直接指向新结点
	}
	else
	{
		SListNode* tail = *pplist;//接收头指针
		while (tail->next != NULL)//若某结点的指针域为NULL，说明它是最后一个结点
		{
			tail = tail->next;////指针指向下一个结点
		}
		tail->next = newnode;//让最后一个结点的指针域指向新结点
	}
}

//选择排序
SListNode* InsertSortList(SListNode* head)
{
	if (head == NULL || head->next == NULL)//若链表为空或链表只有一个结点，则不需排序
		return head;

	SListNode* sortHead = head;//记录排序后的第一个结点的位置
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