//#include<stdio.h>
//#include<stdlib.h>
//#include<malloc.h>
//
//typedef int DataType;
//
//typedef struct Node{   //�������ӽ������� 
//	DataType data;
//	struct Node *next;
//}LinkNode;
//
//typedef struct{       //��ͷβָ���װ��һ��������� 
//	LinkNode *front, *rear;
//}LinkQueue;
//
//typedef LinkQueue * LinkQ;
//LinkQ Init_Queue()  //���г�ʼ�� 
//{
//	LinkQ q;
//	q = (LinkQueue*)malloc(sizeof(LinkQueue));
//	q->front = NULL;
//	q->rear = NULL;
//	return q;
//}
////��Ӳ���������д����
//void Push_Queue(LinkQueue *q, DataType x)  //��Ӳ��� 
//{
//	LinkNode *p;
//	p = (LinkNode*)malloc(sizeof(LinkNode));
//	p->data = x;
//	p->next = NULL;
//	if (q->front == NULL)
//	{
//		//��д��Ӧ����
//		q->front = p;
//		q->rear = p;
//	}
//	else
//	{
//		//��д��Ӧ����
//		q->rear->next = p;//��ӽ��������β������
//		q->rear = p;//βָ��ָ����ӽ��
//	}
//}
//int Queue_Empty(LinkQueue *q)  //�жϿղ��� 
//{
//	if (q->front == NULL)
//		return 1;
//	else
//		return 0;
//}
//void Pop_Queue(LinkQueue *q)  //���Ӳ��� 
//{
//	LinkNode *p;
//	DataType FrontElem;
//	if (Queue_Empty(q))
//		printf("Queue is Empty");
//	else
//	{
//		//��д��Ӧ����
//		FrontElem = q->front->data;//��ͷԪ��
//		p = q->front;
//		q->front = q->front->next;
//		free(p);
//		printf("%d is out\n", FrontElem);
//	}
//}
//void GetHead_Queue(LinkQueue *q) //��ȡ��ͷԪ�� 
//{
//	if (Queue_Empty(q))
//		printf("Queue is Empty!\n");
//	else
//		printf("%d\n", q->front->data);
//}
//void Queue_Length(LinkQueue *q)  //����еĳ��� 
//{
//	LinkNode *p;
//	p = q->front;
//	int t = 0;//��¼������
//	while (p != NULL)
//	{
//		//��д��Ӧ����
//		t++;
//		p = p->next;
//	}
//	printf("Queue Length is %d\n", t);
//}
//
////������
//int main()
//{
//	//��������
//	LinkQ q = Init_Queue();
//	//��Ӳ���
//	Push_Queue(q, 1);
//	//��Ӳ���
//	Push_Queue(q, 2);
//	//��Ӳ���
//	Push_Queue(q, 3);
//
//	Queue_Length(q);
//	GetHead_Queue(q);
//
//	//���Ӳ���
//	Pop_Queue(q);
//
//	Queue_Length(q);
//	GetHead_Queue(q);
//}