#include "project.h"

//打印多项式
void SListPrint(SListNode* head)
{
	SListNode* cur = head;
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
void SListPushBack(SListNode** pHead, SLTDataType coef, SLTDataType expon)
{
	SListNode* newnode = BuySLTNode(coef, expon);//申请一个新结点
	if (*pHead == NULL)//判断是否为空表
	{
		*pHead = newnode;//头指针直接指向新结点
	}
	else
	{
		SListNode* tail = *pHead;//接收头指针
		while (tail->next != NULL)//若某结点的指针域为NULL，说明它是最后一个结点
		{
			tail = tail->next;////指针指向下一个结点
		}
		tail->next = newnode;//让最后一个结点的指针域指向新结点
	}
}

//插入排序
SListNode* InsertSortList(SListNode* head)
{
	if (head == NULL || head->next == NULL)//若链表为空或链表只有一个结点，则不需排序
		return head;

	SListNode* sortHead = head;//记录排序后链表的第一个结点
	SListNode* cur = head->next;//从待排链表的第二个结点开始排序
	sortHead->next = NULL;//默认链表的第一个结点有序，设置其指针域为空
	while (cur)
	{
		SListNode* next = cur->next;//记录当前正在排序的结点的下一个结点
		SListNode* c = sortHead;//记录当前遍历到的有序链表的结点位置
		SListNode* p = NULL;//记录c的前一个结点位置
		while (c)
		{
			if (cur->expon > c->expon)//待插入结点的指数大于当前遍历到的有序链表的结点的指数
			{
				break;
			}
			else//待插入结点与有序链表中的下一个结点比较
			{
				p = c;
				c = c->next;
			}
		}
		if (p == NULL)//将待插入结点插入到有序链表的第一个位置
		{
			cur->next = sortHead;
			sortHead = cur;
		}
		else//将待插入结点插入到p和c之间
		{
			cur->next = c;
			p->next = cur;
		}
		cur = next;//插入下一个待插入结点
	}
	return sortHead;//返回排列好的链表
}

//比较两个结点的指数大小
int Compare(SLTDataType e1, SLTDataType e2)
{
	if (e1 > e2)
		return 1;
	else if (e1 < e2)
		return -1;
	else
		return 0;
}

//多项式相加
SListNode* PolyAdd(SListNode* P1, SListNode* P2)
{
	//SListNode* front = (SListNode*)malloc(sizeof(SListNode));
	//SListNode* tail = front;
	SListNode* front = NULL;//相加后的链表的头指针
	while (P1&&P2)
	{
		switch (Compare(P1->expon, P2->expon))//比较指数
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
	while (P1)//将P1剩余项尾插到链表后面
	{
		SListPushBack(&front, P1->coef, P1->expon);
		P1 = P1->next;
	}
	while (P2)//将P2剩余项尾插到链表后面
	{
		SListPushBack(&front, P2->coef, P2->expon);
		P2 = P2->next;
	}
	return front;//返回新链表
}