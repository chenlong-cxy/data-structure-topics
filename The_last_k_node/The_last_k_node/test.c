//����һ����������������е�����k�����

//#include <stdio.h>
//struct ListNode {
//	int val;
//	struct ListNode *next;
//};
//struct ListNode* FindKthToTail(struct ListNode* pListHead, int k)
//{
//	if (pListHead == NULL)//�ж������Ƿ�Ϊ��
//		return NULL;
//	struct ListNode* cur = pListHead;//��¼��ǰ���λ��
//	int count = 0;//��¼������ܽ����
//	while (cur)
//	{
//		count++;//���������һ
//		cur = cur->next;//ָ�����
//	}
//	if (count < k)//countС��k����ʱ�����ڵ�����k�����
//		return NULL;
//	struct ListNode* ret = pListHead;
//	int pos = count - k;//������k���������һ�����Ľ����
//	while (pos--)
//	{
//		ret = ret->next;//ָ�����
//	}
//	return ret;//����Ŀ����
//}


#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode* FindKthToTail(struct ListNode* pListHead, int k)
{
	struct ListNode* fast = pListHead;//��ָ��
	struct ListNode* slow = pListHead;//��ָ��
	while (k--)//��ָ��������ƶ�k��
	{
		if (fast == NULL)//��ָ���ƶ�������������������������ڵ�����k�����
			return NULL;
		fast = fast->next;//��ָ�����
	}
	while (fast)//��ָ�����������ʱ��������
	{
		fast = fast->next;//��ָ�����
		slow = slow->next;//��ָ�����
	}
	return slow;//������ָ���ֵ
}