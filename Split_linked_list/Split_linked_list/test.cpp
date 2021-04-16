//现有一链表的头指针 ListNode* pHead，给一定值x，
//编写一段代码将所有小于x的结点排在其余结点之前，
//且不能改变原来的数据顺序，返回重新排列后的链表的头指针。

#include <stdio.h>
#include <stdlib.h>
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) : val(x), next(NULL) {}
};
class Partition {
public:
	ListNode* partition(ListNode* pHead, int x) {
		ListNode* greaterHead, *greaterTail, *lessHead, *lessTail;
		//申请一个头结点，后面链接大于x的结点
		greaterHead = greaterTail = (ListNode*)malloc(sizeof(struct ListNode));
		//申请一个头结点，后面链接小于x的结点
		lessHead = lessTail = (ListNode*)malloc(sizeof(struct ListNode));
		greaterTail->next = NULL;//尾指针的指针域置空
		lessTail->next = NULL;//尾指针的指针域置空
		ListNode* cur = pHead;//接收传入的链表，准备遍历
		while (cur)
		{
			if (cur->val < x)
			{
				//结点值小于x，链接到less链表后面
				lessTail->next = cur;
				lessTail = lessTail->next;
			}
			else
			{
				//结点值大于x，链接到greater链表后面
				greaterTail->next = cur;
				greaterTail = greaterTail->next;
			}
			cur = cur->next;//指针后移，遍历后面的结点
		}
		//将less链表和greater链表链接起来
		lessTail->next = greaterHead->next;//greater链表的第一个结点链接到less链表的尾上
		greaterTail->next = NULL;//将greater链表最后一个结点的指针域置空
		ListNode* head = lessHead->next;//接收链接后链表的第一个结点地址
		free(greaterHead);//释放greater链表的头结点
		free(lessHead);//释放less链表的头结点
		return head;//返回新链表
	}
};
void Print(ListNode* pHead)
{
	ListNode* cur = pHead;
	while (cur)
	{
		printf("%d->", cur->val);
		cur = cur->next;
	}
	printf("NULL\n");
}
int main()
{
	ListNode* node1 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node2 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node3 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node4 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node5 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node6 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node7 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node8 = (ListNode*)malloc(sizeof(struct ListNode));

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = node7;
	node7->next = node8;
	node8->next = NULL;

	node1->val = 2;
	node2->val = 4;
	node3->val = 9;
	node4->val = 3;
	node5->val = 2;
	node6->val = 1;
	node7->val = 6;
	node8->val = 3;

	Print(node1);
	ListNode* head = Partition().partition(node1, 5);
	Print(head);
	return 0;
}