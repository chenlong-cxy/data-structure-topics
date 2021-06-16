#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef char BTDataType;//����д洢��Ԫ�����ͣ���charΪ����

typedef struct BTNode
{
	BTDataType data;//����д洢��Ԫ������
	struct BTNode* left;//��ָ����ָ�����ӣ�
	struct BTNode* right;//��ָ����ָ���Һ��ӣ�
}BTNode;

//�������
//ǰ�����
void BinaryPrevOrder(BTNode* root);
//�������
void BinaryInOrder(BTNode* root);
//�������
void BinaryPostOrder(BTNode* root);
//�������
//�������
void BinaryLevelOrder(BTNode* root);

//���ĸ���
int BinaryTreeSize(BTNode* root);
//Ҷ�ӽ��ĸ���
int BinaryTreeLeafSize(BTNode* root);
//��k����ĸ���
int BinaryTreeKLevelSize(BTNode* root, int k);

//����ֵΪx�Ľ��
BTNode* BinaryTreeFind(BTNode* root, BTDataType x);
//����������
int BinaryTreeMaxDepth(BTNode* root);

//����������
void BinaryTreeDestroy(BTNode* root);
//void BinaryTreeDestroy(BTNode** root);
//void BinaryTreeDestroy(BTNode*& root);//ȡ����

//�ж϶������Ƿ�����ȫ������
bool isCompleteTree(BTNode* root);
//�ж϶������Ƿ��ǵ�ֵ������
bool isUnivalTree(BTNode* root);
//�ж����ö������Ƿ���ͬ
bool isSameTree(BTNode* p, BTNode* q);
//�ж϶������Ƿ���ƽ�������
bool isBalanced(BTNode* root);

//ǰ�����
int* preorderTraversal(BTNode* root, int* returnSize);
//�������
int* inorderTraversal(BTNode* root, int* returnSize);
//�������
int* postorderTraversal(BTNode* root, int* returnSize);

//��ת������
BTNode* invertTree(BTNode* root);
//�Գƶ�����
bool isSymmetric(BTNode* root);
//��һ����������
bool isSubtree(BTNode* root, BTNode* subRoot);