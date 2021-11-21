#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
public:
	//前序遍历
	vector<int> preorderTraversal(TreeNode* root) {
		stack<TreeNode*> st; //辅助栈
		vector<int> ret; //用于存放前序遍历的结果
		TreeNode* cur = root;
		while (cur || !st.empty())
		{
			//1、将左路结点入栈，入栈的同时访问左路结点
			while (cur)
			{
				st.push(cur);
				ret.push_back(cur->val);
				cur = cur->left;
			}
			//2、取出栈顶结点
			TreeNode* top = st.top();
			st.pop();
			//3、准备访问其右子树
			cur = top->right;
		}
		return ret; //返回前序遍历结果
	}

	//中序遍历
	vector<int> inorderTraversal(TreeNode* root) {
		stack<TreeNode*> st; //辅助栈
		vector<int> ret; //用于存放中序遍历的结果
		TreeNode* cur = root;
		while (cur || !st.empty())
		{
			//1、将左路结点入栈
			while (cur)
			{
				st.push(cur);
				cur = cur->left;
			}
			//2、取出栈顶结点并访问
			TreeNode* top = st.top();
			st.pop();
			ret.push_back(top->val);
			//3、准备访问其右子树
			cur = top->right;
		}
		return ret; //返回中序遍历结果
	}

	//后序遍历
	vector<int> postorderTraversal(TreeNode* root) {
		stack<TreeNode*> st; //辅助栈
		vector<int> ret; //用于存放后序遍历的结果
		TreeNode* cur = root;
		TreeNode* prev = nullptr; //记录上一次访问的结点
		while (cur || !st.empty())
		{
			//1、将左路结点入栈
			while (cur)
			{
				st.push(cur);
				cur = cur->left;
			}
			//2、取出栈顶结点
			TreeNode* top = st.top();
			//3、若取出结点的右子树为空，或右子树已经访问过了，则访问该结点
			if (top->right == nullptr || top->right == prev)
			{
				//将该结点从栈中弹出并访问
				st.pop();
				ret.push_back(top->val);
				//更新上一次访问的结点
				prev = top;
			}
			else //4、若取出结点的右子树需要被访问，则准备访问其右子树
			{
				cur = top->right;
			}
		}
		return ret; //返回后序遍历结果
	}
};
int main()
{
	TreeNode d5(5);
	TreeNode d3(3);
	TreeNode d7(7);
	TreeNode d1(1);
	TreeNode d4(4);
	TreeNode d8(8);
	TreeNode d6(6);

	d5.left = &d3;
	d5.right = &d7;
	d3.left = &d1;
	d3.right = &d4;
	d7.right = &d8;
	d4.left = &d6;

	vector<int> preorder = Solution().preorderTraversal(&d5);
	vector<int> inorder = Solution().inorderTraversal(&d5);
	vector<int> postorder = Solution().postorderTraversal(&d5);
	for (auto e : preorder)
	{
		cout << e << " ";
	}
	cout << endl;
	for (auto e : inorder)
	{
		cout << e << " ";
	}
	cout << endl;
	for (auto e : postorder)
	{
		cout << e << " ";
	}
	cout << endl;
	return 0;
}


//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct TreeNode
//{
//	struct TreeNode* left;
//	struct TreeNode* right;
//	char data;
//}TreeNode;
////创建树
//TreeNode* CreateTree(char* str, int* pi)
//{
//	if (str[*pi] == '#')//
//	{
//		(*pi)++;
//		return NULL;
//	}
//	//不是NULL，构建结点
//	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
//	root->left = NULL;
//	root->right = NULL;
//	root->data = str[*pi];
//	(*pi)++;
//	//递归构建左子树
//	root->left = CreateTree(str, pi);
//	//递归构建右子树
//	root->right = CreateTree(str, pi);
//	return root;
//}
////中序遍历
//void Inorder(TreeNode* root)
//{
//	if (root == NULL)
//		return;
//	Inorder(root->left);
//	printf("%c ", root->data);
//	Inorder(root->right);
//}
//int main()
//{
//	char str[100];
//	scanf("%s", str);
//	int i = 0;
//	TreeNode* root = CreateTree(str, &i);
//	Inorder(root);
//	return 0;
//}
