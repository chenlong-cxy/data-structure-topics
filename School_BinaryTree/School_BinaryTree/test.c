#include "BinaryTree.h"

//������ʾ��
int main() 
{
	char arr[] = "ABC##DE#G##F###";
	int i = 0;
	TreeNode* root = PreCreateTree(arr, &i);

	printf("ǰ��������Ϊ:>\n");
	PreOrderTree(root);
	printf("\n");

	printf("����������Ϊ:>\n");
	InOrderTree(root);
	printf("\n");

	printf("����������Ϊ:>\n");
	PostOrderTree(root);
	printf("\n");

	printf("���Ľ�����Ϊ:>");
	printf("%d\n", CountNode(root));

	printf("���ĸ߶�Ϊ:>");
	printf("%d\n", TreeDepth(root));

	return 0;
}