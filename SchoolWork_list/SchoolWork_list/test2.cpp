#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//-------- ���Ա�Ķ�̬����˳��洢�ṹ -----------
#define ERROR NULL
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
	ElementType Data;
	PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;
//-------- ���Ա�Ļ������� -----------------------------

/* ���� */
Position Find(List L, ElementType X)
{
	Position p = L; /* pָ��L�ĵ�1����� */

	while (p && p->Data != X)
		p = p->Next;

	/* ������������ return p; �滻 */
	if (p)
		return p;
	else
		return ERROR;
}

/* ��ͷ���Ĳ��� */
/*ע��:�ڲ���λ�ò���P����γ���Ƶ������ͬ���γ���Ƶ��i������λ�򣨴�1��ʼ��������P��������ָ�룬��P֮ǰ�����½�� */
bool Insert(List L, ElementType X, Position P)
{ /* ����Ĭ��L��ͷ��� */
	Position tmp, pre;

	/* ����P��ǰһ����� */
	for (pre = L; pre&&pre->Next != P; pre = pre->Next);
	if (pre == NULL) { /* P��ָ�Ľ�㲻��L�� */
		printf("����λ�ò�������\n");
		return false;
	}
	else { /* �ҵ���P��ǰһ�����pre */
		/* ��Pǰ�����½�� */
		tmp = (Position)malloc(sizeof(struct LNode)); /* ���롢��װ��� */
		tmp->Data = X;
		tmp->Next = P;
		pre->Next = tmp;
		return true;
	}
}

/* ��ͷ����ɾ�� */
/*ע��:��ɾ��λ�ò���P����γ���Ƶ������ͬ���γ���Ƶ��i������λ�򣨴�1��ʼ��������P����ɾ�����ָ�� */
bool Delete(List L, Position P)
{ /* ����Ĭ��L��ͷ��� */
	Position tmp, pre;

	/* ����P��ǰһ����� */
	for (pre = L; pre&&pre->Next != P; pre = pre->Next);
	if (pre == NULL || P == NULL) { /* P��ָ�Ľ�㲻��L�� */
		printf("ɾ��λ�ò�������\n");
		return false;
	}
	else { /* �ҵ���P��ǰһ�����pre */
		/* ��Pλ�õĽ��ɾ�� */
		pre->Next = P->Next;
		free(P);
		return true;
	}
}
//��������
PtrToLNode CreateFromHead()
{
	PtrToLNode L;
	PtrToLNode s;
	int x;
	int flag = 1;
	L = (PtrToLNode)malloc(sizeof(PtrToLNode));
	L->Next = NULL;
	scanf("%d", &x);
	while (x != -1)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->Data = x;
		s->Next = L->Next;
		L->Next = s;
		x--;
	}
	return L;
}
//��ʾ����
void  show_linklist(PtrToLNode L)
{
	if (L->Next == NULL)
	{
		printf("ERROR\n");
		return;
	}
	while (L->Next)
	{
		printf("%d ", L->Next->Data);
		L = L->Next;
	}
	printf("\n");
}
void main(void) {
	int i = 0;
	List L = NULL;
	L = CreateFromHead();
	show_linklist(L);

	printf("��Ԫ��2֮ǰ��������9:>\n");
	Position pos = Find(L, 2);
	Insert(L, 9, pos);
	show_linklist(L);

	printf("��Ԫ��4֮ǰ��������10:>\n");
	pos = Find(L, 4);
	Insert(L, 10, pos);
	show_linklist(L);

	printf("ɾ��ֵΪ9��Ԫ��:>\n");
	pos = Find(L, 9);
	Delete(L, pos);
	show_linklist(L);

	printf("ɾ��ֵΪ10��Ԫ��:>\n");
	pos = Find(L, 10);
	Delete(L, pos);
	show_linklist(L);
}