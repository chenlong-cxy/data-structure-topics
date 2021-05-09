#define _CRT_SECURE_NO_WARNINGS 1
#define STACK_INIT_SIZE 100   //ջ�ĳ�ʼ�ռ��С  
#define STACKINCREAMENT 10    //���ӿռ�
#define MaxSize 100
#include <stdio.h>
#include <stdlib.h>


/*�������Ͷ���*/
typedef int Position;
typedef int SElemType;
struct SNode {
	SElemType Data[MaxSize]; /* �洢Ԫ�ص����� */
	Position Top;            /* ջ��ָ�� */
};
typedef struct SNode *Stack;
//����Ϊ˳��ջ��������
/*����һ����ջ*/
Stack CreateStack()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Top = -1;
	return S;
}

/*ջ���пպ���*/
int IsEmpty(Stack S)
{
	return (S->Top == -1);
}

/*��ջ*/
int Push(Stack S, SElemType X)
{
	if (S->Top == MaxSize - 1) {
		printf("��ջ��");
		return -1;//ʧ�ܷ���
	}
	else {
		//��д��Ӧ����䡣
		S->Data[++S->Top] = X;
		return 0;//�ɹ�����
	}
}


/*��ջ*/
SElemType Pop(Stack S)
{
	//��д��Ӧ����䡣
	if (IsEmpty(S))
	{
		printf("��ջ��\n");
		exit(-1);
	}
	return S->Data[S->Top--];
}

void convert(Stack S, int N, int n)
{
	//��д��Ӧ����䡣
	while (N)
	{
		Push(S, N%n);//������ջ
		N = N / n;
	}
	printf("��%dת��Ϊ%d������Ϊ��", N, n);
	while (!IsEmpty(S))
	{
		printf("%d", Pop(S));//���γ�ջ
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	/*���Ƶ�ת������*/
	int n, N;//Ҫת���ɵĽ�������Ҫת������  

	//��ʼ����ջ  
	Stack S = CreateStack();

	printf("��������Ҫʮ��������");
	scanf("%d", &N);
	printf("\n");
	printf("��������Ҫת���Ľ�������");
	scanf("%d", &n);
	printf("\n");

	// ����convert����;
	convert(S, N, n);

	return 0;
}