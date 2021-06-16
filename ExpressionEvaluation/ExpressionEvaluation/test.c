#include "stack.h"
#include "stack2.h"

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
void Change(char* str, char* post)
{
	int i = 0;
	int j = 0;
	char e;
	Stack st;
	StackInit(&st);
	while (str[i] != '\0')
	{
		while (isdigit(str[i]))
		{/*���������ַ���ֱ�������ֱ����һλ���������ַ���ӡ�ո�����ѭ�� */
			//printf("%c", str[i]);
			post[j++] = str[i];
			i++;
			if (!isdigit(str[i]))
			{
				//printf(" ");
				post[j++] = ' ';
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
						//printf("%c ", e);
						post[j++] = e;
						post[j++] = ' ';

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
				//printf("%c ", e);
				post[j++] = e;
				post[j++] = ' ';

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
		//printf("%c ", e);
		post[j++] = e;
		post[j++] = ' ';
	}
	post[j] = '\0';
	StackDestroy(&st);
}

//����������������һ�������������ؼ�����
double Calculate(double Op1, double Op2, char Opr)
{
	double ret = 0;
	switch (Opr)
	{
	case '+':
		ret = Op1 + Op2;
		break;
	case '-':
		ret = Op1 - Op2;
		break;
	case '*':
		ret = Op1*Op2;
		break;
	case '/':
		ret = Op1 / Op2;
		break;
	default:
		printf("error\n");
		exit(-1);
	}
	return ret;
}

//��׺���ʽ��ֵ
double PostFixExp(char* post)
{
	double ret = 0;
	Stack2 st;
	StackInit2(&st); //��ʼ��ջ
	while (*post != '\0')
	{
		if (isdigit(*post))//������
		{
			double num = atof(post);
			StackPush2(&st, num);
			while (*post != ' ')
				post++;
		}
		else//�������
		{
			double Op2 = StackTop2(&st);
			StackPop2(&st);
			double Op1 = StackTop2(&st);
			StackPop2(&st);
			ret = Calculate(Op1, Op2, *post);
			StackPush2(&st, ret);
			post++;
		}
		post++;
	}
	StackDestroy2(&st);
	return ret;
}
void test(char* post)
{
	double num = atof(post);
	printf("%lf\n", num);
	post += 2;

	num = atof(post);
	printf("%lf\n", num);
	post += 2;

	num = atof(post);
	printf("%lf\n", num);
	post += 2;

	num = atof(post);
	printf("%lf\n", num);
	post += 2;

	printf("%c\n", *post);
}
int main()
{
	char str[MAX];
	char post[MAX];
	gets(str);
	//InfixToPostfix(str);
	Change(str, post);
	printf("��׺���ʽΪ:%s\n", post);
	//test(post);
	double ret = PostFixExp(post);
	printf("������Ϊ:%.2lf\n", ret);
	return 0;
}