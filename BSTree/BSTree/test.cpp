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

bool FindPath(TreeNode* root, TreeNode* x, stack<TreeNode*>& path)
{
	if (root == nullptr)
		return false;
	if (root == x)
		return true;
	path.push(root);
	bool leftfind = FindPath(root->left, x, path);
	if (leftfind)
		return true;
	bool rightfind = FindPath(root->right, x, path);
	if (rightfind)
		return true;
	return true;
}