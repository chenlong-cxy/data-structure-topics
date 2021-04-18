#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef int STDataType;//栈中存储的元素类型（这里用整型举例）

typedef struct Stack
{
	STDataType* a;//栈
	int top;//栈顶
	int capacity;//容量，方便增容
}Stack;

//初始化栈
void StackInit(Stack* pst);
//销毁栈
void StackDestroy(Stack* pst);

//入栈
void StackPush(Stack* pst, STDataType x);
//出栈
void StackPop(Stack* pst);

//获取栈顶元素
STDataType StackTop(Stack* pst);
//检测栈是否为空
bool StackEmpty(Stack* pst);
//获取栈中有效元素个数
int StackSize(Stack* pst);