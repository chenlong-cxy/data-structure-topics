#include "BinaryTree.h"
#include "queue.h"

//�������
//ǰ�����
void BinaryPrevOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	//��->������->������
	printf("%c ", root->data);
	BinaryPrevOrder(root->left);
	BinaryPrevOrder(root->right);
}

//�������
void BinaryInOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	//������->��->������
	BinaryInOrder(root->left);
	printf("%c ", root->data);
	BinaryInOrder(root->right);
}

//�������
void BinaryPostOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	//������->������->��
	BinaryPostOrder(root->left);
	BinaryPostOrder(root->right);
	printf("%c ", root->data);
}

//�������
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
		printf("%c ", front->data);//��ӡ���ӵ�Ԫ��
		if (front->left)
		{
			QueuePush(&q, front->left);//����Ԫ�ص����������
		}
		if (front->right)
		{
			QueuePush(&q, front->right);//����Ԫ�ص��Һ��������
		}
	}
	QueueDestroy(&q);//���ٶ���
}

//���ĸ���
int BinaryTreeSize(BTNode* root)
{
	//if (root == NULL)
	//{
	//	return 0;
	//}
	//return BinaryTreeSize(root->left) + BinaryTreeSize(root->right) + 1;
	
	//������ = �������Ľ����� + �������Ľ����� + �Լ�
	return root == NULL ? 0 : BinaryTreeSize(root->left) + BinaryTreeSize(root->right) + 1;
}

//Ҷ�ӽ��ĸ���
int BinaryTreeLeafSize(BTNode* root)
{
	if (root == NULL)//������Ҷ�ӽ��
		return 0;
	if (root->left == NULL&&root->right == NULL)//��Ҷ�ӽ��
		return 1;
	//Ҷ�ӽ��ĸ��� = ��������Ҷ�ӽ����� + ��������Ҷ�ӽ�����
	return BinaryTreeLeafSize(root->left) + BinaryTreeLeafSize(root->right);
}

//��k����ĸ���
int BinaryTreeKLevelSize(BTNode* root, int k)
{
	if (k < 1 || root == NULL)//����������kֵ���Ϸ�
		return 0;
	if (k == 1)//��һ�������
		return 1;
	//����ڸ����ĵ�k��Ľ����� = ������������ӽ��ĵ�k-1��Ľ�����֮��
	return BinaryTreeKLevelSize(root->left, k - 1) + BinaryTreeKLevelSize(root->right, k - 1);
}

//����ֵΪx�Ľ��
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	if (root == NULL)//����
		return NULL;
	if (root->data == x)//�ڸ���㴦��
		return root;
	BTNode* lret = BinaryTreeFind(root->left, x);//������������
	if (lret)
		return lret;
	BTNode* rret = BinaryTreeFind(root->right, x);//������������
	if (rret)
		return rret;
	return NULL;//���������������о�û���ҵ�
}

//��ϴ�ֵ
int Max(int a, int b)
{
	return a > b ? a : b;
}
//����������
int BinaryTreeMaxDepth(BTNode* root)
{
	if (root == NULL)//���������Ϊ0
		return 0;
	//���������� = ������������Ƚϴ��ֵ + 1
	return Max(BinaryTreeMaxDepth(root->left), BinaryTreeMaxDepth(root->right)) + 1;
}

//����������
void BinaryTreeDestroy(BTNode* root)
{
	if (root == NULL)
		return;

	BinaryTreeDestroy(root->left);//����������
	BinaryTreeDestroy(root->right);//����������
	free(root);//�ͷŸ����
}

//void BinaryTreeDestroy(BTNode** root)
//{
//	if (*root == NULL)
//		return;
//
//	BinaryTreeDestroy(&(*root)->left);
//	BinaryTreeDestroy(&(*root)->right);
//	free(*root);
//	*root = NULL;
//}

//void BinaryTreeDestroy(BTNode*& root)//ȡ����
//{
//	if (root == NULL)
//		return;
//
//	BinaryTreeDestroy(root->left);
//	BinaryTreeDestroy(root->right);
//	free(root);
//	root = NULL;
//}

//�ж϶������Ƿ�����ȫ������
bool isCompleteTree(BTNode* root)
{
	Queue q;
	QueueInit(&q);//��ʼ������
	if (root != NULL)
		QueuePush(&q, root);
	while (!QueueEmpty(&q))//�����в�Ϊ��ʱ��ѭ������
	{
		BTNode* front = QueueFront(&q);//��ȡ��ͷԪ��
		QueuePop(&q);//ɾ����ͷԪ��
		if (front == NULL)//����ȡ����ָ��ʱ��ֹͣ��Ӳ���
			break;
		QueuePush(&q, front->left);//����Ԫ�ص����������
		QueuePush(&q, front->right);//����Ԫ�ص��Һ��������
	}
	while (!QueueEmpty(&q))//��ȡ������ʣ�������
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);
		if (front != NULL)//�������д��ڷǿ�ָ�룬������ȫ������
		{
			QueueDestroy(&q);//���ٶ���
			return false;
		}
	}
	QueueDestroy(&q);//���ٶ���
	return true;//��������ȫ�ǿ�ָ�룬������ȫ������
}

//�ж϶������Ƿ��ǵ�ֵ������
bool isUnivalTree(BTNode* root)
{
	if (root == NULL)//��Ϊ�գ��ǵ�ֵ������
		return true;
	if (root->left && root->left->data != root->data)//���Ӵ��ڣ������ӵ�ֵ�����ڸ���ֵ
		return false;
	if (root->right && root->right->data != root->data)//�Һ��Ӵ��ڣ����Һ��ӵ�ֵ�����ڸ���ֵ
		return false;
	return isUnivalTree(root->left) && isUnivalTree(root->right);//�������ǵ�ֵ�����������������ǵ�ֵ������
}

//�ж����ö������Ƿ���ͬ
bool isSameTree(BTNode* p, BTNode* q)
{
	if (p == NULL&&q == NULL)//��������Ϊ�գ�����ͬ
		return true;
	if (p == NULL || q == NULL)//��������ֻ��һ����Ϊ�գ�����ͬ
		return false;
	if (p->data != q->data)//����������ֵ��ͬ������ͬ
		return false;
	return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);//����������������ͬ������������ͬ��������������ͬ
}

//�����Ľ�����
int TreeSize(BTNode* root)
{
	return root == NULL ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
}
//�����н���ֵ��������
void preorder(BTNode* root, int* arr, int* pi)
{
	if (root == NULL)//�����Ϊ�գ�ֱ�ӷ���
		return;
	arr[(*pi)++] = root->data;//�Ƚ�������ֵ��������
	//printf("%d ",root->val);
	preorder(root->left, arr, pi);//�ٽ��������н���ֵ��������
	preorder(root->right, arr, pi);//����������н���ֵ��������
}
//ǰ�����
int* preorderTraversal(BTNode* root, int* returnSize)
{
	*returnSize = TreeSize(root);//ֵ�ĸ������ڽ��ĸ���
	int* arr = (int*)malloc(sizeof(int)*(*returnSize));
	int i = 0;
	preorder(root, arr, &i);//�����н���ֵ��������
	return arr;
}

////�����Ľ�����
//int TreeSize(BTNode* root)
//{
//	return root == NULL ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
//}
//�����н���ֵ��������
void inorder(BTNode* root, int* arr, int* pi)
{
	if (root == NULL)//�����Ϊ�գ�ֱ�ӷ���
		return;
	inorder(root->left, arr, pi);//�Ƚ��������н���ֵ��������
	arr[(*pi)++] = root->data;//�ٽ�������ֵ��������
	inorder(root->right, arr, pi);//����������н���ֵ��������
}
//�������
int* inorderTraversal(BTNode* root, int* returnSize)
{
	*returnSize = TreeSize(root);//ֵ�ĸ������ڽ��ĸ���
	int* arr = (int*)malloc(sizeof(int)*(*returnSize));
	int i = 0;
	preorder(root, arr, &i);//�����н���ֵ��������
	return arr;
}

////�����Ľ�����
//int TreeSize(BTNode* root)
//{
//	return root == NULL ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
//}
//�����н���ֵ��������
void postorder(BTNode* root, int* arr, int* pi)
{
	if (root == NULL)//�����Ϊ�գ�ֱ�ӷ���
		return;
	postorder(root->left, arr, pi);//�Ƚ��������н���ֵ��������
	postorder(root->right, arr, pi);//�ٽ��������н���ֵ��������
	arr[(*pi)++] = root->data;//��󽫸�����ֵ��������
}
//�������
int* postorderTraversal(BTNode* root, int* returnSize)
{
	*returnSize = TreeSize(root);//ֵ�ĸ������ڽ��ĸ���
	int* arr = (int*)malloc(sizeof(int)*(*returnSize));
	int i = 0;
	preorder(root, arr, &i);//�����н���ֵ��������
	return arr;
}

//��ת������
BTNode* invertTree(BTNode* root)
{
	if (root == NULL)//��Ϊ�գ�ֱ�ӷ���
		return NULL;
	BTNode* left = invertTree(root->left);//��ת������
	BTNode* right = invertTree(root->right);//��ת������
	//��������λ�ý���
	root->left = right;
	root->right = left;
	return root;
}

//�ж϶Գ�λ���Ƿ���������
bool travel(BTNode* left, BTNode* right)
{
	if (left == NULL&&right == NULL)//������Ҷ�ӽ�㶼��ͬ���ǶԳƶ�����
		return true;
	if (left == NULL || right == NULL)//���Ҷ�Ӧ��ָ��һ������һ�������ڣ����ǶԳƶ�����
		return false;
	if (left->data != right->data)//���Ҷ�Ӧ����ֵ��ͬ�����ǶԳƶ�����
		return false;
	//��һֱ����������������һֱ��������������������ͬ�����ǶԳƶ�����
	return travel(left->left, right->right) && travel(left->right, right->left);
}
//�Գƶ�����
bool isSymmetric(BTNode* root)
{
	if (root == NULL)//�����ǶԳƶ�����
		return true;
	return travel(root->left, root->right);//�ж϶Գ�λ���Ƿ���������
}

//�Ƚ���root��subRootΪ�������������Ƿ����
bool Compare(BTNode* root, BTNode* subRoot)
{
	if (root == NULL&&subRoot == NULL)//��Ϊ���������
		return true;
	if (root == NULL || subRoot == NULL)//һ��Ϊ����һ����Ϊ�գ������
		return false;
	if (root->data != subRoot->data)//����ֵ��ͬ�������
		return false;
	//�Ƚ����������ӽ��
	return Compare(root->left, subRoot->left) && Compare(root->right, subRoot->right);
}
//��һ����������
bool isSubtree(BTNode* root, BTNode* subRoot)
{
	if (root == NULL)//��һ���������꣬û���ҵ���ڶ�������ͬ������
		return false;
	if (Compare(root, subRoot))//��root��subRootΪ������ʼ�Ƚ��������Ƿ���ͬ
		return true;
	//�ж�root�������������������Ƿ���ĳһ��������subRoot��ͬ
	return isSubtree(root->left, subRoot) || isSubtree(root->right,subRoot);
}

//�ж϶������Ƿ���ƽ�������
bool isBalanced(BTNode* root)
{
	if (root == NULL)//������ƽ�������
		return true;

	int leftDepth = BinaryTreeMaxDepth(root->left);//�������������
	int rightDepth = BinaryTreeMaxDepth(root->right);//�������������
	//���������߶Ȳ�ľ���ֵ������1 && ����������ƽ������� && ����������ƽ�������
	return abs(leftDepth - rightDepth) < 2 && isBalanced(root->left) && isBalanced(root->right);
}


bool _isBalanced(BTNode* root, int* ph)
{
	if (root == NULL)//������ƽ�������
	{
		*ph = 0;//�������ظ߶�Ϊ0
		return true;
	}
	//���ж�������
	int leftHight = 0;
	if (_isBalanced(root->left, &leftHight) == false)
		return false;
	//���ж�������
	int rightHight = 0;
	if (_isBalanced(root->right, &rightHight) == false)
		return false;
	//�����������ĸ߶��еĽϴ�ֵ+1��Ϊ��ǰ���ĸ߶ȷ��ظ���һ��
	*ph = Max(leftHight, rightHight) + 1;

	return abs(leftHight - rightHight) < 2;//ƽ�������������
}
//�ж϶������Ƿ���ƽ�������
bool isBalanced(BTNode* root)
{
	int hight = 0;
	return _isBalanced(root, &hight);
}


//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct TreeNode
//{
//    struct TreeNode* left;
//    struct TreeNode* right;
//    char data;
//}TreeNode;
//
//TreeNode* CreateTree(char* str, int* pi)
//{
//    if(str[*pi] == '#')//
//    {
//        (*pi)++;
//        return NULL;
//    }
//    //����NULL���������
//    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
//    root->left = NULL;
//    root->right = NULL;
//    root->data = str[*pi];
//    (*pi)++;
//    //�ݹ鹹��������
//    root->left = CreateTree(str, pi);
//    //�ݹ鹹��������
//    root->right = CreateTree(str, pi);
//    return root;
//}
////�������
//void Inorder(TreeNode* root)
//{
//    if(root == NULL)
//        return;
//    Inorder(root->left);
//    printf("%c ", root->data);
//    Inorder(root->right);
//}
//int main()
//{
//    char str[100];
//    scanf("%s", str);
//    int i = 0;
//    TreeNode* root = CreateTree(str, &i);
//    Inorder(root);
//    return 0;
//}