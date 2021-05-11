#include "stack.h"

//初始化栈
void StackInit(Stack* pst)
{
	assert(pst);

	pst->a = (STDataType*)malloc(sizeof(STDataType)* 4);//初始化栈可存储4个元素
	pst->top = 0;//初始时栈中无元素，栈顶为0
	pst->capacity = 4;//容量为4
}

//销毁栈
void StackDestroy(Stack* pst)
{
	assert(pst);

	free(pst->a);//释放栈
	pst->a = NULL;//及时置空
	pst->top = 0;//栈顶置0
	pst->capacity = 0;//容量置0
}

//入栈
void StackPush(Stack* pst, STDataType x)
{
	assert(pst);

	if (pst->top == pst->capacity)//栈已满，需扩容
	{
		STDataType* tmp = (STDataType*)realloc(pst->a, sizeof(STDataType)*pst->capacity * 2);
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		pst->a = tmp;
		pst->capacity *= 2;//栈容量扩大为原来的两倍
	}
	pst->a[pst->top] = x;//栈顶位置存放元素x
	pst->top++;//栈顶上移
}

//出栈
void StackPop(Stack* pst)
{
	assert(pst);
	assert(!StackEmpty(pst));//检测栈是否为空

	pst->top--;//栈顶下移
}

//获取栈顶元素
STDataType StackTop(Stack* pst)
{
	assert(pst);
	assert(!StackEmpty(pst));//检测栈是否为空

	return pst->a[pst->top - 1];//返回栈顶元素
}

//检测栈是否为空
bool StackEmpty(Stack* pst)
{
	assert(pst);

	return pst->top == 0;
}

//获取栈中有效元素个数
int StackSize(Stack* pst)
{
	assert(pst);

	return pst->top;//top的值便是栈中有效元素的个数
}

//判断出入序列是否为回文结构
bool Judgearray(char* arr)
{
	int sz = strlen(arr);
	int count = sz / 2;
	Stack st;//创建一个栈
	StackInit(&st);//初始化栈
	int i = 0;
	for (i = 0; i < count; i++)//前半入栈
	{
		StackPush(&st, *(arr + i));
	}
	int start = sz / 2;//找到后半部分的开头
	if (sz % 2 != 0)
	{
		start++;//若序列的大小为奇数，则从后半部分从sz/2+1处开始与前半部分比较
	}
	while (*(arr + start))//当字符串未比较完毕，即start为走到'\0'，继续比较
	{
		if (StackTop(&st) != *(arr + start))//栈顶的元素与start位置的字符不匹配
			return false;//不是回文
		StackPop(&st);//删除栈顶元素，下比较下一个元素
		start++;//准备与后半部分的后一个元素比较
	}
	StackDestroy(&st);//销毁栈
	return true;//是回文
}