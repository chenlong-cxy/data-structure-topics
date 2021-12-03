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
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (kv.first < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false; //插入失败
			}
		}
		//进行插入
		Node* newnode = new Node(kv);
		return false; /////////////////////
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
private:
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
		Node* subRL = subL->_left;
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