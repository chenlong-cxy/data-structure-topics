//编写一个程序，找到两个单链表相交的起始节点

#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
	struct ListNode* curA = headA, *curB = headB;//用于遍历两个链表的指针
	int lenA = 0, lenB = 0;//记录链表长度
	//计算链表A的长度（实际是链表长度减一）
	while (curA->next)
	{
		lenA++;
		curA = curA->next;
	}
	//计算链表B的长度（实际是链表长度减一）
	while (curB->next)
	{
		lenB++;
		curB = curB->next;
	}
	//判断两个链表是否相交
	if (curA != curB)
		return NULL;

	struct ListNode* longlist = headA, *shortlist = headB;//用于寻找两个链表的起始相交结点的指针
	if (lenA < lenB)
	{
		longlist = headB;
		shortlist = headA;
	}
	int count = abs(lenA - lenB);//两个链表的结点数之差
	//让指向较长链表的指针先走count步
	while (count--)
	{
		longlist = longlist->next;
	}
	//然后两个指针同时向后移，若两个指针指向的结点地址相同，则该结点为链表相交的起始结点
	while (longlist != shortlist)
	{
		longlist = longlist->next;
		shortlist = shortlist->next;
	}
	return longlist;//返回链表相交的起始结点
}