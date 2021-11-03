#include <iostream>
using namespace std;

template<class K>
struct BSTreeNode
{
	K _key;                 //结点值
	BSTreeNode<K>* _left;   //左指针 
	BSTreeNode<K>* _right;  //右指针

	//构造一个值为key，左右指针为空的结点
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
		if (root == nullptr) //空树直接返回
			return nullptr;

		Node* copyNode = new Node(root->_key); //拷贝根结点
		copyNode->_left = _Copy(root->_left); //拷贝左子树
		copyNode->_right = _Copy(root->_right); //拷贝右子树
		return copyNode; //返回拷贝的树
	}
	//拷贝构造函数
	BSTree(const BSTree<K>& t)
	{
		_root = _Copy(t._root); //拷贝t对象的二叉搜索树
	}

	//赋值运算符重载函数
	//现代写法
	BSTree<K>& operator=(BSTree<K> t) //编译器接收右值的时候自动调用拷贝构造函数
	{
		swap(_root, t._root); //交换这两个对象的二叉搜索树
		return *this; //支持连续赋值
	}

	////传统写法
	//const BSTree<K>& operator=(const BSTree<K>& t)
	//{
	//	if (this != &t) //防止自己给自己赋值
	//	{
	//		_root = _Copy(t._root); //拷贝t对象的二叉搜索树
	//	}
	//	return *this; //支持连续赋值
	//}

	//释放树中结点
	void _Destory(Node* root)
	{
		if (root == nullptr) //空树无需释放
			return;

		_Destory(root->_left); //释放左子树中的结点
		_Destory(root->_right); //释放右子树中的结点
		delete root; //释放根结点
	}
	//析构函数
	~BSTree()
	{
		_Destory(_root); //释放二叉搜索树中的结点
		_root = nullptr; //及时置空
	}

	//插入函数
	bool Insert(const K& key)
	{
		if (_root == nullptr) //空树
		{
			_root = new Node(key); //直接申请值为key的结点作为二叉搜索树的根结点
			return true; //插入成功，返回true
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key) //key值小于当前结点的值
			{
				//往该结点的左子树走
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key) //key值大于当前结点的值
			{
				//往该结点的右子树走
				parent = cur;
				cur = cur->_right;
			}
			else //key值等于当前结点的值
			{
				return false; //插入失败，返回false
			}
		}
		cur = new Node(key); //申请值为key的结点
		if (key < parent->_key) //key值小于当前parent结点的值
		{
			parent->_left = cur; //将结点连接到parent的左边
		}
		else //key值大于当前parent结点的值
		{
			parent->_right = cur; //将结点连接到parent的右边
		}
		return true; //插入成功，返回true
	}
	//递归插入函数的子函数
	bool _InsertR(Node*& root, const K& key) //注意引用
	{
		if (root == nullptr) //空树
		{
			root = new Node(key); //直接申请值为key的结点作为树的根结点
			return true; //插入成功，返回true
		}

		if (key < root->_key) //key值小于根结点的值
		{
			return _InsertR(root->_left, key); //应将结点插入到左子树当中
		}
		else if (key > root->_key) //key值大于根结点的值
		{
			return _InsertR(root->_right, key); //应将结点插入到右子树当中
		}
		else //key值等于根结点的值
		{
			return false; //插入失败，返回false
		}
	}
	//递归插入函数
	bool InsertR(const K& key)
	{
		return _InsertR(_root, key); //调用子函数进行插入
	}
	//删除函数1
	bool Erase(const K& key)
	{
		Node* parent = nullptr; //标记待删除结点的父结点
		Node* cur = _root; //标记待删除结点
		while (cur)
		{
			if (key < cur->_key) //key值小于当前结点的值
			{
				//往该结点的左子树走
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key) //key值大于当前结点的值
			{
				//往该结点的右子树走
				parent = cur;
				cur = cur->_right;
			}
			else //找到了待删除结点
			{
				if (cur->_left == nullptr) //待删除结点的左子树为空
				{
					if (cur == _root) //待删除结点是根结点，此时parent为nullptr
					{
						_root = cur->_right; //二叉搜索树的根结点改为根结点的右孩子即可
					}
					else //待删除结点不是根结点，此时parent不为nullptr
					{
						if (cur == parent->_left) //待删除结点是其父结点的左孩子
						{
							parent->_left = cur->_right; //父结点的左指针指向待删除结点的右子树即可
						}
						else //待删除结点是其父结点的右孩子
						{
							parent->_right = cur->_right; //父结点的右指针指向待删除结点的右子树即可
						}
					}
					delete cur; //释放待删除结点
					return true; //删除成功，返回true
				}
				else if (cur->_right == nullptr) //待删除结点的右子树为空
				{
					if (cur == _root) //待删除结点是根结点，此时parent为nullptr
					{
						_root = cur->_left; //二叉搜索树的根结点改为根结点的左孩子即可
					}
					else //待删除结点不是根结点，此时parent不为nullptr
					{
						if (cur == parent->_left) //待删除结点是其父结点的左孩子
						{
							parent->_left = cur->_left; //父结点的左指针指向待删除结点的左子树即可
						}
						else //待删除结点是其父结点的右孩子
						{
							parent->_right = cur->_left; //父结点的右指针指向待删除结点的左子树即可
						}
					}
					delete cur; //释放待删除结点
					return true; //删除成功，返回true
				}
				else //待删除结点的左右子树均不为空
				{
					//替换法删除
					Node* minParent = cur; //标记待删除结点右子树当中值最小结点的父结点
					Node* minRight = cur->_right; //标记待删除结点右子树当中值最小的结点
					//寻找待删除结点右子树当中值最小的结点
					while (minRight->_left)
					{
						//一直往左子树走
						minParent = minRight;
						minRight = minRight->_left;
					}
					cur->_key = minRight->_key; //将待删除结点的值改为minRight的值
					//注意一个隐含条件：此时minRight的_left为空
					if (minRight == minParent->_left) //minRight是其父结点的左孩子
					{
						minParent->_left = minRight->_right; //父结点的左指针指向minRight的右子树即可
					}
					else //minRight是其父结点的右孩子
					{
						minParent->_right = minRight->_right; //父结点的右指针指向minRight的右子树即可
					}
					delete minRight; //释放minRight
					return true; //删除成功，返回true
				}
			}
		}
		return false; //没有找到待删除结点，删除失败，返回false
	}

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
	//				Node* minRight = cur->_right;
	//				while (minRight->_left)
	//				{
	//					minRight = minRight->_left;
	//				}
	//				K minKey = minRight->_key;
	//				Erase(minKey); //this->Erase(minKey);
	//				cur->_key = minKey;
	//			}
	//		}
	//	}
	//	return false;
	//}

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
		_InOrder(root->_left); //遍历左子树
		cout << root->_key << " "; //遍历根结点
		_InOrder(root->_right); //遍历右子树
	}
	//中序遍历
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
private:
	Node* _root; //二叉搜索树的根结点
};





////结点类
//template<class K>
//struct BSTreeNode
//{
//	K _key;                 //结点值
//	BSTreeNode<K>* _left;   //左指针 
//	BSTreeNode<K>* _right;  //右指针
//
//	//构造函数
//	BSTreeNode(const K& key = 0)
//		:_key(key)
//		, _left(nullptr)
//		, _right(nullptr)
//	{}
//};

////二叉搜索树
//template<class K>
//class BSTree
//{
//	typedef BSTreeNode<K> Node;
//public:
//	//构造函数
//	BSTree();
//
//	//拷贝构造函数
//	BSTree(const BSTree<K>& t);
//
//	//赋值运算符重载函数
//	BSTree<K>& operator=(BSTree<K> t);
//
//	//析构函数
//	~BSTree();
//
//	//插入函数
//	bool Insert(const K& key);
//
//	//删除函数
//	bool Erase(const K& key);
//
//	//查找函数
//	Node* Find(const K& key);
//
//	//中序遍历
//	void InOrder();
//private:
//	Node* _root; //指向二叉搜索树的根结点
//};










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