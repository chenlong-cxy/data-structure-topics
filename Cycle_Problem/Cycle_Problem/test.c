//����һ�������ж��������Ƿ��л���

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
		fast = fast->next->next;//����������
		slow = slow->next;//�ڹ���һ��
		if (fast == slow)//�������ڹ�����
			return true;
	}
	return false;
}

//����һ��������������ʼ�뻷�ĵ�һ���ڵ㡣 ��������޻����򷵻� null��

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
		slow = slow->next;//��ָ����һ��
		fast = fast->next->next;//��ָ��������
		if (fast == slow)//����
		{
			struct ListNode* meet = fast;//������
			while (head != meet)
			{
				head = head->next;//һ��ָ��ӳ����㿪ʼ��
				meet = meet->next;//һ��ָ��������㿪ʼ��
			}
			return meet;//����ָ�����������ص�ǰ���
		}
	}
	return NULL;//��������
}