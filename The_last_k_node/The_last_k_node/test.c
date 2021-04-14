//输入一个链表，输出该链表中倒数第k个结点

//#include <stdio.h>
//struct ListNode {
//	int val;
//	struct ListNode *next;
//};
//struct ListNode* FindKthToTail(struct ListNode* pListHead, int k)
//{
//	if (pListHead == NULL)//判断链表是否为空
//		return NULL;
//	struct ListNode* cur = pListHead;//记录当前结点位置
//	int count = 0;//记录链表的总结点数
//	while (cur)
//	{
//		count++;//结点总数加一
//		cur = cur->next;//指针后移
//	}
//	if (count < k)//count小于k，此时不存在倒数第k个结点
//		return NULL;
//	struct ListNode* ret = pListHead;
//	int pos = count - k;//倒数第k个结点距离第一个结点的结点数
//	while (pos--)
//	{
//		ret = ret->next;//指针后移
//	}
//	return ret;//返回目标结点
//}


#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode* FindKthToTail(struct ListNode* pListHead, int k)
{
	struct ListNode* fast = pListHead;//快指针
	struct ListNode* slow = pListHead;//慢指针
	while (k--)//快指针先向后移动k步
	{
		if (fast == NULL)//快指针移动过程中链表遍历结束，不存在倒数第k个结点
			return NULL;
		fast = fast->next;//快指针后移
	}
	while (fast)//快指针遍历完链表时结束遍历
	{
		fast = fast->next;//快指针后移
		slow = slow->next;//慢指针后移
	}
	return slow;//返回慢指针的值
}