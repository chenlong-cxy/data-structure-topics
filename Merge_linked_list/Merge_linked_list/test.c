//将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
	struct ListNode* guard = (struct ListNode*)malloc(sizeof(struct ListNode));//申请一个头结点
	struct ListNode* tail = guard;//尾指针
	struct ListNode* cur1 = l1;//记录当前遍历到的l1链表的结点位置
	struct ListNode* cur2 = l2;//记录当前遍历到的l2链表的结点位置
	while (cur1&&cur2)//当l1，l2中有一个链表遍历完毕时便停止
	{
		//取小的结点尾插到新链表后面
		if (cur1->val < cur2->val)
		{
			tail->next = cur1;
			cur1 = cur1->next;
		}
		else
		{
			tail->next = cur2;
			cur2 = cur2->next;
		}
		tail = tail->next;//结点增加，尾指针后移
	}
	//将未遍历完的链表的剩余结点接到新链表后面
	if (cur1)
		tail->next = cur1;
	else
		tail->next = cur2;

	struct ListNode* head = guard->next;//新链表的头指针
	free(guard);//释放头结点
	return head;//返回新链表
}