#include "stack.h"

//��׺���ʽת��׺���ʽ
//void InfixToPostfix(char* str)
//{
//	int sz = strlen(str);
//	int i = 0;
//	Stack st;
//	StackInit(&st);
//	while (i < sz)
//	{
//		while (str[i] >= '0'&&str[i] <= '9')
//		{
//			printf("%c", str[i]);
//			i++;
//			if (str[i]<'0' || str[i]>'9')
//			{
//				printf(" ");
//			}
//		}
//		if (str[i] == '(')//������ֱ����ջ
//			StackPush(&st, str[i]);
//		if (str[i] == ')')
//		{
//			char top = StackTop(&st);
//			StackPop(&st);
//			while (top != '(')
//			{
//				printf("%c ", top);
//				top = StackTop(&st);
//				StackPop(&st);
//			}
//		}
//		if (str[i] == '+' || str[i] == '-')
//		{
//			if (!StackEmpty(&st))
//			{
//				char top = StackTop(&st);
//			    if (top == '+' || top == '-')
//				{
//					StackPop(&st);
//					printf("%c ", top);
//				}
//			}
//			StackPush(&st, str[i]);
//			i++;
//		}
//		if (str[i] == '*' || str[i] == '/')
//		{
//			if (!StackEmpty(&st))
//			{
//				char top = StackTop(&st);
//				while (top != '(')
//				{
//					StackPop(&st);
//					printf("%c ", top);
//					if (StackEmpty(&st))
//						break;
//					top = StackTop(&st);
//				}
//			}
//			StackPush(&st, str[i]);
//			i++;
//		}
//	}
//	while (!StackEmpty(&st))
//	{
//		char top = StackTop(&st);
//		StackPop(&st);
//		printf("%c ", top);
//	}
//	StackDestroy(&st);
//}
/*��׺ת��׺����*/
void Change(char* str)
{
	int i = 0;
	char e;
	Stack st;
	StackInit(&st);
	while (str[i] != '\0')
	{
		while (isdigit(str[i]))
		{/*���������ַ���ֱ�������ֱ����һλ���������ַ���ӡ�ո�����ѭ�� */
			printf("%c", str[i]);

			i++;
			if (!isdigit(str[i]))
			{
				printf(" ");
			}
		}
		/*�Ӽ���������ȼ���ͣ����ջ��Ԫ��Ϊ����ֱ����ջ������ջ�д洢
		�������ȫ����ջ�����������������ֹͣ���������������Ŵ���ѹջ����Ϊ��
		����Ҫ��������ƥ��ʱ������������浥�����ۡ����������ȼ��͵������ѹ��ջ��*/
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
					if (e != '(')
					{
						printf("%c ", e);
						StackPop(&st);
					}
				} while (!StackEmpty(&st) && e != '(');
				StackPush(&st, str[i]);
			}
		}
		/*�������������ǣ���������ʣ��������������ֱ��ƥ�䵽������Ϊֹ
		������ֻ��������ӡ��������Ҳ��ѹջ��*/
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
		/*�ˡ����������Ŷ������ȼ��ߵģ�ֱ��ѹջ*/
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
			printf("\n�����ʽ����\n");
			return;
		}
		i++;
	}
	/*����ջ��ʣ�����������ε�ջ��ӡ*/
	while (!StackEmpty(&st))
	{
		e = StackTop(&st);
		StackPop(&st);
		printf("%c ", e);
	}
}


int main()
{
	char str[MAX];
	char post[MAX];
	gets(str);
	//InfixToPostfix(str);
	Change(str);
	
	return 0;
}