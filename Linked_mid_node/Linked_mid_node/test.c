//链表的中间结点
//给定一个头结点为 head 的非空单链表，返回链表的中间结点。
//如果有两个中间结点，则返回第二个中间结点。

//#include <stdio.h>
//struct ListNode {
//	int val;
//	struct ListNode *next;
//};
//struct ListNode* middleNode(struct ListNode* head)
//{
//	struct ListNode* cur = head;//记录当前结点位置
//	int count = 0;//记录链表中结点的总数
//	while (cur)//遍历的停止条件
//	{
//		count++;//总数加一
//		cur = cur->next;//指针后移
//	}
//	int mid = count / 2;//中间结点与第一个结点之间相差的结点数
//	struct ListNode* midnode = head;//记录中间结点的位置
//	while (mid--)//从第一个结点开始，指针后移mid个结点
//	{
//		midnode = midnode->next;//指针后移
//	}
//	return midnode;//返回中间结点
//}


#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode* middleNode(struct ListNode* head)
{
	struct ListNode* fast = head;//快指针
	struct ListNode* slow = head;//慢指针
	while (fast&&fast->next)//遍历继续的条件
	{
		slow = slow->next;//慢指针一次走一步
		fast = fast->next->next;//快指针一次走两步
	}
	return slow;//返回慢指针
}