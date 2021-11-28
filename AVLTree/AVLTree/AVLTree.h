#pragma once
#include <iostream>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	//三叉链
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	//存储的键值对
	pair<K, V> _kv;

	//平衡因子(balance factor)
	int _bf; //右子树高度-左子树高度

	//构造函数
	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(nullptr)
	{}
	bool Insert(const pair<K, V>& kv)
	{
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
				return false;
			}
		}
		Node* newnode = new Node(kv);
		if (parent == nullptr)
		{
			_root = newnode;
		}
		else
		{
			if (cur == parent->_left)
			{
				parent->_left = newnode;
				newnode->_parent = parent;
			}
			else //cur == parent->_right
			{
				parent->_right = newnode;
				newnode->_parent = parent;
			}
		}
	}
	Node* Find(const K& key)
	{
		return nullptr;
	}
	bool Erase(const K& key)
	{
		return false;
	}
private:
	Node* _root;
};