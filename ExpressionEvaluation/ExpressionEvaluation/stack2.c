#include "stack2.h"

//��ʼ��ջ
void StackInit2(Stack2* pst)
{
	assert(pst);

	pst->a = (STDataType2*)malloc(sizeof(STDataType2)* 4);//��ʼ��ջ�ɴ洢4��Ԫ��
	pst->top = 0;//��ʼʱջ����Ԫ�أ�ջ��Ϊ0
	pst->capacity = 4;//����Ϊ4
}

//����ջ
void StackDestroy2(Stack2* pst)
{
	assert(pst);

	free(pst->a);//�ͷ�ջ
	pst->a = NULL;//��ʱ�ÿ�
	pst->top = 0;//ջ����0
	pst->capacity = 0;//������0
}

//��ջ
void StackPush2(Stack2* pst, STDataType2 x)
{
	assert(pst);

	if (pst->top == pst->capacity)//ջ������������
	{
		STDataType2* tmp = (STDataType2*)realloc(pst->a, sizeof(STDataType2)*pst->capacity * 2);
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

//��ջ
void StackPop2(Stack2* pst)
{
	assert(pst);
	assert(!StackEmpty2(pst));//���ջ�Ƿ�Ϊ��

	pst->top--;//ջ������
}

//��ȡջ��Ԫ��
STDataType2 StackTop2(Stack2* pst)
{
	assert(pst);
	assert(!StackEmpty2(pst));//���ջ�Ƿ�Ϊ��

	return pst->a[pst->top - 1];//����ջ��Ԫ��
}

//���ջ�Ƿ�Ϊ��
bool StackEmpty2(Stack2* pst)
{
	assert(pst);

	return pst->top == 0;
}

//��ȡջ����ЧԪ�ظ���
int StackSize2(Stack2* pst)
{
	assert(pst);

	return pst->top;//top��ֵ����ջ����ЧԪ�صĸ���
}