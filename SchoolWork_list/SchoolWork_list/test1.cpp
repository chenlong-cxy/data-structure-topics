//#include<stdio.h>
//#include<stdlib.h>
////-------- ���Ա�Ķ�̬����˳��洢�ṹ -----------
//#define MAXSIZE 10
//typedef int ElementType;
//typedef int Position;
//typedef struct LNode *List;
//struct LNode {
//	ElementType Data[MAXSIZE];
//	Position Last;
//};
////-------- ���Ա�Ļ������� -----------------------------
////������������ʾ˳���Ԫ��
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
///* ��ʼ�� */
//List MakeEmpty()
//{
//	List PtrL;
//	PtrL = (List)malloc(sizeof(struct LNode));
//	PtrL->Last = -1;
//	return PtrL;
//}
//
///* ���� */
//#define ERROR -1
//
//Position Find(List L, ElementType X)
//{
//	Position i = 0;
//
//	while (i <= L->Last && L->Data[i] != X)
//		i++;
//	if (i > L->Last)  return ERROR; /* ���û�ҵ������ش�����Ϣ */
//	else  return i;  /* �ҵ��󷵻ص��Ǵ洢λ�� */
//}
//
///* ���� */
//void Insert(ElementType X, int i, List PtrL)
//{
//	int j;
//	if (PtrL->Last == MAXSIZE - 1){  /* ��ռ����������ܲ���*/
//		printf("full\n");
//		return;
//	}
//	if (i < 1 || i > PtrL->Last + 2) { /*������λ�õĺϷ���*/
//		printf("error\n");
//		return;
//	}
//	for (j = PtrL->Last; j >= i - 1; j--)
//		PtrL->Data[j + 1] = PtrL->Data[j];     /*�� ai�� an��������ƶ�*/
//	PtrL->Data[i - 1] = X;                 /*��Ԫ�ز���*/
//	PtrL->Last++;                        /*Last��ָ�����Ԫ��*/
//	return;
//}
///* ɾ�� */
///*ע��:��ɾ��λ�ò���P����γ���Ƶ������ͬ���γ���Ƶ��i������λ�򣨴�1��ʼ��������P�Ǵ洢�±�λ�ã���0��ʼ�������߲�1*/
//void  Delete(List L, int  P)
//{ /* ��L��ɾ��ָ��λ��P��Ԫ�� */
//	int i;
//
//	if (P<0 || P>L->Last) { /* ���ձ�ɾ��λ�õĺϷ��� */
//		printf("λ��%d������Ԫ��", P);
//		return;
//	}
//	for (i = P + 1; i <= L->Last; i++)
//		L->Data[i - 1] = L->Data[i]; /* ��λ��P+1���Ժ��Ԫ��˳����ǰ�ƶ� */
//	L->Last--; /* Last��ָ�����Ԫ�� */
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
//	printf("ɾ��������Ԫ�غ�:>\n");
//	Delete(L, 3 - 1);//ɾ��������Ԫ��
//	show_seqlist(L);
//
//
//	Position pos = Find(L, 2);
//	printf("ֵΪ%d��Ԫ�ص�λ��Ϊ:>%d\n", 2, pos + 1);
//}