#include "project.h"
//打印链表
//void SListPrint(SListNode* plist)
//{
//	SListNode* cur = plist;//接收头指针
//	while (cur != NULL)//判断链表是否打印完毕
//	{
//		printf("%d->", cur->data);//打印数据
//		cur = cur->next;//指针指向下一个结点
//	}
//	printf("NULL\n");//打印NULL，表明链表最后一个结点指向NULL
//}

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