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