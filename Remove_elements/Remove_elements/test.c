//����һ�������ͷ�ڵ� head ��һ������ val ��
//����ɾ���������������� Node.val == val �Ľڵ㣬������ �µ�ͷ�ڵ�
//���룺head = [1, 2, 6, 3, 4, 5, 6], val = 6
//�����[1, 2, 3, 4, 5]

//˼·һ
//#include <stdio.h>
//struct ListNode {
//	int val;
//	struct ListNode *next;
//};
//struct ListNode* removeElements(struct ListNode* head, int val)
//{
//	struct ListNode* prev = NULL;//��¼���Ų����ǰһ�����λ��
//	struct ListNode* cur = head;//��¼��ǰ�����Ų�Ľ��λ��
//	while (cur != NULL)//��curΪ��ʱ��ѭ��ֹͣ
//	{
//		if (cur->val == val)//��ǰ�Ų�Ľ���Ǵ��Ƴ��Ľ��
//		{
//			struct ListNode* next = cur->next;//��¼���Ų���ĺ�һ�����λ��
//			if (cur == head)//���Ƴ��Ľ��������ĵ�һ�����
//			{
//				head = next;//ͷָ��ָ��next
//				free(cur);//�ͷŵ�һ�����
//				cur = next;//��nextָ�븳ֵ��curָ��
//			}
//			else//���Ƴ��Ľ�㲻������ĵ�һ�����
//			{
//				prev->next = next;//prevָ��ָ��Ľ��ָ��next
//				free(cur);//��curָ��ָ��Ľ���ͷŵ�
//				cur = next;//��nextָ�븳ֵ��curָ��
//			}
//		}
//		else//��ǰ�Ų�Ľ�㲻�Ǵ��Ƴ��Ľ��
//		{
//			prev = cur;//ָ�����
//			cur = cur->next;//ָ�����
//		}
//	}
//	return head;//�����µ�ͷָ��
//}


//˼·��
#include <stdio.h>
#include <stdlib.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode* removeElements(struct ListNode* head, int val)
{
	struct ListNode* guard = (struct ListNode*)malloc(sizeof(struct ListNode));//����һ��ͷ��㣬�������ַ
	guard->next = head;//��ͷ���ָ������ĵ�һ�����
	struct ListNode* cur = guard->next;//curָ��ָ��ԭ�����һ�����
	struct ListNode* prev = guard;//prevָ��ָ��ͷ���
	while (cur != NULL)//��curΪ��ʱ��ѭ��ֹͣ
	{
		if (cur->val == val)//��ǰ�Ų�Ľ���Ǵ��Ƴ��Ľ��
		{
			struct ListNode* next = cur->next;//��¼���Ų���ĺ�һ�����λ��
			prev->next = next;//prevָ��ָ��Ľ��ָ��next
			free(cur);//��curָ��ָ��Ľ���ͷŵ�
			cur = next;//��nextָ�븳ֵ��curָ��
		}
		else//��ǰ�Ų�Ľ�㲻�Ǵ��Ƴ��Ľ��
		{
			prev = cur;//ָ�����
			cur = cur->next;//ָ�����
		}
	}
	head = guard->next;//��ͷ���ָ���λ�ø�ֵ��ͷָ�룬ʹͷָ��ָ�������һ�����
	free(guard);//�ͷ�ͷ���
	guard = NULL;//��ʱ�ÿ�
	return head;//�����µ�ͷָ��
}