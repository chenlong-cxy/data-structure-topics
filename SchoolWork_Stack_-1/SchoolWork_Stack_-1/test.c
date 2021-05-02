#include "stack.h"

//栈的-1问题
void StackQuestion()
{
	Stack st;
	StackInit(&st);//初始化栈
	int input = 0;
	while (scanf("%d", &input) != EOF)//循环输入
	{
		if (input != -1)//input不等于-1，进栈
		{
			StackPush(&st, input);
		}
		else//input等于-1，打印栈顶元素并出栈
		{
			int output = StackTop(&st);//读取栈顶元素
			printf("出栈元素为：%d\n", output);
			StackPop(&st);//出栈
		}
	}

	StackDestroy(&st);//销毁栈
}

int main()
{
	StackQuestion();
	return 0;
}