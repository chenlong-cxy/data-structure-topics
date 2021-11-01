#include <iostream>
using namespace std;

template<class K>
struct BSTreeNode
{
	K _key;
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;

	BSTreeNode(const K& key = 0)
		:_key(key)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	//构造函数
	BSTree()
		:_root(nullptr)
	{}

	//拷贝树
	Node* _Copy(Node* root)
	{
		if (root == nullptr)
			return nullptr;

		Node* copyNode = new Node(root->_key);
		copyNode->_left = _Copy(root->_left);
		copyNode->_right = _Copy(root->_right);
		return copyNode;
	}
	//拷贝构造函数
	BSTree(const BSTree<K>& t)
	{
		_root = _Copy(t._root);
	}

	//赋值运算符重载函数
	BSTree<K>& operator=(BSTree<K> t)
	{
		swap(_root, t._root);
		return *this;
	}

	//const BSTree<K>& operator=(const BSTree<K>& t)
	//{
	//	if (this != &t)
	//	{
	//		_root = _Copy(t._root);
	//	}
	//	return *this;
	//}

	//析构函数的子函数
	void _Destory(Node* root)
	{
		if (root == nullptr)
			return;

		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}
	//析构函数
	~BSTree()
	{
		_Destory(_root);
		_root = nullptr;
	}

	//插入函数
	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key);
		if (key < parent->_key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		return true;
	}
	//递归插入函数的子函数
	bool _InsertR(Node*& root, const K& key) //注意引用
	{
		if (root == nullptr)
		{
			root = new Node(key);
			return true;
		}

		if (key < root->_key)
			return _Insert(root->_left, key);
		else if (key > root->_key)
			return _Insert(root->_right, key);
		else
			return false;
	}
	//递归插入函数
	bool InsertR(const K& key)
	{
		return _Insert(_root, key);
	}
	//删除函数1
	//bool Erase(const K& key)
	//{
	//	Node* parent = nullptr;
	//	Node* cur = _root;
	//	while (cur)
	//	{
	//		if (key < cur->_key)
	//		{
	//			parent = cur;
	//			cur = cur->_left;
	//		}
	//		else if (key > cur->_key)
	//		{
	//			parent = cur;
	//			cur = cur->_right;
	//		}
	//		else
	//		{
	//			//找到了
	//			if (cur->_left == nullptr)
	//			{
	//				if (cur == _root)
	//				{
	//					_root = cur->_right;
	//				}
	//				else
	//				{
	//					if (parent->_left == cur)
	//					{
	//						parent->_left = cur->_right;
	//					}
	//					else
	//					{
	//						parent->_right = cur->_right;
	//					}
	//				}
	//				delete cur;
	//				return true;
	//			}
	//			else if (cur->_right == nullptr)
	//			{
	//				if (cur == _root)
	//				{
	//					_root = cur->_left;
	//				}
	//				else
	//				{
	//					if (parent->_left = cur)
	//					{
	//						parent->_left = cur->_left;
	//					}
	//					else
	//					{
	//						parent->_right = cur->_left;
	//					}
	//				}
	//				delete cur;
	//				return true;
	//			}
	//			else
	//			{
	//				Node* minParent = cur;
	//				Node* minRight = cur->_right;
	//				while (minRight->_left)
	//				{
	//					minParent = minRight;
	//					minRight = minRight->_left;
	//				}
	//				cur->_key = minRight->_key;
	//				if (minParent->_left == minRight)
	//				{
	//					minParent->_left = minRight->_right;
	//				}
	//				else
	//				{
	//					minParent->_right = minRight->_right;
	//				}

	//				delete minRight;
	//				return true;
	//			}
	//		}
	//	}
	//	return false;
	//}

	////递归删除函数1的子函数(待查)
	//bool _EraseR(Node*& root, const K& key)
	//{
	//	if (root == nullptr)
	//		return false;

	//	if (key < root->_key)
	//		return _EraseR(root->_left, key);
	//	else if (key > root->_key)
	//		return _EraseR(root->_right, key);
	//	else
	//	{
	//		//找到了
	//		if (root->_left == nullptr)
	//		{
	//			Node* del = root;
	//			root = root->_right;
	//			delete del;
	//		}
	//		else if (root->_right == nullptr)
	//		{
	//			Node* del = root;
	//			root = root->_left;
	//			delete del;
	//		}
	//		else
	//		{
	//			Node* minParent = root;
	//			Node* minRight = root->_right;
	//			while (minRight->_left)
	//			{
	//				minParent = minRight;
	//				minRight = minRight->_left;
	//			}
	//			root->_key = minRight->_key;
	//			if (minRight == minParent->_left)
	//				minParent->_left = minRight->_right;
	//			else
	//				minParent->_right = minRight->_right;
	//			delete minRight;
	//		}
	//		return true;
	//	}
	//}
	////递归删除函数1
	//bool EraseR(const K& key)
	//{
	//	return _EraseR(_root, key);
	//}

	//删除函数2
	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				//找到了
				if (cur->_left == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
					}
					delete cur;
					return true;
				}
				else if (cur->_right == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_left;
					}
					else
					{
						if (parent->_left = cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
					delete cur;
					return true;
				}
				else
				{
					Node* minRight = cur->_right;
					while (minRight->_left)
					{
						minRight = minRight->_left;
					}
					K minKey = minRight->_key;
					Erase(minKey); //this->Erase(minKey);
					cur->_key = minKey;
				}
			}
		}
		return false;
	}

	//递归删除函数2的子函数
	bool _EraseR(Node*& root, const K& key)
	{
		if (root == nullptr)
			return false;

		if (key < root->_key)
			return _EraseR(root->_left, key);
		else if (key > root->_key)
			return _EraseR(root->_right, key);
		else
		{
			//找到了
			if (root->_left == nullptr)
			{
				Node* del = root;
				root = root->_right;
				delete del;
			}
			else if (root->_right == nullptr)
			{
				Node* del = root;
				root = root->_left;
				delete del;
			}
			else
			{
				Node* minRight = root->_right;
				while (minRight->_left)
				{
					minRight = minRight->_left;
				}
				K minKey = minRight->_key;
				_EraseR(root->_right, minKey);
				root->_key = minKey;
			}
			return true;
		}
	}
	//递归删除函数2
	bool EraseR(const K& key)
	{
		return _EraseR(_root, key);
	}

	//查找函数
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else
			{
				//找到了
				return cur;
			}
		}
		return nullptr;
	}
	//递归查找函数的子函数
	Node* _FindR(Node* root, const K& key)
	{
		if (root == nullptr)
			return nullptr;

		if (key < root->_key)
			return _FindR(root->_left, key);
		else if (key > root->_key)
			return _FindR(root->_right, key);
		else
			return root;
	}
	//递归查找函数
	Node* FindR(const K& key)
	{
		return _FindR(_root, key);
	}
	//中序遍历的子函数
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	//中序遍历
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
private:
	Node* _root;
};

















//#include <iostream>
//using namespace std;
//template<class K>
//struct BSTreeNode
//{
//	K _key;
//	BSTreeNode<K>* _left;
//	BSTreeNode<K>* _right;
//	BSTreeNode(const K& key)
//		:_key(key)
//		, _left(nullptr)
//		, _right(nullptr)
//	{}
//};
//
//template<class K>
//class BSTree
//{
//	typedef BSTreeNode<K> Node;
//public:
//	//非递归
//	bool Insert(const K& key)
//	{
//		if (_root == nullptr)
//		{
//			_root = new Node(key);
//			return true;
//		}
//		Node* parent = nullptr;
//		Node* cur = _root;
//		while (cur)
//		{
//			if (key > cur->_key)
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//			else if (key < cur->_key)
//			{
//				parent = cur;
//				cur = cur->_left;
//			}
//			else
//			{
//				return false;
//			}
//		}
//		cur = new Node(key);
//		if (cur = parent->_left) //error
//		{
//			parent->_left = cur;
//		}
//		else
//		{
//			parent->_right = cur;
//		}
//		return true;
//	}
//	bool Erase(const K& key)
//	{
//		Node* parent = nullptr;
//		Node* cur = _root;
//		while (cur)
//		{
//			if (key > cur->_key)
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//			else if (key < cur->_key)
//			{
//				parent = cur;
//				cur = cur->_left;
//			}
//			else
//			{
//
//			}
//		}
//	}
//	Node* Find(const K& key)
//	{
//		Node* cur = _root;
//		while (cur)
//		{
//			if (key > cur->_key)
//			{
//				cur = cur->_right;
//			}
//			else if (key < cur->_key)
//			{
//				cur = cur->_left;
//			}
//			else
//			{
//				return cur;
//			}
//		}
//		return nullptr;
//	}
//private:
//	Node* _root;
//};