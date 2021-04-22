#include "calculator.h"

/*中缀转后缀函数*/
void Change(STDataType* str)
{
	Stack st;
	int i = 0;
	STDataType e;
	StackInit(&st);
	while (str[i] != '\0')
	{
			
		while (isdigit(str[i]))
		{/*过滤数字字符，直接输出，直到下一位不是数字字符打印空格跳出循环 */
			printf("%c", str[i++]);
			if (!isdigit(str[i]))
			{
				printf(" ");
			}
		}
		/*加减运算符优先级最低，如果栈顶元素为空则直接入栈，否则将栈中存储
		的运算符全部弹栈，如果遇到左括号则停止，将弹出的左括号从新压栈，因为左
		括号要和又括号匹配时弹出，这个后面单独讨论。弹出后将优先级低的运算符压入栈中*/
		if (str[i] == '+' || str[i] == '-')
		{
			if (StackEmpty(&st))
			{
				StackPush(&st, str[i]);
			}
			else
			{
				do
				{
					e = StackTop(&st);
					StackPop(&st);
					if (e == '(')
					{
						StackPush(&st, e);
					}
					else
					{
						printf("%c ", e);
					}
				} while (!StackEmpty(&st) && e != '(');
				StackPush(&st, str[i]);
			}
		}
		/*当遇到右括号是，把括号里剩余的运算符弹出，直到匹配到左括号为止
		左括号只弹出不打印（右括号也不压栈）*/
		else if (str[i] == ')')
		{
			e = StackTop(&st);
			StackPop(&st);
			while (e != '(')
			{
				printf("%c ", e);
				e = StackTop(&st);
				StackPop(&st);
			}
		}
		/*乘、除、左括号都是优先级高的，直接压栈*/
		else if (str[i] == '*' || str[i] == '/' || str[i] == '(')
		{
			StackPush(&st, str[i]);
		}

		else if (str[i] == '\0')
		{
			break;
		}

		else
		{
			printf("\n输入格式错误！\n");
			return;
		}
		i++;
	}
	/*最后把栈中剩余的运算符依次弹栈打印*/
	while (StackSize(&st))
	{
		e = StackTop(&st);
		StackPop(&st);
		printf("%c ", e);
	}
	printf("\n");
}

void Test1()
{
	STDataType str[MAX] = { 0 };
	gets(str);
	Change(str);
}

int main()
{
	Test1();
	return 0;
}