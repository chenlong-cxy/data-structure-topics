//对于一个链表，请设计一个时间复杂度为O(n), 额外空间复杂度为O(1)的算法，
//判断其是否为回文结构。
//给定一个链表的头指针A，请返回一个bool值，代表其是否为回文结构。
//保证链表长度小于等于900。

#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
}; 
class PalindromeList {
public:
	//查找链表的中间结点
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
	//反转链表
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
	bool chkPalindrome(ListNode* A) {
		ListNode* mid = middleNode(A);//查找链表的中间结点
		ListNode* RHead = reverseList(mid);//反转后半段链表
		while (RHead)//比较结束的条件
		{
			if (A->val != RHead->val)//不是回文结构
				return false;
			A = A->next;//指针后移
			RHead = RHead->next;//指针后移
		}
		return true;//是回文结构
	}
};