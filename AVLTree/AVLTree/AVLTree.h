#pragma once
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	//������
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	//�洢�ļ�ֵ��
	pair<K, V> _kv;

	//ƽ������(balance factor)
	int _bf; //�������߶�-�������߶�

	//���캯��
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
		//�ҵ�������λ�ã���������
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

		//����ƽ��
		//1������ƽ������
		//2��������ֲ�ƽ�⣬����Ҫ��ת
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
			//�ж��Ƿ���½�������Ҫ������ת
			if (parent->_bf == 0) //���½���
			{
				break;
			}
			else if (parent->_bf == -1 || parent->_bf == 1) //��Ҫ�������ϸ���ƽ������
			{
				//parent���������ĸ߶ȱ仯����Ӱ���丸����ƽ�����ӣ���Ҫ�������ϸ���
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2) //��Ҫ������ת
			{
				if (parent->_bf == -2)
				{
					//cur��ƽ�����Ӳ�������0
					//1��cur��������㣬ƽ������Ϊ1
					//2��cur����һ�θ���ƽ�����ӵ�parent����cur��ƽ������Ϊ0��������һ�θ���ƽ������ʱ�ͽ�����
					if (cur->_bf == -1)
					{
						RotateR(parent); //�ҵ���
					}
					else //cur->_bf == 1
					{
						RotateLR(parent); //����˫��
					}
				}
				else //parent->_bf == 2
				{
					if (cur->_bf == -1)
					{
						RotateRL(parent); //����˫��
					}
					else //cur->_bf == 1
					{
						RotateL(parent); //����
					}
				}
				break; //��ת��һ��ƽ���ˣ�����������ϸ���ƽ������
			}
			else
			{
				assert(false); //�ڲ���ǰ����ƽ�����Ӿ�������
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
	//����
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* parentParent = parent->_parent;

		//1������subR��parent֮��Ĺ�ϵ
		parent->_parent = subR;
		subR->_left = parent;

		//2������parent��subRL֮��Ĺ�ϵ
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		//3������parentParent��subR֮��Ĺ�ϵ
		if (parentParent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr; //subR��_parentָ����ı�
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

		//4������ƽ������
		subR->_bf = parent->_bf = 0;
	}

	//�ҵ���
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* parentParent = parent->_parent;

		//1������subL��parent֮��Ĺ�ϵ
		subL->_right = parent;
		parent->_parent = subL;

		//2������parent��subLR֮��Ĺ�ϵ
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		//3������parentParent��subL֮��Ĺ�ϵ
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

		//4������ƽ������
		subL->_bf = parent->_bf = 0;
	}

	//����˫��
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf; //subLR������Ϊnullptr����ΪsubL��ƽ��������1

		//1����subLΪ���������
		RotateL(subL);

		//2����parentΪ������ҵ���
		RotateR(parent);

		//3������ƽ������
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
			assert(false); //����תǰ����ƽ�����Ӿ�������
		}
	}

	//����˫��
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		//1����subRΪ������ҵ���
		RotateR(subR);

		//2����parentΪ���������
		RotateL(parent);

		//3������ƽ������
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
			assert(false); //����תǰ����ƽ�����Ӿ�������
		}
	}

	//�������
	void _Inorder(Node* root)
	{
		if (root == nullptr)
			return;
		_Inorder(root->_left);
		cout << root->_kv.first << " ";
		_Inorder(root->_right);
	}

	//���
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
			cout << "ƽ�����������쳣��" << root->_kv.first << endl;
		}
		hight = max(leftHight, rightHight) + 1;
		return abs(rightHight - leftHight) < 2;
	}
	Node* _root;
};