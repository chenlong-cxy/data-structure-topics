//给定一个链表，判断链表中是否有环。

#include <stdio.h>
#include <stdbool.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
bool hasCycle(struct ListNode *head) {
	struct ListNode* slow = head;
	struct ListNode* fast = head;
	while (fast && fast->next)
	{
		fast = fast->next->next;//兔子走两步
		slow = slow->next;//乌龟走一步
		if (fast == slow)//兔子与乌龟相遇
			return true;
	}
	return false;
}

//给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode *detectCycle(struct ListNode *head) {
	struct ListNode* fast = head;
	struct ListNode* slow = head;
	while (fast && fast->next)
	{
		slow = slow->next;//慢指针走一步
		fast = fast->next->next;//快指针走两步
		if (fast == slow)//相遇
		{
			struct ListNode* meet = fast;//相遇点
			while (head != meet)
			{
				head = head->next;//一个指针从出发点开始走
				meet = meet->next;//一个指针从相遇点开始走
			}
			return meet;//两个指针相遇，返回当前结点
		}
	}
	return NULL;//链表不带环
}