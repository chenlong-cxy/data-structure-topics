#pragma once
#include <iostream>
#include <algorithm>
#include <assert.h>
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
	bool Erase(const K& key)
	{
		return false;
	}
	void Inorder()
	{
		_Inorder(_root);
	}
	bool IsAVLTree()
	{
		int hight = 0;
		return _IsBalanced(_root, hight);
	}
private:
	//左单旋
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* parentParent = parent->_parent;

		//1、建立subR和parent之间的关系
		parent->_parent = subR;
		subR->_left = parent;

		//2、建立parent和subRL之间的关系
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		//3、建立parentParent和subR之间的关系
		if (parentParent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr; //subR的_parent指向需改变
		}
		else
		{
			if (parent == parentParent->_left)
			{
				parentParent->_left = subR;
			}
			else //parent == parentParent->_right
			{
				parentParent->_right = subR;
			}
			subR->_parent = parentParent;
		}

		//4、更新平衡因子
		subR->_bf = parent->_bf = 0;
	}

	//右单旋
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* parentParent = parent->_parent;

		//1、建立subL和parent之间的关系
		subL->_right = parent;
		parent->_parent = subL;

		//2、建立parent和subLR之间的关系
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		//3、建立parentParent和subL之间的关系
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
			else //parent == parentParent->_right
			{
				parentParent->_right = subL;
			}
			subL->_parent = parentParent;
		}

		//4、更新平衡因子
		subL->_bf = parent->_bf = 0;
	}

	//左右双旋
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf; //subLR不可能为nullptr，因为subL的平衡因子是1

		//1、以subL为轴进行左单旋
		RotateL(subL);

		//2、以parent为轴进行右单旋
		RotateR(parent);

		//3、更新平衡因子
		if (bf == 1)
		{
			subLR->_bf = 0;
			subL->_bf = -1;
			parent->_bf = 0;
		}
		else if (bf == -1)
		{
			subLR->_bf = 0;
			subL->_bf = 0;
			parent->_bf = 1;
		}
		else if (bf == 0)
		{
			subLR->_bf = 0;
			subL->_bf = 0;
			parent->_bf = 0;
		}
		else
		{
			assert(false); //在旋转前树的平衡因子就有问题
		}
	}

	//右左双旋
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		//1、以subR为轴进行右单旋
		RotateR(subR);

		//2、以parent为轴进行左单旋
		RotateL(parent);

		//3、更新平衡因子
		if (bf == 1)
		{
			subRL->_bf = 0;
			parent->_bf = -1;
			subR->_bf = 0;
		}
		else if (bf == -1)
		{
			subRL->_bf = 0;
			parent->_bf = 0;
			subR->_bf = 1;
		}
		else if (bf == 0)
		{
			subRL->_bf = 0;
			parent->_bf = 0;
			subR->_bf = 0;
		}
		else
		{
			assert(false); //在旋转前树的平衡因子就有问题
		}
	}

	//中序遍历
	void _Inorder(Node* root)
	{
		if (root == nullptr)
			return;
		_Inorder(root->_left);
		cout << root->_kv.first << " ";
		_Inorder(root->_right);
	}

	//检测
	bool _IsBalanced(Node* root, int& hight)
	{
		if (root == nullptr)
			return true;
		int leftHight = 0;
		if (_IsBalanced(root->_left, leftHight) == false)
			return false;
		int rightHight = 0;
		if (_IsBalanced(root->_right, rightHight) == false)
			return false;
		if (rightHight - leftHight != root->_bf)
		{
			cout << "平衡因子设置异常：" << root->_kv.first << endl;
		}
		hight = max(leftHight, rightHight) + 1;
		return abs(rightHight - leftHight) < 2;
	}
	Node* _root;
};