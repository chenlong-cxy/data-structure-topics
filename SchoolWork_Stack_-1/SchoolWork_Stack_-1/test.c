#include "stack.h"

//ջ��-1����
void StackQuestion()
{
	Stack st;
	StackInit(&st);//��ʼ��ջ
	int input = 0;
	while (scanf("%d", &input) != EOF)//ѭ������
	{
		if (input != -1)//input������-1����ջ
		{
			StackPush(&st, input);
		}
		else//input����-1����ӡջ��Ԫ�ز���ջ
		{
			int output = StackTop(&st);//��ȡջ��Ԫ��
			printf("��ջԪ��Ϊ��%d\n", output);
			StackPop(&st);//��ջ
		}
	}

	StackDestroy(&st);//����ջ
}

int main()
{
	StackQuestion();
	return 0;
}