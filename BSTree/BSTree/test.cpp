#include "BSTree.h"
int main()
{
	BSTree<int> t;
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	for (auto e : arr)
	{
		t.Insert(e);
	}
	t.InOrder();
	
	BSTree<int> tmp;
	int arr2[] = { 51, 13, 14, 31, 17, 18, 12, 16, 10, 19 };
	for (auto e : arr2)
	{
		tmp.Insert(e);
	}
	tmp.InOrder();
	tmp = t;
	tmp.InOrder();

	//BSTree<int> c(t);
	//c.Insert(10);
	//c.InOrder();

	//BSTree<int> f;
	//f = t;
	//f.Insert(11);
	//f.InOrder();

	//t.EraseR(5);
	//t.InOrder();

	//t.EraseR(3);
	//t.InOrder();

	//t.EraseR(4);
	//t.InOrder();

	//t.EraseR(1);
	//t.InOrder();

	//t.EraseR(7);
	//t.InOrder();

	//t.EraseR(8);
	//t.InOrder();

	//t.EraseR(2);
	//t.InOrder();

	//t.EraseR(6);
	//t.InOrder();

	//t.EraseR(9);
	//t.InOrder();

	//t.EraseR(0);
	//t.InOrder();
	//for (auto e : arr)
	//{
	//	t.Erase(e);
	//	t.InOrder();
	//}

	return 0;
}



//bool EraseR(Node*& root, const K& key)
//{
//	if (root == nullptr)
//		return false;
//
//	if (root->_key < key)
//	{
//		return EraseR(root->_right, key);
//	}
//	else if (root->_key > key)
//	{
//		return EraseR(root->_left, key);
//	}
//	else
//	{
//		if (root->_left == nullptr)
//		{
//			Node* tmp = root;
//			root = root->_right;
//			delete tmp;
//			return true;
//		}
//		else if (root->_right == nullptr)
//		{
//			Node* tmp = root;
//			root = root->_left;
//			delete tmp;
//			return true;
//		}
//		else
//		{
//			Node* minRight = root->
//
//		}
//	}
//}

//bool FindPath(TreeNode* root, TreeNode* x, stack<TreeNode*>& path)
//{
//	if (root == nullptr)
//		return false;
//	if (root == x)
//		return true;
//	path.push(root);
//	bool leftfind = FindPath(root->left, x, path);
//	if (leftfind)
//		return true;
//	bool rightfind = FindPath(root->right, x, path);
//	if (rightfind)
//		return true;
//	return true;
//}