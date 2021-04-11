//��תһ��������
//����: 1->2->3->4->5->NULL
//��� : 5->4->3->2->1->NULL

//#include <stdio.h>
//struct ListNode {
//	int val;
//	struct ListNode *next;
//};
//struct ListNode* reverseList(struct ListNode* head)
//{
//	if (head == NULL || head->next == NULL)//������Ϊ�ջ�ֻ��һ�����ʱ���������
//		return head;//ֱ�ӷ���
//
//	struct ListNode* n1 = NULL;//��¼ָ��ָ��Ҫ��ת�Ľ�㷴ת��Ҫָ���λ�á�
//	struct ListNode* n2 = head;//��¼ָ��ָ��Ҫ��ת�Ľ�㡣
//	struct ListNode* n3 = head->next;//��¼ָ��ָ��Ҫ��ת�Ľ�����һ����㡣
//	while (n2)//n2ΪNULLʱ��ֹͣ����
//	{
//		n2->next = n1;//��ת���ָ��
//		n1 = n2;//ָ�����
//		n2 = n3;//ָ�����
//		if (n3)//�ж�n3�Ƿ�ΪNULL
//			n3 = n3->next;//ָ�����
//	}
//	return n1;//����n1ָ��ָ���λ��
//}


#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
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