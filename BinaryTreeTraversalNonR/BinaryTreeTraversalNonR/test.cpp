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
	//ǰ�����
	vector<int> preorderTraversal(TreeNode* root) {
		stack<TreeNode*> st; //����ջ
		vector<int> ret; //���ڴ��ǰ������Ľ��
		TreeNode* cur = root;
		while (cur || !st.empty())
		{
			//1������·�����ջ����ջ��ͬʱ������·���
			while (cur)
			{
				st.push(cur);
				ret.push_back(cur->val);
				cur = cur->left;
			}
			//2��ȡ��ջ�����
			TreeNode* top = st.top();
			st.pop();
			//3��׼��������������
			cur = top->right;
		}
		return ret; //����ǰ��������
	}

	//�������
	vector<int> inorderTraversal(TreeNode* root) {
		stack<TreeNode*> st; //����ջ
		vector<int> ret; //���ڴ����������Ľ��
		TreeNode* cur = root;
		while (cur || !st.empty())
		{
			//1������·�����ջ
			while (cur)
			{
				st.push(cur);
				cur = cur->left;
			}
			//2��ȡ��ջ����㲢����
			TreeNode* top = st.top();
			st.pop();
			ret.push_back(top->val);
			//3��׼��������������
			cur = top->right;
		}
		return ret; //��������������
	}

	//�������
	vector<int> postorderTraversal(TreeNode* root) {
		stack<TreeNode*> st; //����ջ
		vector<int> ret; //���ڴ�ź�������Ľ��
		TreeNode* cur = root;
		TreeNode* prev = nullptr; //��¼��һ�η��ʵĽ��
		while (cur || !st.empty())
		{
			//1������·�����ջ
			while (cur)
			{
				st.push(cur);
				cur = cur->left;
			}
			//2��ȡ��ջ�����
			TreeNode* top = st.top();
			//3����ȡ������������Ϊ�գ����������Ѿ����ʹ��ˣ�����ʸý��
			if (top->right == nullptr || top->right == prev)
			{
				//���ý���ջ�е���������
				st.pop();
				ret.push_back(top->val);
				//������һ�η��ʵĽ��
				prev = top;
			}
			else //4����ȡ��������������Ҫ�����ʣ���׼��������������
			{
				cur = top->right;
			}
		}
		return ret; //���غ���������
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
////������
//TreeNode* CreateTree(char* str, int* pi)
//{
//	if (str[*pi] == '#')//
//	{
//		(*pi)++;
//		return NULL;
//	}
//	//����NULL���������
//	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
//	root->left = NULL;
//	root->right = NULL;
//	root->data = str[*pi];
//	(*pi)++;
//	//�ݹ鹹��������
//	root->left = CreateTree(str, pi);
//	//�ݹ鹹��������
//	root->right = CreateTree(str, pi);
//	return root;
//}
////�������
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
