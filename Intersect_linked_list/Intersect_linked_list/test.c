//��дһ�������ҵ������������ཻ����ʼ�ڵ�

#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
	struct ListNode* curA = headA, *curB = headB;//���ڱ������������ָ��
	int lenA = 0, lenB = 0;//��¼������
	//��������A�ĳ��ȣ�ʵ���������ȼ�һ��
	while (curA->next)
	{
		lenA++;
		curA = curA->next;
	}
	//��������B�ĳ��ȣ�ʵ���������ȼ�һ��
	while (curB->next)
	{
		lenB++;
		curB = curB->next;
	}
	//�ж����������Ƿ��ཻ
	if (curA != curB)
		return NULL;

	struct ListNode* longlist = headA, *shortlist = headB;//����Ѱ�������������ʼ�ཻ����ָ��
	if (lenA < lenB)
	{
		longlist = headB;
		shortlist = headA;
	}
	int count = abs(lenA - lenB);//��������Ľ����֮��
	//��ָ��ϳ������ָ������count��
	while (count--)
	{
		longlist = longlist->next;
	}
	//Ȼ������ָ��ͬʱ����ƣ�������ָ��ָ��Ľ���ַ��ͬ����ý��Ϊ�����ཻ����ʼ���
	while (longlist != shortlist)
	{
		longlist = longlist->next;
		shortlist = shortlist->next;
	}
	return longlist;//���������ཻ����ʼ���
}