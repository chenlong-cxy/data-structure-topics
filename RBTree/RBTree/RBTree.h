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
	pair<Node*, bool> Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr) //�������Ϊ�������������ֱ����Ϊ�����
		{
			_root = new Node(kv);
			_root->_col = BLACK; //���������Ǻ�ɫ
			return make_pair(_root, true); //����ɹ�
		}
		//1���������������Ĳ��뷽�����ҵ�������λ��
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (kv.first < cur->_kv.first) //���������keyֵС�ڵ�ǰ����keyֵ
			{
				//���ý�����������
				parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > cur->_kv.first) //���������keyֵ���ڵ�ǰ����keyֵ
			{
				//���ý�����������
				parent = cur;
				cur = cur->_right;
			}
			else //���������keyֵ���ڵ�ǰ����keyֵ
			{
				return make_pair(cur, false); //����ʧ��
			}
		}

		//2��������������뵽����
		cur = new Node(kv); //��������ֵ����һ�����
		Node* newnode = cur; //��¼�²���Ľ�㣨���ں��򷵻أ�
		if (kv.first < parent->_kv.first) //�½���keyֵС��parent��keyֵ
		{
			//���뵽parent�����
			parent->_left = cur;
			cur->_parent = parent;
		}
		else //�½���keyֵ����parent��keyֵ
		{
			//���뵽parent���ұ�
			parent->_right = cur;
			cur->_parent = parent;
		}

		//3����������ĸ�����Ǻ�ɫ�ģ�����Ҫ�Ժ�������е���
		while (parent&&parent->_col == RED)
		{
			Node* grandfather = parent->_parent; //parent�Ǻ�ɫ�����丸���һ������
			if (parent == grandfather->_left) //parent��grandfather������
			{
				Node* uncle = grandfather->_right; //uncle��grandfather���Һ���
				if (uncle&&uncle->_col == RED) //���1��uncle������Ϊ��
				{
					//��ɫ����
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					//�������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				else //���2+���3��uncle������ + uncle������Ϊ��
				{
					if (cur == parent->_left)
					{
						RotateR(grandfather); //�ҵ���

						//��ɫ����
						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					else //cur == parent->_right
					{
						RotateLR(grandfather); //����˫��

						//��ɫ����
						grandfather->_col = RED;
						cur->_col = BLACK;
					}
					break; //������ת�󣬸������ĸ�����˺�ɫ������������Ͻ��д���
				}
			}
			else //parent��grandfather���Һ���
			{
				Node* uncle = grandfather->_left; //uncle��grandfather������
				if (uncle&&uncle->_col == RED) //���1��uncle������Ϊ��
				{
					//��ɫ����
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;

					//�������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				else //���2+���3��uncle������ + uncle������Ϊ��
				{
					if (cur == parent->_left)
					{
						RotateRL(grandfather); //����˫��

						//��ɫ����
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					else //cur == parent->_right
					{
						RotateL(grandfather); //����

						//��ɫ����
						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					break; //������ת�󣬸������ĸ�����˺�ɫ������������Ͻ��д���
				}
			}
		}
		_root->_col = BLACK; //��������ɫΪ��ɫ�����ܱ����һ����˺�ɫ����Ҫ��غ�ɫ��
		return make_pair(newnode, true); //����ɹ�
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
	
	//�ж��Ƿ�Ϊ�����
	bool ISRBTree()
	{
		if (_root->_col == RED)
		{
			cout << "error�������Ϊ��ɫ" << endl;
			return false;
		}
		
		//�������һ���Ӹ���Ҷ�ӵ�·�����к�ɫ������Ŀ
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
	//�ж��Ƿ�Ϊ��������Ӻ���
	bool _ISRBTree(Node* root, int count, int BlackCount)
	{
		//��·���Ѿ�������
		if (root == nullptr)
		{
			if (count != BlackCount)
			{
				cout << "error���Ӹ���Ҷ�ӵ�·����������ɫ������Ŀ����ͬ" << endl;
				return false;
			}
			return true;
		}
		if (root->_col == BLACK)
			count++;
		Node* parent = root->_parent;
		if (parent&&parent->_col == RED&&root->_col == RED)
		{
			cout << "error�����������ĺ�ɫ���" << endl;
			return false;
		}
		return _ISRBTree(root->_left, count, BlackCount);
	}
	//���������Ӻ���
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
		Node* subRL = subR->_left;
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