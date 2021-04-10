//给你一个链表的头节点 head 和一个整数 val ，
//请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点
//输入：head = [1, 2, 6, 3, 4, 5, 6], val = 6
//输出：[1, 2, 3, 4, 5]

#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode* removeElements(struct ListNode* head, int val)
{
	struct ListNode* prev = NULL;//记录待排查结点的前一个结点位置
	struct ListNode* cur = head;//记录当前正在排查的结点位置
	while (cur != NULL)//当cur为空时，循环停止
	{
		if (cur->val == val)//当前排查的结点是待移除的结点
		{
			struct ListNode* next = cur->next;//记录待排查结点的后一个结点位置
			if (cur == head)//待移除的结点是链表的第一个结点
			{
				head = next;//头指针指向next
				free(cur);//释放第一个结点
				cur = next;//将next指针赋值给cur指针
			}
			else//待移除的结点不是链表的第一个结点
			{
				prev->next = next;//prev指针指向的结点指向next
				free(cur);//将cur指针指向的结点释放掉
				cur = next;//将next指针赋值给cur指针
			}
		}
		else//当前排查的结点不是待移除的结点
		{
			prev = cur;//指针后移
			cur = cur->next;//指针后移
		}
	}
	return head;//返回新的头指针
}