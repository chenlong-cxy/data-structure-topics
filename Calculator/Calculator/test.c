#include "calculator.h"

/*��׺ת��׺����*/
//void Change(STDataType* str)
//{
//	Stack st;
//	int i = 0;
//	STDataType e;
//	StackInit(&st);
//	while (str[i] != '\0')
//	{
//			
//		while (isdigit(str[i]))
//		{/*���������ַ���ֱ�������ֱ����һλ���������ַ���ӡ�ո�����ѭ�� */
//			printf("%c", str[i++]);
//			if (!isdigit(str[i]))
//			{
//				printf(" ");
//			}
//		}
//		/*�Ӽ���������ȼ���ͣ����ջ��Ԫ��Ϊ����ֱ����ջ������ջ�д洢
//		�������ȫ����ջ�����������������ֹͣ���������������Ŵ���ѹջ����Ϊ��
//		����Ҫ��������ƥ��ʱ������������浥�����ۡ����������ȼ��͵������ѹ��ջ��*/
//		if (str[i] == '+' || str[i] == '-')
//		{
//			if (StackEmpty(&st))
//			{
//				StackPush(&st, str[i]);
//			}
//			else
//			{
//				do
//				{
//					e = StackTop(&st);
//					StackPop(&st);
//					if (e == '(')
//					{
//						StackPush(&st, e);
//					}
//					else
//					{
//						printf("%c ", e);
//					}
//				} while (!StackEmpty(&st) && e != '(');
//				StackPush(&st, str[i]);
//			}
//		}
//		/*�������������ǣ���������ʣ��������������ֱ��ƥ�䵽������Ϊֹ
//		������ֻ��������ӡ��������Ҳ��ѹջ��*/
//		else if (str[i] == ')')
//		{
//			e = StackTop(&st);
//			StackPop(&st);
//			while (e != '(')
//			{
//				printf("%c ", e);
//				e = StackTop(&st);
//				StackPop(&st);
//			}
//		}
//		/*�ˡ����������Ŷ������ȼ��ߵģ�ֱ��ѹջ*/
//		else if (str[i] == '*' || str[i] == '/' || str[i] == '(')
//		{
//			StackPush(&st, str[i]);
//		}
//
//		else if (str[i] == '\0')
//		{
//			break;
//		}
//
//		else
//		{
//			printf("\n�����ʽ����\n");
//			return;
//		}
//		i++;
//	}
//	/*����ջ��ʣ�����������ε�ջ��ӡ*/
//	while (StackSize(&st))
//	{
//		e = StackTop(&st);
//		StackPop(&st);
//		printf("%c ", e);
//	}
//	printf("\n");
//}

void InfixToSuffix(STDataType* str)
{
	Stack st;//����һ��ջ
	StackInit(&st);//��ʼ��ջ
	STDataType* cur = str;//���ڱ����ַ�����ָ��
	while (*cur)
	{
		while (isdigit(*cur))//�����֣�ֱ�Ӵ�ӡ
		{
			printf("%c", *cur);
			cur++;
			if (!isdigit(*cur))//�������֣�����ѭ��
			{
				printf(" ");
				break;
			}
		}
		if (*cur == '+' || *cur == '-')
		{
			if (StackEmpty(&st))//ջΪ�գ�ֱ����ջ
			{
				StackPush(&st, *cur);
			}
			else//ջ��Ϊ�գ��Ƚ�ջ�е������ȫ�����������;����ǰ���ţ���ֹͣ����������õ�ǰ�������ջ
			{
				while (!StackEmpty(&st) && StackTop(&st) != '(')
				{
					printf("%c ", StackTop(&st));
					StackPop(&st);
				}
				StackPush(&st, *cur);
			}
			cur++;
		}
		else if (*cur == '*' || *cur == '/' || *cur == '(')//�˺š����š�ǰ���ž�ֱ����ջ
		{
			StackPush(&st, *cur);
			cur++;
		}
		else if (*cur == ')')//���������ţ���ʼ��ջ������������ֱ��������֮ƥ���ǰ���ţ�ǰ���Ų���ӡ��
		{
			while (StackTop(&st) != '(')
			{
				printf("%c ", StackTop(&st));
				StackPop(&st);
			}
			StackPop(&st);//ɾ��ǰ����
			cur++;
		}
		else if (*cur == ' ')//��ȡ���ո�����
		{
			cur++;
		}
		else if (*cur == '\0')//�ַ�����ȡ��ϣ�����ѭ��
		{
			break;
		}
	}
	while (!StackEmpty(&st))//���ջ�е�ȫ�������
	{
		printf("%c ", StackTop(&st));
		StackPop(&st);
	}
	printf("\n");
	StackDestroy(&st);//����ջ����ֹ�ڴ�й©
}

void Test1()
{
	STDataType str[MAX] = { 0 };
	gets(str);
	MyChange(str);
}

int main()
{
	Test1();
	return 0;
}