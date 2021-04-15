//��������������ϲ�Ϊһ���µ� ���� �������ء���������ͨ��ƴ�Ӹ�����������������нڵ���ɵġ�

#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
	struct ListNode* guard = (struct ListNode*)malloc(sizeof(struct ListNode));//����һ��ͷ���
	struct ListNode* tail = guard;//βָ��
	struct ListNode* cur1 = l1;//��¼��ǰ��������l1����Ľ��λ��
	struct ListNode* cur2 = l2;//��¼��ǰ��������l2����Ľ��λ��
	while (cur1&&cur2)//��l1��l2����һ������������ʱ��ֹͣ
	{
		//ȡС�Ľ��β�嵽���������
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
		tail = tail->next;//������ӣ�βָ�����
	}
	//��δ������������ʣ����ӵ����������
	if (cur1)
		tail->next = cur1;
	else
		tail->next = cur2;

	struct ListNode* head = guard->next;//�������ͷָ��
	free(guard);//�ͷ�ͷ���
	return head;//����������
}