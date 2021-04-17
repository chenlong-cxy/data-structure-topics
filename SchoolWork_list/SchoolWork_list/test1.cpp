//#include<stdio.h>
//#include<stdlib.h>
////-------- 线性表的动态分配顺序存储结构 -----------
//#define MAXSIZE 10
//typedef int ElementType;
//typedef int Position;
//typedef struct LNode *List;
//struct LNode {
//	ElementType Data[MAXSIZE];
//	Position Last;
//};
////-------- 线性表的基本运算 -----------------------------
////辅助函数：显示顺序表元素
//void show_seqlist(List L)
//{
//	int i = 0;
//	if (L == NULL)
//	{
//		puts("seqlist_t *L is NULL");
//		return;
//	}
//	for (i = 0; i <= L->Last; i++)
//		printf("L->data[%d] = %d\n", i, L->Data[i]);
//	return;
//
//}
///* 初始化 */
//List MakeEmpty()
//{
//	List PtrL;
//	PtrL = (List)malloc(sizeof(struct LNode));
//	PtrL->Last = -1;
//	return PtrL;
//}
//
///* 查找 */
//#define ERROR -1
//
//Position Find(List L, ElementType X)
//{
//	Position i = 0;
//
//	while (i <= L->Last && L->Data[i] != X)
//		i++;
//	if (i > L->Last)  return ERROR; /* 如果没找到，返回错误信息 */
//	else  return i;  /* 找到后返回的是存储位置 */
//}
//
///* 插入 */
//void Insert(ElementType X, int i, List PtrL)
//{
//	int j;
//	if (PtrL->Last == MAXSIZE - 1){  /* 表空间已满，不能插入*/
//		printf("full\n");
//		return;
//	}
//	if (i < 1 || i > PtrL->Last + 2) { /*检查插入位置的合法性*/
//		printf("error\n");
//		return;
//	}
//	for (j = PtrL->Last; j >= i - 1; j--)
//		PtrL->Data[j + 1] = PtrL->Data[j];     /*将 ai～ an倒序向后移动*/
//	PtrL->Data[i - 1] = X;                 /*新元素插入*/
//	PtrL->Last++;                        /*Last仍指向最后元素*/
//	return;
//}
///* 删除 */
///*注意:在删除位置参数P上与课程视频有所不同，课程视频中i是序列位序（从1开始），这里P是存储下标位置（从0开始），两者差1*/
//void  Delete(List L, int  P)
//{ /* 从L中删除指定位置P的元素 */
//	int i;
//
//	if (P<0 || P>L->Last) { /* 检查空表及删除位置的合法性 */
//		printf("位置%d不存在元素", P);
//		return;
//	}
//	for (i = P + 1; i <= L->Last; i++)
//		L->Data[i - 1] = L->Data[i]; /* 将位置P+1及以后的元素顺序向前移动 */
//	L->Last--; /* Last仍指向最后元素 */
//}
//void main(void) {
//	int i = 0;
//	List L = NULL;
//	L = MakeEmpty();
//	Insert(1, 1, L);
//	Insert(2, 2, L);
//	Insert(3, 3, L);
//	Insert(4, 4, L);
//	show_seqlist(L);
//
//	printf("删除第三个元素后:>\n");
//	Delete(L, 3 - 1);//删除第三个元素
//	show_seqlist(L);
//
//
//	Position pos = Find(L, 2);
//	printf("值为%d的元素的位置为:>%d\n", 2, pos + 1);
//}