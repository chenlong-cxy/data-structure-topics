//��������в�������
//��������Ķ�����ʾ���ϡ��ӵ�һ��Ԫ�ؿ�ʼ����������Ա���Ϊ�Ѿ����������ú�ɫ��ʾ����
//ÿ�ε���ʱ���������������Ƴ�һ��Ԫ�أ��ú�ɫ��ʾ������ԭ�ؽ�����뵽���ź���������С�

#include <stdio.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* insertionSortList(struct ListNode* head)
{
	if (head == NULL || head->next == NULL)
		return head;

	struct ListNode* sortHead = head;
	struct ListNode* cur = head->next;
	sortHead->next = NULL;
	while (cur)
	{
		struct ListNode* next = cur->next;
		struct ListNode* p = NULL;
		struct ListNode* c = sortHead;
		while (c)
		{
			if (cur->val < c->val)
			{
				break;
			}
			else
			{
				p = c;
				c = c->next;
			}
		}
		if (p == NULL)
		{
			cur->next = sortHead;
			sortHead = cur;
		}
		else
		{
			cur->next = c;
			p->next = cur;
		}
		cur = next;
	}
	return sortHead;
}