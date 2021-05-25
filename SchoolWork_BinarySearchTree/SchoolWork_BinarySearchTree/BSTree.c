#include "BSTree.h"
#include "queue.h"

//�½�һ�����
BTNode* CreateNode(BTDataType x)
{
	BTNode* Node = (BTNode*)malloc(sizeof(BTNode));
	if (Node == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	Node->data = x;
	Node->left = Node->right = NULL;

	return Node;
}
//����
BTNode* Insert(BTNode* root, BTDataType x)
{
	if (root == NULL)//����
	{
		BTNode* newNode = CreateNode(x);
		return newNode;
	}
	else
	{
		if (x < root->data)
		{
			root->left = Insert(root->left, x);
		}
		else if (x>root->data)
		{
			root->right = Insert(root->right, x);
		}
		return root;
	}
}
//ɾ��
void Delet(BTNode* root, BTDataType x)
{

}

//���ң��ݹ飩
BTNode* Find(BTNode* root, BTDataType x)
{
	if (root == NULL)
		return NULL;
	if (x > root->data)//��������
		return Find(root->right, x);
	else if (x < root->data)//��������
		return Find(root->left, x);
	return root;
}

//���ң��ǵݹ飩
BTNode* FindNonR(BTNode* root, BTDataType x);

//�������Ԫ�أ��ݹ飩
BTNode* FindMax(BTNode* root);
//�������Ԫ�أ��ǵݹ飩
BTNode* FindMaxNonR(BTNode* root);

//������СԪ�أ��ݹ飩
BTNode* FindMin(BTNode* root);
//������СԪ�أ��ǵݹ飩
BTNode* FindMinNonR(BTNode* root);

////�������
//void BinaryLevelOrder(BTNode* root)
//{
//	Queue q;
//	QueueInit(&q);//��ʼ������
//	if (root != NULL)
//		QueuePush(&q, root);
//	while (!QueueEmpty(&q))//�����в�Ϊ��ʱ��ѭ������
//	{
//		BTNode* front = QueueFront(&q);//��ȡ��ͷԪ��
//		QueuePop(&q);//ɾ����ͷԪ��
//		printf("%d ", front->data);//��ӡ���ӵ�Ԫ��
//		if (front->left)
//		{
//			QueuePush(&q, front->left);//����Ԫ�ص����������
//		}
//		if (front->right)
//		{
//			QueuePush(&q, front->right);//����Ԫ�ص��Һ��������
//		}
//	}
//	QueueDestroy(&q);//���ٶ���
//}

//�������
void BinaryLevelOrder(BTNode* root)
{
	Queue q;
	QueueInit(&q);//��ʼ������
	if (root != NULL)
		QueuePush(&q, root);
	while (!QueueEmpty(&q))//�����в�Ϊ��ʱ��ѭ������
	{
		BTNode* front = QueueFront(&q);//��ȡ��ͷԪ��
		QueuePop(&q);//ɾ����ͷԪ��
		if (front == NULL)
		{
			printf("NULL ");
		}
		else
		{
			printf("%d ", front->data);//��ӡ���ӵ�Ԫ��
		}
		if (front)
		{
			QueuePush(&q, front->left);//����Ԫ�ص����������
			QueuePush(&q, front->right);//����Ԫ�ص��Һ��������
		}
	}
	QueueDestroy(&q);//���ٶ���
}