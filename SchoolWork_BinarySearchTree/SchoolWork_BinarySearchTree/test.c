#include "BSTree.h"

void Test1()
{
	BTNode* p = NULL;
	p = Insert(p, 10);
	p = Insert(p, 2);
	p = Insert(p, 35);
	p = Insert(p, 4);
	p = Insert(p, 5);
	//BinaryLevelOrder(p);
	BTNode* find = Find(p, 35);
	printf("%d\n", find->data);
	find = Find(p, 1);
	if (find == NULL)
	{
		printf("查找失败\n");
	}
	else
	{
		printf("%d\n", find->data);
	}
}
// 要删除的是叶结点
void TestDelete1(BTNode* p)
{
	printf("删除叶子结点35后:>\n");
	p = Delete(p, 35);
	BinaryLevelOrder(p);
}
// 要删除的结点只有一个孩子结点
void TestDelete2(BTNode* p)
{
	printf("删除只有一个孩子的结点33后:>\n");
	p = Delete(p, 33);
	BinaryLevelOrder(p);
}
// 要删除的结点有左、右两棵子树
void TestDelete3(BTNode* p)
{
	p = Insert(p, 34);
	printf("插入元素34后:>\n");
	BinaryLevelOrder(p);

	printf("删除有两个孩子的结点41后:>\n");
	p = Delete(p, 41);
	BinaryLevelOrder(p);
}

void Test2()
{
	BTNode* p = NULL;
	p = Insert(p, 30);
	p = Insert(p, 15);
	p = Insert(p, 41);
	p = Insert(p, 50);
	p = Insert(p, 33);
	printf("原二叉搜索树为:>\n");
	printf("层序遍历:>");
	BinaryLevelOrder(p);
	printf("中序遍历:>");
	BinaryInOrder(p);
	printf("\n");

	p = Insert(p, 35);
	printf("插入元素35后:>\n");
	printf("层序遍历:>");
	BinaryLevelOrder(p);
	printf("中序遍历:>");
	BinaryInOrder(p);
	printf("\n");

	// 递归测试
	//BTNode* pmax = FindMax(p);
	//BTNode* pmin = FindMin(p);
	// 非递归测试
	BTNode* pmax = FindMaxNonR(p);
	BTNode* pmin = FindMinNonR(p);
	printf("最大元素为:>%d\n", pmax->data);
	printf("最小元素为:>%d\n", pmin->data);

	// 要删除的是叶结点
	//TestDelete1(p);
	// 要删除的结点只有一个孩子结点
	TestDelete2(p);
	// 要删除的结点有左、右两棵子树
	//TestDelete3(p);
}

int main()
{
	Test2();
	return 0;
}