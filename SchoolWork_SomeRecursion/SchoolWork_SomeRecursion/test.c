#include "SList.h"

//�������е��������
int SListMax(SListNode* plist)
{
	if (plist == NULL)//�ݹ����ֹ����
		return 0;
	int nextMax = SListMax(plist->next);//Ѱ��plist->next�����е����ֵ�������⣩
	//���ص�ǰֵ��plist->next�����е����ֵ�нϴ��ֵ
	return plist->data > nextMax ? plist->data : nextMax;
}
//������Ľ�����
int SListSize(SListNode* plist)
{
	if (plist == NULL)//�ݹ����ֹ����
		return 0;
	return 1 + SListSize(plist->next);//����1+��������Ľ�������������⣩
}
//������������ƽ��ֵ
double SListAverage(SListNode* plist)
{
	static double sum = 0.0;//ͳ�ƽ�����ݺ�
	static double count = 0.0;//ͳ�ƽ�����
	if (plist->next == NULL)//�ݹ����ֹ����
	{
		return (sum + plist->data) / (count + 1);//����ƽ��ֵ
	}
	sum = sum + plist->data;//������ݺ͸���
	count++;//����������
	return SListAverage(plist->next);//�ݹ�
}

int main()
{
	SListNode* plist = NULL;
	SListPushBack(&plist, 3);
	SListPushBack(&plist, 34);
	SListPushBack(&plist, 54);
	SListPushBack(&plist, 67);
	SListPushBack(&plist, 37);
	SListPushBack(&plist, 50);
	SListPushBack(&plist, 8);
	SListPushBack(&plist, 94);
	SListPushBack(&plist, 93);
	SListPushBack(&plist, 56);
	printf("����������Ϊ:");
	SListPrint(plist);
	printf("�����е��������Ϊ��%d\n", SListMax(plist));
	printf("����Ľ�����Ϊ��%d\n", SListSize(plist));
	printf("��������������ƽ��ֵΪ��%lf\n", SListAverage(plist));
	return 0;
}