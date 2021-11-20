#include <iostream>
#include <stack>
using namespace std;
//������
//struct TreeNode {
//    int val;
//    TreeNode *left;
//    TreeNode *right;
//	TreeNode *parent;
//    TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
//};
//class Solution {
//public:
//	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//		TreeNode* curp = p, *curq = q; //���ڱ���p��q�������Ƚ��
//		int lenp = 0, lenq = 0; //�ֱ��¼p��q�����Ե����Ƚ�����
//		//ͳ��p�������Ƚ�����
//		while (curp != root)
//		{
//			lenp++;
//			curp = curp->parent;
//		}
//		//ͳ��q�������Ƚ�����
//		while (curq != root)
//		{
//			lenq++;
//			curq = curq->parent;
//		}
//		//longpath��shortpath�ֱ�������·���ϳ��ͽ϶̵Ľ��
//		TreeNode* longpath = p, *shortpath = q;
//		if (lenp < lenq)
//		{
//			longpath = q;
//			shortpath = p;
//		}
//		//p��q������Ƚ������Ĳ�ֵ
//		int count = abs(lenp - lenq);
//		//����longpath������count�����
//		while (count--)
//		{
//			longpath = longpath->parent;
//		}
//		//����longpath��shortpathͬʱ�����ߣ���ʱ��һ����ͬ�Ľ���������������Ƚ��
//		while (longpath != shortpath)
//		{
//			longpath = longpath->parent;
//			shortpath = shortpath->parent;
//		}
//		return longpath; //��������������Ƚ��
//	}
//};
//void test1()
//{
//	TreeNode d3(3);
//	TreeNode d5(5);
//	TreeNode d1(1);
//	TreeNode d6(6);
//	TreeNode d2(2);
//	TreeNode d0(0);
//	TreeNode d8(8);
//	TreeNode d7(7);
//	TreeNode d4(4);
//	d3.left = &d5;
//	d3.right = &d1;
//	d5.left = &d6;
//	d5.right = &d2;
//	d1.left = &d0;
//	d1.right = &d8;
//	d2.left = &d7;
//	d2.right = &d4;
//
//	d5.parent = &d3;
//	d1.parent = &d3;
//	d6.parent = &d5;
//	d2.parent = &d5;
//	d0.parent = &d1;
//	d8.parent = &d1;
//	d7.parent = &d2;
//	d4.parent = &d2;
//	cout << Solution().lowestCommonAncestor(&d3, &d7, &d4)->val << endl;
//}

////����������
//struct TreeNode {
//	int val;
//	TreeNode *left;
//	TreeNode *right;
//	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
//};
//class Solution {
//public:
//	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//		if (p->val == root->val || q->val == root->val) //p��q�����ĳһ������ֵ���ڸ�����ֵ��������������������������������
//			return root;
//		if (p->val < root->val&&q->val < root->val) //p��q����ֵ��С�ڸ�����ֵ��˵������������������������ڸ���������������
//			return lowestCommonAncestor(root->left, p, q);
//		else if (p->val > root->val&&q->val > root->val) //p��q����ֵ�����ڸ�����ֵ��˵������������������������ڸ���������������
//			return lowestCommonAncestor(root->right, p, q);
//		else //p��q����ֵһ���ȸ�Сһ���ȸ���˵�����������������������������
//			return root;
//	}
//};
//void test2()
//{
//	TreeNode d5(5);
//	TreeNode d1(1);
//	TreeNode d7(7);
//	TreeNode d0(0);
//	TreeNode d3(3);
//	TreeNode d6(6);
//	TreeNode d8(8);
//	TreeNode d2(2);
//	TreeNode d4(4);
//
//	d5.left = &d1;
//	d5.right = &d7;
//	d1.left = &d0;
//	d1.right = &d3;
//	d7.left = &d6;
//	d7.right = &d8;
//	d3.left = &d2;
//	d3.right = &d4;
//
//	cout << Solution().lowestCommonAncestor(&d5, &d0, &d5)->val << endl;
//}

//��ͨ������
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//class Solution {
//public:
//	bool Find(TreeNode* root, TreeNode* x)
//	{
//		if (root == nullptr) //����������ʧ��
//			return false;
//		if (root == x) //���ҳɹ�
//			return true;
//
//		return Find(root->left, x) || Find(root->right, x); //���������ҵ��˻����������ҵ��ˣ���˵���ý���ڸ�������
//	}
//	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//		if (p == root || q == root) //p��q�����ĳһ�����Ϊ����㣬������������������������������
//			return root;
//		//�ж�p��q����Ƿ�����������
//		bool IspInLeft, IspInRight, IsqInLeft, IsqInRight;
//		IspInLeft = Find(root->left, p);
//		IspInRight = !IspInLeft;
//		IsqInLeft = Find(root->left, q);
//		IsqInRight = !IsqInLeft;
//
//		if (IspInLeft&&IsqInLeft) //p��q��㶼����������˵�����������������������Ҳ������������
//			return lowestCommonAncestor(root->left, p, q);
//		else if (IspInRight&&IsqInRight) //p��q��㶼����������˵�����������������������Ҳ������������
//			return lowestCommonAncestor(root->right, p, q);
//		else //p��q���һ����������һ������������˵�����������������������������
//			return root;
//	}
//};
class Solution {
public:
	bool FindPath(TreeNode* root, TreeNode* x, stack<TreeNode*>& path)
	{
		if (root == nullptr)
			return false;
		path.push(root); //�ý�������·�����еĽ�㣬����ջ

		if (root == x) //�ý�������ս�㣬���ҽ���
			return true;

		if (FindPath(root->left, x, path)) //�ڸý����������ҵ������ս�㣬���ҽ���
			return true;
		if (FindPath(root->right, x, path)) //�ڸý����������ҵ������ս�㣬���ҽ���
			return true;

		path.pop(); //�ڸý�������������û���ҵ����ս�㣬�ý�㲻������·�����еĽ�㣬�ý���ջ
		return false; //�ڸý�㴦����ʧ��
	}
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		stack<TreeNode*> pPath, qPath;
		FindPath(root, p, pPath); //���Ӹ���p����·����ŵ�pPath����
		FindPath(root, q, qPath); //���Ӹ���q����·����ŵ�qPath����
		//longpath��shortpath�ֱ��ǳ�·���Ͷ�·��
		stack<TreeNode*>* longPath = &pPath, *shortPath = &qPath;
		if (pPath.size() < qPath.size())
		{
			longPath = &qPath;
			shortPath = &pPath;
		}
		//��longPath�ȵ�����ֵ������
		int count = longPath->size() - shortPath->size();
		while (count--)
		{
			longPath->pop();
		}
		//longPath��shortPathһ�����ݣ�ֱ������ջ���Ľ����ͬ
		while (longPath->top() != shortPath->top())
		{
			longPath->pop();
			shortPath->pop();
		}
		return longPath->top(); //���������ͬ�Ľ�㣬�������������
	}
};
void test3()
{
	TreeNode d3(3);
	TreeNode d5(5);
	TreeNode d1(1);
	TreeNode d6(6);
	TreeNode d2(2);
	TreeNode d0(0);
	TreeNode d8(8);
	TreeNode d7(7);
	TreeNode d4(4);
	d3.left = &d5;
	d3.right = &d1;
	d5.left = &d6;
	d5.right = &d2;
	d1.left = &d0;
	d1.right = &d8;
	d2.left = &d7;
	d2.right = &d4;

	cout << Solution().lowestCommonAncestor(&d3, &d7, &d6)->val << endl;
}
int main()
{
	//test1();
	//test2();
	test3();
	return 0;
}