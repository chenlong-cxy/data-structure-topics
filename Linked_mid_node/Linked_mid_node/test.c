//������м���
//����һ��ͷ���Ϊ head �ķǿյ���������������м��㡣
//����������м��㣬�򷵻صڶ����м��㡣

#include <stdio.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode* middleNode(struct ListNode* head)
{
	struct ListNode* cur = head;//��¼��ǰ���λ��
	int count = 0;//��¼�����н�������
	while (cur)//������ֹͣ����
	{
		count++;//������һ
		cur = cur->next;//ָ�����
	}
	int mid = count / 2;//�м������һ�����֮�����Ľ����
	struct ListNode* midnode = head;//��¼�м����λ��
	while (mid--)//�ӵ�һ����㿪ʼ��ָ�����mid�����
	{
		midnode = midnode->next;//ָ�����
	}
	return midnode;//�����м���
}