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
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		//找到待插入位置，将结点插入
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
		cur = new Node(kv);

		if (kv.first < parent->_kv.first)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else //kv.first > parent->_kv.first
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		//控制平衡
		//1、更新平衡因子
		//2、如果出现不平衡，则需要旋转
		while (cur != _root)
		{
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else if (cur == parent->_right)
			{
				parent->_bf++;
			}
			//判断是否更新结束或需要进行旋转
			if (parent->_bf == 0) //更新结束
			{
				break;
			}
			else if (parent->_bf == -1 || parent->_bf == 1) //需要继续往上更新平衡因子
			{
				//parent所在子树的高度变化，会影响其父结点的平衡因子，需要继续往上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2) //需要进行旋转
			{
				if (parent->_bf == -2)
				{
					//cur的平衡因子不可能是0
					//1、cur是新增结点，平衡因子为1
					//2、cur是上一次更新平衡因子的parent，若cur的平衡因子为0，则在上一次更新平衡因子时就结束了
					if (cur->_bf == -1)
					{
						RotateR(parent); //右单旋
					}
					else //cur->_bf == 1
					{
						RotateLR(parent); //左右双旋
					}
				}
				else //parent->_bf == 2
				{
					if (cur->_bf == -1)
					{
						RotateRL(parent); //右左双旋
					}
					else //cur->_bf == 1
					{
						RotateL(parent); //左单旋
					}
				}
				break; //旋转后一定平衡了，无需继续往上更新平衡因子
			}
			else
			{
				assert(false); //在插入前树的平衡因子就有问题
			}
		}

		return true;
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
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* parentParent = parent->_parent;

		//建立parent和subRL之间的关系
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		//建立parent和subR之间的关系
		parent->_parent = subR;
		subR->_left = parent;

		//建立subR和parentParent之间的关系
		if (parentParent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr; //subR的_parent指向需改变
		}
		else
		{
			if (parent == parentParent->_left)
			{
				parentParent->_left = curR;
			}
			else //parent == parentParent->_right
			{
				parentParent->_right = curR;
			}
			subR->_parent = parentParent;
		}

		//平衡因子调整
		parent->_bf = cur->_bf = 0;
	}
	void RotateR(Node* parent)
	{

	}
	void RotateLR(Node* parent)
	{

	}
	void RotateRL(Node* parent)
	{

	}
	Node* _root;
};