#pragma once
#include <iostream>
using namespace std;

//ö�ٶ��������ɫ
enum Colour
{
	RED,
	BLACK
};

template<class K, class V>
struct RBTreeNode
{
	//������
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	//�洢�ļ�ֵ��
	pair<K, V> _kv;

	//������ɫ
	int _col; //��/��

	//���캯��
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
	//���캯��
	RBTree()
		:_root(nullptr)
	{}
	//��������
	//operator=

	//��������
	~RBTree()
	{
		_Destroy(_root);
		_root = nullptr;
	}

	//���Һ���
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

	//���뺯��
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
				return false; //����ʧ��
			}
		}
		//���в���
		Node* newnode = new Node(kv);
		return false; /////////////////////
	}

	//ɾ������
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
				//�ҵ��˴�ɾ�����

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
	//����
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subL->_left;
		Node* parentParent = parent->_parent;

		//����subRL��parent֮�����ϵ
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		//����parent��subR֮�����ϵ
		subR->_left = parent;
		parent->_parent = subR;

		//����subR��parentParent֮�����ϵ
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

	//�ҵ���
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* parentParent = parent->_parent;

		//����subLR��parent֮�����ϵ
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		//����parent��subL֮�����ϵ
		subL->_right = parent;
		parent->_parent = subL;

		//����subL��parentParent֮�����ϵ
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

	//����˫��
	void RotateLR(Node* parent)
	{
		RotateL(parent->_left);
		RotateR(parent);
	}

	//����˫��
	void RotateRL(Node* parent)
	{
		RotateR(parent->_right);
		RotateL(parent);
	}

	Node* _root;
};