#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//-------- 线性表的动态分配顺序存储结构 -----------
#define ERROR NULL
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
	ElementType Data;
	PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;
//-------- 线性表的基本运算 -----------------------------

/* 查找 */
Position Find(List L, ElementType X)
{
	Position p = L; /* p指向L的第1个结点 */

	while (p && p->Data != X)
		p = p->Next;

	/* 下列语句可以用 return p; 替换 */
	if (p)
		return p;
	else
		return ERROR;
}

/* 带头结点的插入 */
/*注意:在插入位置参数P上与课程视频有所不同，课程视频中i是序列位序（从1开始），这里P是链表结点指针，在P之前插入新结点 */
bool Insert(List L, ElementType X, Position P)
{ /* 这里默认L有头结点 */
	Position tmp, pre;

	/* 查找P的前一个结点 */
	for (pre = L; pre&&pre->Next != P; pre = pre->Next);
	if (pre == NULL) { /* P所指的结点不在L中 */
		printf("插入位置参数错误\n");
		return false;
	}
	else { /* 找到了P的前一个结点pre */
		/* 在P前插入新结点 */
		tmp = (Position)malloc(sizeof(struct LNode)); /* 申请、填装结点 */
		tmp->Data = X;
		tmp->Next = P;
		pre->Next = tmp;
		return true;
	}
}

/* 带头结点的删除 */
/*注意:在删除位置参数P上与课程视频有所不同，课程视频中i是序列位序（从1开始），这里P是拟删除结点指针 */
bool Delete(List L, Position P)
{ /* 这里默认L有头结点 */
	Position tmp, pre;

	/* 查找P的前一个结点 */
	for (pre = L; pre&&pre->Next != P; pre = pre->Next);
	if (pre == NULL || P == NULL) { /* P所指的结点不在L中 */
		printf("删除位置参数错误\n");
		return false;
	}
	else { /* 找到了P的前一个结点pre */
		/* 将P位置的结点删除 */
		pre->Next = P->Next;
		free(P);
		return true;
	}
}
//创建链表
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
//显示链表
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

	printf("在元素2之前插入整数9:>\n");
	Position pos = Find(L, 2);
	Insert(L, 9, pos);
	show_linklist(L);

	printf("在元素4之前插入整数10:>\n");
	pos = Find(L, 4);
	Insert(L, 10, pos);
	show_linklist(L);

	printf("删除值为9的元素:>\n");
	pos = Find(L, 9);
	Delete(L, pos);
	show_linklist(L);

	printf("删除值为10的元素:>\n");
	pos = Find(L, 10);
	Delete(L, pos);
	show_linklist(L);
}