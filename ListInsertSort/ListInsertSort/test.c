//对链表进行插入排序。
//插入排序的动画演示如上。从第一个元素开始，该链表可以被认为已经部分排序（用黑色表示）。
//每次迭代时，从输入数据中移除一个元素（用红色表示），并原地将其插入到已排好序的链表中。

#include <stdio.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* insertionSortList(struct ListNode* head)
{
	if (head == NULL || head->next == NULL)
		return head;

	struct ListNode* sortHead = head;
	struct ListNode* cur = head->next;
	sortHead->next = NULL;
	while (cur)
	{
		struct ListNode* next = cur->next;
		struct ListNode* p = NULL;
		struct ListNode* c = sortHead;
		while (c)
		{
			if (cur->val < c->val)
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