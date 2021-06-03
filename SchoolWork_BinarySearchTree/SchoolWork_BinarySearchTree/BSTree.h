#include <stdio.h>
#include <stdlib.h>

typedef int BTDataType;

typedef struct BTNode
{
	BTDataType data;
	struct BTNode* left;
	struct BTNode* right;
}BTNode;

//����
BTNode* Insert(BTNode* root, BTDataType x);
//ɾ��
BTNode* Delete(BTNode* root, BTDataType x);

//���ң��ݹ飩
BTNode* Find(BTNode* root, BTDataType x);
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

//�������
void BinaryLevelOrder(BTNode* root);