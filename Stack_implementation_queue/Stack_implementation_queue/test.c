//请你仅使用两个栈实现先入先出队列。
//队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int STDataType;//栈中存储的元素类型

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
//-----------以上是栈的基本功能实现，以下是题解主体部分-----------
typedef struct {
	Stack pushST;//插入数据时用的栈
	Stack popST;//删除数据时用的栈
} MyQueue;

/** Initialize your data structure here. */

MyQueue* myQueueCreate() {
	MyQueue* obj = (MyQueue*)malloc(sizeof(MyQueue));//申请一个队列类型
	StackInit(&obj->pushST);//初始化pushST
	StackInit(&obj->popST);//初始化popST

	return obj;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
	StackPush(&obj->pushST, x);//插入数据，向pushST插入
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
	if (StackEmpty(&obj->popST))//popST为空时，需先将pushST中数据导入popST
	{
		while (!StackEmpty(&obj->pushST))//将pushST数据全部导入popST
		{
			StackPush(&obj->popST, StackTop(&obj->pushST));
			StackPop(&obj->pushST);
		}
	}
	return StackTop(&obj->popST);//返回popST栈顶的元素
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
	int top = myQueuePeek(obj);
	StackPop(&obj->popST);//删除数据，删除popST中栈顶的元素
	return top;
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
	return StackEmpty(&obj->pushST) && StackEmpty(&obj->popST);//两个栈均为空，则“队列”为空
}

void myQueueFree(MyQueue* obj) {
	//先释放两个栈，再释放队列的结构体类型
	StackDestroy(&obj->pushST);
	StackDestroy(&obj->popST);
	free(obj);
}