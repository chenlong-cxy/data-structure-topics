#pragma once
#include <iostream>
using namespace std;

//枚举定义结点的颜色
enum Colour
{
	RED,
	BLACK
};

template<class K, class V>
struct RBTreeNode
{
	//三叉链
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	//存储的键值对
	pair<K, V> _kv;

	//结点的颜色
	int _col; //红/黑

	//构造函数
	RBTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _col(RED)
	{}
};

template<class K, class V>
struct __TreeIterator
{
	typedef RBTreeNode<K, V> Node;

	Node* _node;

	__TreeIterator(Node* node)
		:_node(node)
	{}

	//operator*();
	//operator++();
	//operator--();
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	//构造函数
	RBTree()
		:_root(nullptr)
	{}
	//拷贝构造
	//operator=

	//析构函数
	~RBTree()
	{
		_Destroy(_root);
		_root = nullptr;
	}

	//查找函数
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_kv.first)
			{
				cur = cur->_left;
			}
			else if (key > cur->_kv.first)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}

	//插入函数
	pair<Node*, bool> Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr) //若红黑树为空树，则插入结点直接作为根结点
		{
			_root = new Node(kv);
			_root->_col = BLACK; //根结点必须是黑色
			return make_pair(_root, true); //插入成功
		}
		//1、按二叉搜索树的插入方法，找到待插入位置
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (kv.first < cur->_kv.first) //待插入结点的key值小于当前结点的key值
			{
				//往该结点的左子树走
				parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > cur->_kv.first) //待插入结点的key值大于当前结点的key值
			{
				//往该结点的右子树走
				parent = cur;
				cur = cur->_right;
			}
			else //待插入结点的key值等于当前结点的key值
			{
				return make_pair(cur, false); //插入失败
			}
		}

		//2、将待插入结点插入到树中
		cur = new Node(kv); //根据所给值构造一个结点
		Node* newnode = cur; //记录新插入的结点（便于后序返回）
		if (kv.first < parent->_kv.first) //新结点的key值小于parent的key值
		{
			//插入到parent的左边
			parent->_left = cur;
			cur->_parent = parent;
		}
		else //新结点的key值大于parent的key值
		{
			//插入到parent的右边
			parent->_right = cur;
			cur->_parent = parent;
		}

		//3、若插入结点的父结点是红色的，则需要对红黑树进行调整
		while (parent&&parent->_col == RED)
		{
			Node* grandfather = parent->_parent; //parent是红色，则其父结点一定存在
			if (parent == grandfather->_left) //parent是grandfather的左孩子
			{
				Node* uncle = grandfather->_right; //uncle是grandfather的右孩子
				if (uncle&&uncle->_col == RED) //情况1：uncle存在且为红
				{
					//颜色调整
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					//继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else //情况2+情况3：uncle不存在 + uncle存在且为黑
				{
					if (cur == parent->_left)
					{
						RotateR(grandfather); //右单旋

						//颜色调整
						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					else //cur == parent->_right
					{
						RotateLR(grandfather); //左右双旋

						//颜色调整
						grandfather->_col = RED;
						cur->_col = BLACK;
					}
					break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
				}
			}
			else //parent是grandfather的右孩子
			{
				Node* uncle = grandfather->_left; //uncle是grandfather的左孩子
				if (uncle&&uncle->_col == RED) //情况1：uncle存在且为红
				{
					//颜色调整
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;

					//继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else //情况2+情况3：uncle不存在 + uncle存在且为黑
				{
					if (cur == parent->_left)
					{
						RotateRL(grandfather); //右左双旋

						//颜色调整
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					else //cur == parent->_right
					{
						RotateL(grandfather); //左单旋

						//颜色调整
						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
				}
			}
		}
		_root->_col = BLACK; //根结点的颜色为黑色（可能被情况一变成了红色，需要变回黑色）
		return make_pair(newnode, true); //插入成功
	}

	//删除函数
	bool Erase(const K& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (key < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				//找到了待删除结点

			}
		}
		return false; ////////////////
	}
	
	//判断是否为红黑树
	bool ISRBTree()
	{
		if (_root->_col == RED)
		{
			cout << "error：根结点为红色" << endl;
			return false;
		}
		
		//任意计算一条从根到叶子的路径当中黑色结点的数目
		Node* cur = _root;
		int BlackCount = 0;
		while (cur)
		{
			if (cur->_col == BLACK)
				BlackCount++;
			cur = cur->_left;
		}

		int count = 0;
		return _ISRBTree(_root, count, BlackCount);
	}
private:
	//判断是否为红黑树的子函数
	bool _ISRBTree(Node* root, int count, int BlackCount)
	{
		//该路径已经走完了
		if (root == nullptr)
		{
			if (count != BlackCount)
			{
				cout << "error：从根到叶子的路径所包含黑色结点的数目不相同" << endl;
				return false;
			}
			return true;
		}
		if (root->_col == BLACK)
			count++;
		Node* parent = root->_parent;
		if (parent&&parent->_col == RED&&root->_col == RED)
		{
			cout << "error：存在连续的红色结点" << endl;
			return false;
		}
		return _ISRBTree(root->_left, count, BlackCount);
	}
	//析构函数子函数
	void _Destroy(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}

	//左单旋
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* parentParent = parent->_parent;

		//建立subRL与parent之间的联系
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		//建立parent与subR之间的联系
		subR->_left = parent;
		parent->_parent = subR;

		//建立subR与parentParent之间的联系
		if (parentParent == nullptr)
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			if (parent == parentParent->_left)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}
			subR->_parent = parentParent;
		}
	}

	//右单旋
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* parentParent = parent->_parent;

		//建立subLR与parent之间的联系
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		//建立parent与subL之间的联系
		subL->_right = parent;
		parent->_parent = subL;

		//建立subL与parentParent之间的联系
		if (parentParent == nullptr)
		{
			_root = subL;
			_root->_parent = nullptr;
		}
		else
		{
			if (parent == parentParent->_left)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}
			subL->_parent = parentParent;
		}
	}

	//左右双旋
	void RotateLR(Node* parent)
	{
		RotateL(parent->_left);
		RotateR(parent);
	}

	//右左双旋
	void RotateRL(Node* parent)
	{
		RotateR(parent->_right);
		RotateL(parent);
	}

	Node* _root;
};