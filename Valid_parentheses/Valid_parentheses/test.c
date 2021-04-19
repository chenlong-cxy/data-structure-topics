//给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef char STDataType;//栈中存储的元素类型

typedef struct Stack
{
	STDataType* a;//栈
	int top;//栈顶
	int capacity;//容量，方便增容
}Stack;

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

//检测栈是否为空
bool StackEmpty(Stack* pst)
{
	assert(pst);

	return pst->top == 0;
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

//获取栈中有效元素个数
int StackSize(Stack* pst)
{
	assert(pst);

	return pst->top;//top的值便是栈中有效元素的个数
}

bool isValid(char * s){
	Stack st;//创建栈
	StackInit(&st);//初始化栈
	char* cur = s;
	while (*cur)//遍历字符串
	{
		if (*cur == '(' || *cur == '{' || *cur == '[')//前括号，压栈
		{
			StackPush(&st, *cur);
			cur++;
		}
		else//后括号
		{
			if (StackEmpty(&st))//栈为空，返回false
			{
				StackDestroy(&st);
				return false;
			}
			char top = StackTop(&st);
			if ((top == '('&&*cur != ')')
				|| (top == '{'&&*cur != '}')
				|| (top == '['&&*cur != ']'))//后括号未与栈顶位置的括号形式匹配
			{
				StackDestroy(&st);
				return false;
			}
			else//括号匹配
			{
				StackPop(&st);
				cur++;
			}
		}
	}
	bool ret = StackEmpty(&st);//栈是否为空
	StackDestroy(&st);
	return ret;//返回
}