#include "SList.h"

//求链表中的最大整数
int SListMax(SListNode* plist)
{
	if (plist == NULL)//递归的终止条件
		return 0;
	int nextMax = SListMax(plist->next);//寻找plist->next链表中的最大值（子问题）
	//返回当前值和plist->next链表中的最大值中较大的值
	return plist->data > nextMax ? plist->data : nextMax;
}
//求链表的结点个数
int SListSize(SListNode* plist)
{
	if (plist == NULL)//递归的终止条件
		return 0;
	return 1 + SListSize(plist->next);//返回1+后面链表的结点总数（子问题）
}
//求所有整数的平均值
double SListAverage(SListNode* plist)
{
	static double sum = 0.0;//统计结点数据和
	static double count = 0.0;//统计结点个数
	if (plist->next == NULL)//递归的终止条件
	{
		return (sum + plist->data) / (count + 1);//返回平均值
	}
	sum = sum + plist->data;//结点数据和更新
	count++;//结点个数更新
	return SListAverage(plist->next);//递归
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
	printf("链表内数据为:");
	SListPrint(plist);
	printf("链表中的最大整数为：%d\n", SListMax(plist));
	printf("链表的结点个数为：%d\n", SListSize(plist));
	printf("链表所有整数的平均值为：%lf\n", SListAverage(plist));
	return 0;
}