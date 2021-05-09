//#include<stdio.h>
//#include<stdlib.h>
//#include<malloc.h>
//
//typedef int DataType;
//
//typedef struct Node{   //定义链队结点的类型 
//	DataType data;
//	struct Node *next;
//}LinkNode;
//
//typedef struct{       //将头尾指针封装在一起的链队列 
//	LinkNode *front, *rear;
//}LinkQueue;
//
//typedef LinkQueue * LinkQ;
//LinkQ Init_Queue()  //队列初始化 
//{
//	LinkQ q;
//	q = (LinkQueue*)malloc(sizeof(LinkQueue));
//	q->front = NULL;
//	q->rear = NULL;
//	return q;
//}
////入队操作，请填写完整
//void Push_Queue(LinkQueue *q, DataType x)  //入队操作 
//{
//	LinkNode *p;
//	p = (LinkNode*)malloc(sizeof(LinkNode));
//	p->data = x;
//	p->next = NULL;
//	if (q->front == NULL)
//	{
//		//填写相应代码
//		q->front = p;
//		q->rear = p;
//	}
//	else
//	{
//		//填写相应代码
//		q->rear->next = p;//入队结点链接在尾结点后面
//		q->rear = p;//尾指针指向入队结点
//	}
//}
//int Queue_Empty(LinkQueue *q)  //判断空操作 
//{
//	if (q->front == NULL)
//		return 1;
//	else
//		return 0;
//}
//void Pop_Queue(LinkQueue *q)  //出队操作 
//{
//	LinkNode *p;
//	DataType FrontElem;
//	if (Queue_Empty(q))
//		printf("Queue is Empty");
//	else
//	{
//		//填写相应代码
//		FrontElem = q->front->data;//队头元素
//		p = q->front;
//		q->front = q->front->next;
//		free(p);
//		printf("%d is out\n", FrontElem);
//	}
//}
//void GetHead_Queue(LinkQueue *q) //读取队头元素 
//{
//	if (Queue_Empty(q))
//		printf("Queue is Empty!\n");
//	else
//		printf("%d\n", q->front->data);
//}
//void Queue_Length(LinkQueue *q)  //求队列的长度 
//{
//	LinkNode *p;
//	p = q->front;
//	int t = 0;//记录结点个数
//	while (p != NULL)
//	{
//		//填写相应代码
//		t++;
//		p = p->next;
//	}
//	printf("Queue Length is %d\n", t);
//}
//
////主函数
//int main()
//{
//	//创建队列
//	LinkQ q = Init_Queue();
//	//入队操作
//	Push_Queue(q, 1);
//	//入队操作
//	Push_Queue(q, 2);
//	//入队操作
//	Push_Queue(q, 3);
//
//	Queue_Length(q);
//	GetHead_Queue(q);
//
//	//出队操作
//	Pop_Queue(q);
//
//	Queue_Length(q);
//	GetHead_Queue(q);
//}