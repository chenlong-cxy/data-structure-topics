#include "BinaryTree.h"

//主程序示例
int main() 
{
	char arr[] = "ABC##DE#G##F###";
	int i = 0;
	TreeNode* root = PreCreateTree(arr, &i);

	printf("前序遍历结果为:>\n");
	PreOrderTree(root);
	printf("\n");

	printf("中序遍历结果为:>\n");
	InOrderTree(root);
	printf("\n");

	printf("后序遍历结果为:>\n");
	PostOrderTree(root);
	printf("\n");

	printf("树的结点个数为:>");
	printf("%d\n", CountNode(root));

	printf("树的高度为:>");
	printf("%d\n", TreeDepth(root));

	return 0;
}