//����һ�����ͷָ�� ListNode* pHead����һ��ֵx��
//��дһ�δ��뽫����С��x�Ľ������������֮ǰ��
//�Ҳ��ܸı�ԭ��������˳�򣬷����������к�������ͷָ�롣

#include <stdio.h>
#include <stdlib.h>
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) : val(x), next(NULL) {}
};
class Partition {
public:
	ListNode* partition(ListNode* pHead, int x) {
		ListNode* greaterHead, *greaterTail, *lessHead, *lessTail;
		//����һ��ͷ��㣬�������Ӵ���x�Ľ��
		greaterHead = greaterTail = (ListNode*)malloc(sizeof(struct ListNode));
		//����һ��ͷ��㣬��������С��x�Ľ��
		lessHead = lessTail = (ListNode*)malloc(sizeof(struct ListNode));
		greaterTail->next = NULL;//βָ���ָ�����ÿ�
		lessTail->next = NULL;//βָ���ָ�����ÿ�
		ListNode* cur = pHead;//���մ��������׼������
		while (cur)
		{
			if (cur->val < x)
			{
				//���ֵС��x�����ӵ�less�������
				lessTail->next = cur;
				lessTail = lessTail->next;
			}
			else
			{
				//���ֵ����x�����ӵ�greater�������
				greaterTail->next = cur;
				greaterTail = greaterTail->next;
			}
			cur = cur->next;//ָ����ƣ���������Ľ��
		}
		//��less�����greater������������
		lessTail->next = greaterHead->next;//greater����ĵ�һ��������ӵ�less�����β��
		greaterTail->next = NULL;//��greater�������һ������ָ�����ÿ�
		ListNode* head = lessHead->next;//�������Ӻ�����ĵ�һ������ַ
		free(greaterHead);//�ͷ�greater�����ͷ���
		free(lessHead);//�ͷ�less�����ͷ���
		return head;//����������
	}
};
void Print(ListNode* pHead)
{
	ListNode* cur = pHead;
	while (cur)
	{
		printf("%d->", cur->val);
		cur = cur->next;
	}
	printf("NULL\n");
}
int main()
{
	ListNode* node1 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node2 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node3 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node4 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node5 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node6 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node7 = (ListNode*)malloc(sizeof(struct ListNode));
	ListNode* node8 = (ListNode*)malloc(sizeof(struct ListNode));

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = node7;
	node7->next = node8;
	node8->next = NULL;

	node1->val = 2;
	node2->val = 4;
	node3->val = 9;
	node4->val = 3;
	node5->val = 2;
	node6->val = 1;
	node7->val = 6;
	node8->val = 3;

	Print(node1);
	ListNode* head = Partition().partition(node1, 5);
	Print(head);
	return 0;
}