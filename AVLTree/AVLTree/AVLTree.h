#pragma once
#include <iostream>
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

		//����parent��subRL֮��Ĺ�ϵ
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		//����parent��subR֮��Ĺ�ϵ
		parent->_parent = subR;
		subR->_left = parent;

		//����subR��parentParent֮��Ĺ�ϵ
		if (parentParent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr; //subR��_parentָ����ı�
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

		//ƽ�����ӵ���
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