//�����ʹ������ջʵ�������ȳ����С�
//����Ӧ��֧��һ�����֧�ֵ����в�����push��pop��peek��empty����

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int STDataType;//ջ�д洢��Ԫ������

typedef struct Stack
{
	STDataType* a;//ջ
	int top;//ջ��
	int capacity;//��������������
}Stack;

//��ʼ��ջ
void StackInit(Stack* pst)
{
	assert(pst);

	pst->a = (STDataType*)malloc(sizeof(STDataType)* 4);//��ʼ��ջ�ɴ洢4��Ԫ��
	pst->top = 0;//��ʼʱջ����Ԫ�أ�ջ��Ϊ0
	pst->capacity = 4;//����Ϊ4
}

//����ջ
void StackDestroy(Stack* pst)
{
	assert(pst);

	free(pst->a);//�ͷ�ջ
	pst->a = NULL;//��ʱ�ÿ�
	pst->top = 0;//ջ����0
	pst->capacity = 0;//������0
}

//��ջ
void StackPush(Stack* pst, STDataType x)
{
	assert(pst);

	if (pst->top == pst->capacity)//ջ������������
	{
		STDataType* tmp = (STDataType*)realloc(pst->a, sizeof(STDataType)*pst->capacity * 2);
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		pst->a = tmp;
		pst->capacity *= 2;//ջ��������Ϊԭ��������
	}
	pst->a[pst->top] = x;//ջ��λ�ô��Ԫ��x
	pst->top++;//ջ������
}

//���ջ�Ƿ�Ϊ��
bool StackEmpty(Stack* pst)
{
	assert(pst);

	return pst->top == 0;
}

//��ջ
void StackPop(Stack* pst)
{
	assert(pst);
	assert(!StackEmpty(pst));//���ջ�Ƿ�Ϊ��

	pst->top--;//ջ������
}

//��ȡջ��Ԫ��
STDataType StackTop(Stack* pst)
{
	assert(pst);
	assert(!StackEmpty(pst));//���ջ�Ƿ�Ϊ��

	return pst->a[pst->top - 1];//����ջ��Ԫ��
}

//��ȡջ����ЧԪ�ظ���
int StackSize(Stack* pst)
{
	assert(pst);

	return pst->top;//top��ֵ����ջ����ЧԪ�صĸ���
}
//-----------������ջ�Ļ�������ʵ�֣�������������岿��-----------
typedef struct {
	Stack pushST;//��������ʱ�õ�ջ
	Stack popST;//ɾ������ʱ�õ�ջ
} MyQueue;

/** Initialize your data structure here. */

MyQueue* myQueueCreate() {
	MyQueue* obj = (MyQueue*)malloc(sizeof(MyQueue));//����һ����������
	StackInit(&obj->pushST);//��ʼ��pushST
	StackInit(&obj->popST);//��ʼ��popST

	return obj;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
	StackPush(&obj->pushST, x);//�������ݣ���pushST����
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
	if (StackEmpty(&obj->popST))//popSTΪ��ʱ�����Ƚ�pushST�����ݵ���popST
	{
		while (!StackEmpty(&obj->pushST))//��pushST����ȫ������popST
		{
			StackPush(&obj->popST, StackTop(&obj->pushST));
			StackPop(&obj->pushST);
		}
	}
	return StackTop(&obj->popST);//����popSTջ����Ԫ��
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
	int top = myQueuePeek(obj);
	StackPop(&obj->popST);//ɾ�����ݣ�ɾ��popST��ջ����Ԫ��
	return top;
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
	return StackEmpty(&obj->pushST) && StackEmpty(&obj->popST);//����ջ��Ϊ�գ��򡰶��С�Ϊ��
}

void myQueueFree(MyQueue* obj) {
	//���ͷ�����ջ�����ͷŶ��еĽṹ������
	StackDestroy(&obj->pushST);
	StackDestroy(&obj->popST);
	free(obj);
}