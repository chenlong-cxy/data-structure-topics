//反转一个单链表。
//输入: 1->2->3->4->5->NULL
//输出 : 5->4->3->2->1->NULL

//#include <stdio.h>
//struct ListNode {
//	int val;
//	struct ListNode *next;
//};
//struct ListNode* reverseList(struct ListNode* head)
//{
//	if (head == NULL || head->next == NULL)//当链表为空或只有一个结点时，无需操作
//		return head;//直接返回
//
//	struct ListNode* n1 = NULL;//记录指针指向将要反转的结点反转后要指向的位置。
//	struct ListNode* n2 = head;//记录指针指向将要反转的结点。
//	struct ListNode* n3 = head->next;//记录指针指向将要反转的结点的下一个结点。
//	while (n2)//n2为NULL时，停止遍历
//	{
//		n2->next = n1;//反转结点指向
//		n1 = n2;//指针后移
//		n2 = n3;//指针后移
//		if (n3)//判断n3是否为NULL
//			n3 = n3->next;//指针后移
//	}
//	return n1;//返回n1指针指向的位置
//}


#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode* reverseList(struct ListNode* head)
{
	struct ListNode* cur = head;//记录当前待头插的结点
	struct ListNode* newhead = NULL;//新链表初始时为空
	while (cur)//链表中结点头插完毕时停止循环
	{
		struct ListNode* next = cur->next;//记录下一个待头插的结点
		cur->next = newhead;//将结点头插至新链表
		newhead = cur;//新链表头指针后移
		cur = next;//指向下一个待头插的结点
	}
	return newhead;//返回反转后的头指针
}