//����һ�����������һ��ʱ�临�Ӷ�ΪO(n), ����ռ临�Ӷ�ΪO(1)���㷨��
//�ж����Ƿ�Ϊ���Ľṹ��
//����һ�������ͷָ��A���뷵��һ��boolֵ���������Ƿ�Ϊ���Ľṹ��
//��֤������С�ڵ���900��

#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
}; 
class PalindromeList {
public:
	//����������м���
	struct ListNode* middleNode(struct ListNode* head)
	{
		struct ListNode* fast = head;//��ָ��
		struct ListNode* slow = head;//��ָ��
		while (fast&&fast->next)//��������������
		{
			slow = slow->next;//��ָ��һ����һ��
			fast = fast->next->next;//��ָ��һ��������
		}
		return slow;//������ָ��
	}
	//��ת����
	struct ListNode* reverseList(struct ListNode* head)
	{
		struct ListNode* cur = head;//��¼��ǰ��ͷ��Ľ��
		struct ListNode* newhead = NULL;//�������ʼʱΪ��
		while (cur)//�����н��ͷ�����ʱֹͣѭ��
		{
			struct ListNode* next = cur->next;//��¼��һ����ͷ��Ľ��
			cur->next = newhead;//�����ͷ����������
			newhead = cur;//������ͷָ�����
			cur = next;//ָ����һ����ͷ��Ľ��
		}
		return newhead;//���ط�ת���ͷָ��
	}
	bool chkPalindrome(ListNode* A) {
		ListNode* mid = middleNode(A);//����������м���
		ListNode* RHead = reverseList(mid);//��ת��������
		while (RHead)//�ȽϽ���������
		{
			if (A->val != RHead->val)//���ǻ��Ľṹ
				return false;
			A = A->next;//ָ�����
			RHead = RHead->next;//ָ�����
		}
		return true;//�ǻ��Ľṹ
	}
};