#define _CRT_SECURE_NO_WARNINGS 1
#define STACK_INIT_SIZE 100   //栈的初始空间大小  
#define STACKINCREAMENT 10    //增加空间
#define MaxSize 100
#include <stdio.h>
#include <stdlib.h>


/*数据类型定义*/
typedef int Position;
typedef int SElemType;
struct SNode {
	SElemType Data[MaxSize]; /* 存储元素的数组 */
	Position Top;            /* 栈顶指针 */
};
typedef struct SNode *Stack;
//以下为顺序栈操作函数
/*构造一个空栈*/
Stack CreateStack()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Top = -1;
	return S;
}

/*栈的判空函数*/
int IsEmpty(Stack S)
{
	return (S->Top == -1);
}

/*进栈*/
int Push(Stack S, SElemType X)
{
	if (S->Top == MaxSize - 1) {
		printf("堆栈满");
		return -1;//失败返回
	}
	else {
		//填写相应的语句。
		S->Data[++S->Top] = X;
		return 0;//成功返回
	}
}


/*出栈*/
SElemType Pop(Stack S)
{
	//填写相应的语句。
	if (IsEmpty(S))
	{
		printf("堆栈空\n");
		exit(-1);
	}
	return S->Data[S->Top--];
}

void convert(Stack S, int N, int n)
{
	//填写相应的语句。
	while (N)
	{
		Push(S, N%n);//余数入栈
		N = N / n;
	}
	printf("将%d转换为%d进制数为：", N, n);
	while (!IsEmpty(S))
	{
		printf("%d", Pop(S));//依次出栈
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	/*数制的转换过程*/
	int n, N;//要转换成的进制数和要转换的数  

	//初始化空栈  
	Stack S = CreateStack();

	printf("请输入需要十进制数：");
	scanf("%d", &N);
	printf("\n");
	printf("请输入需要转换的进制数：");
	scanf("%d", &n);
	printf("\n");

	// 调用convert函数;
	convert(S, N, n);

	return 0;
}