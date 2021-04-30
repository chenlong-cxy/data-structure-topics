#include "DStack.h"

//双栈初始化
void DblStackInit(DblStack* pds)
{
	assert(pds);//断言，判断指针有效性

	pds->m = 10;//栈最大可容纳元素个数
	SElemType* tmp = (SElemType*)malloc(sizeof(SElemType)*pds->m);
	if (tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	pds->V = tmp;
	pds->bot[0] = -1;//第一个栈底为-1
	pds->bot[1] = pds->m;//第二个栈底为m
	pds->top[0] = -1;//第一个栈顶初始为-1
	pds->top[1] = pds->m;//第二个栈顶初始为m
}

//判断栈空
void DblStackEmpty(DblStack* pds)
{
	assert(pds);//断言，判断指针有效性

	if (pds->top[0] == -1)
	{
		printf("堆栈1空\n");
	}
	if (pds->top[1] == pds->m)
	{
		printf("堆栈2空\n");
	}
}

//判断栈满
bool DblStackFull(DblStack* pds)
{
	assert(pds);//断言，判断指针有效性

	return pds->top[1] - pds->top[0] == 1;
}

//进栈
void DblStackPush(DblStack* pds, int tag, SElemType x)
{
	assert(pds);//断言，判断指针有效性
	assert(!DblStackFull(pds));//栈满，无法进栈

	if (tag == 1)//入第一个栈
	{
		pds->top[0]++;
		pds->V[pds->top[0]] = x;
	}
	else//入第二个栈
	{
		pds->top[1]--;
		pds->V[pds->top[1]] = x;
	}
}

//出栈
SElemType DblStackPop(DblStack*pds, int tag)
{
	assert(pds);//断言，判断指针有效性

	if (tag == 1)//第一个栈出数据
	{
		if (pds->top[0] == -1)
		{
			printf("堆栈1空\n");
			exit(-1);
		}
		return pds->V[pds->top[0]--];
	}
	else//第二个栈出数据
	{
		if (pds->top[1] == pds->m)
		{
			printf("堆栈2空\n");
			exit(-1);
		}
		return pds->V[pds->top[1]++];
	}
}

//打印
void DblStackPrint(DblStack* pds)
{
	assert(pds);

	int i = 0;
	for (i = 0; i < pds->m; i++)
	{
		printf("%d ", pds->V[i]);
	}
	printf("\n");
}