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
	t.Erase(5);
	t.InOrder();

	t.Erase(3);
	t.InOrder();

	t.Erase(4);
	t.InOrder();

	t.Erase(1);
	t.InOrder();

	t.Erase(7);
	t.InOrder();

	t.Erase(8);
	t.InOrder();

	t.Erase(2);
	t.InOrder();

	t.Erase(6);
	t.InOrder();

	t.Erase(9);
	t.InOrder();

	t.Erase(0);
	t.InOrder();
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