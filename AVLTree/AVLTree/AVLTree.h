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
	//���캯��
	AVLTree()
		:_root(nullptr)
	{}
	//��������
	~AVLTree()
	{
		_Destroy(_root);
	}
	//operator[]����
	V& operator[](const K& key)
	{
		//���ò��뺯�������ֵ��
		pair<Node*, bool> ret = Insert(make_pair(key, V()));
		//�ó��Ӳ��뺯����ȡ���Ľ��
		Node* node = ret.first;
		//���ظý��value������
		return node->_kv.second;
	}
	//�޸ĺ���
	bool Modify(const K& key, const V& value)
	{
		Node* ret = Find(key);
		if (ret == nullptr) //δ�ҵ�ָ��keyֵ�Ľ��
		{
			return false;
		}
		ret->_kv.second = value; //�޸Ľ���value
		return true;
	}
	//���뺯��
	pair<Node*, bool>& Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr) //��AVL��Ϊ�������������ֱ����Ϊ�����
		{
			_root = new Node(kv);
			return make_pair(_root, true); //����ɹ��������²������true
		}
		//1�����ն����������Ĳ��뷽�����ҵ�������λ��
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
				//����ʧ�ܣ�������keyֵ���ࣩ
				return make_pair(cur, false); //����ʧ�ܣ������Ѿ����ڵĽ���false
			}
		}

		//2��������������뵽����
		cur = new Node(kv); //��������ֵ����һ���½��
		Node* newnode = cur; //��¼�²���Ľ��
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

		//3������ƽ�����ӣ�������ֲ�ƽ�⣬����Ҫ������ת
		while (cur != _root) //�һ·���µ������
		{
			if (cur == parent->_left) //parent������������
			{
				parent->_bf--; //parent��ƽ������--
			}
			else if (cur == parent->_right) //parent������������
			{
				parent->_bf++; //parent��ƽ������++
			}
			//�ж��Ƿ���½�������Ҫ������ת
			if (parent->_bf == 0) //���½�������������parent��������������һ�������ˣ���ʱ���Ҹ߶�һ�£�
			{
				break; //parent���ĸ߶�û�з����仯������Ӱ���丸��㼰���Ͻ���ƽ������
			}
			else if (parent->_bf == -1 || parent->_bf == 1) //��Ҫ�������ϸ���ƽ������
			{
				//parent���ĸ߶ȱ仯����Ӱ���丸����ƽ�����ӣ���Ҫ�������ϸ���ƽ������
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2) //��Ҫ������ת����ʱparent���Ѿ���ƽ���ˣ�
			{
				if (parent->_bf == -2)
				{
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
				break; //��ת���һ��ƽ���ˣ�����������ϸ���ƽ������(��ת�����߶ȱ�Ϊ����֮ǰ��)
			}
			else
			{
				assert(false); //�ڲ���ǰ����ƽ�����Ӿ�������
			}
		}

		return make_pair(newnode, true); //����ɹ��������²������true
	}
	//���Һ���
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_kv.first) //keyֵС�ڸý���ֵ
			{
				cur = cur->_left; //�ڸý������������в���
			}
			else if (key > cur->_kv.first) //keyֵ���ڸý���ֵ
			{
				cur = cur->_right; //�ڸý������������в���
			}
			else //�ҵ���Ŀ����
			{
				return cur; //���ظý��
			}
		}
		return nullptr; //����ʧ��
	}

	//ɾ������
	bool Erase(const K& key)
	{
		//���ڱ���������
		Node* parent = nullptr;
		Node* cur = _root;
		//���ڱ��ʵ�ʵ�ɾ����㼰�丸���
		Node* delParentPos = nullptr;
		Node* delPos = nullptr;
		while (cur)
		{
			if (key < cur->_kv.first) //����keyֵС�ڵ�ǰ����keyֵ
			{
				//���ý�����������
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_kv.first) //����keyֵ���ڵ�ǰ����keyֵ
			{
				//���ý�����������
				parent = cur;
				cur = cur->_right;
			}
			else //�ҵ��˴�ɾ�����
			{
				if (cur->_left == nullptr) //��ɾ������������Ϊ��
				{
					if (cur == _root) //��ɾ������Ǹ����
					{
						_root = _root->_right; //�ø�������������Ϊ�µĸ����
						if (_root)
							_root->_parent = nullptr;
						delete cur; //ɾ��ԭ�����
						return true; //����������Ƚ�㣬�������ƽ�����ӵĸ��²���
					}
					else
					{
						delParentPos = parent; //���ʵ��ɾ�����ĸ����
						delPos = cur; //���ʵ��ɾ���Ľ��
					}
					break; //ɾ����������Ƚ�㣬�����ƽ������
				}
				else if (cur->_right == nullptr) //��ɾ������������Ϊ��
				{
					if (cur == _root) //��ɾ������Ǹ����
					{
						_root = _root->_left; //�ø�������������Ϊ�µĸ����
						if (_root)
							_root->_parent = nullptr;
						delete cur; //ɾ��ԭ�����
						return true; //����������Ƚ�㣬�������ƽ�����ӵĸ��²���
					}
					else
					{
						delParentPos = parent; //���ʵ��ɾ�����ĸ����
						delPos = cur; //���ʵ��ɾ���Ľ��
					}
					break; //ɾ����������Ƚ�㣬�����ƽ������
				}
				else //��ɾ������������������Ϊ��
				{
					//�滻��ɾ��
					//Ѱ�Ҵ�ɾ���������������keyֵ��С�Ľ����Ϊʵ��ɾ�����
					Node* minParent = cur;
					Node* minRight = cur->_right;
					while (minRight->_left)
					{
						minParent = minRight;
						minRight = minRight->_left;
					}
					cur->_kv.first = minRight->_kv.first; //����ɾ������key��ΪminRight��key
					cur->_kv.second = minRight->_kv.second; //����ɾ������value��ΪminRight��value
					delParentPos = minParent; //���ʵ��ɾ�����ĸ����
					delPos = minRight; //���ʵ��ɾ���Ľ��
					break; //ɾ����������Ƚ�㣬�����ƽ������
				}
			}
		}
		if (delParentPos == nullptr) //delParentPosû�б��޸Ĺ���˵��û���ҵ���ɾ�����
		{
			return false;
		}

		//��¼��ɾ����㼰�丸��㣨���ں���ʵ��ɾ����
		Node* del = delPos;
		Node* delP = delParentPos;

		//����ƽ������
		while (delPos != _root) //�һ·���µ������
		{
			if (delPos == delParentPos->_left) //delParentPos���������߶Ƚ���
			{
				delParentPos->_bf++; //delParentPos��ƽ������++
			}
			else if (delPos == delParentPos->_right) //delParentPos���������߶Ƚ���
			{
				delParentPos->_bf--; //delParentPos��ƽ������--
			}
			//�ж��Ƿ���½�������Ҫ������ת
			if (delParentPos->_bf == 0)//��Ҫ�������ϸ���ƽ������
			{
				//delParentPos���ĸ߶ȱ仯����Ӱ���丸����ƽ�����ӣ���Ҫ�������ϸ���ƽ������
				delPos = delParentPos;
				delParentPos = delParentPos->_parent;
			}
			else if (delParentPos->_bf == -1 || delParentPos->_bf == 1) //���½���
			{
				break; //delParent���ĸ߶�û�з����仯������Ӱ���丸��㼰���Ͻ���ƽ������
			}
			else if (delParentPos->_bf == -2 || delParentPos->_bf == 2) //��Ҫ������ת����ʱdelParentPos���Ѿ���ƽ���ˣ�
			{
				if (delParentPos->_bf == -2)
				{
					if (delParentPos->_left->_bf == -1)
					{
						Node* tmp = delParentPos->_left; //��¼delParentPos����ת���µĸ����
						RotateR(delParentPos); //�ҵ���
						delParentPos = tmp; //���¸����
					}
					else //delParentPos->_left->_bf == 1
					{
						Node* tmp = delParentPos->_left->_right; //��¼delParentPos������ת���µĸ����
						RotateLR(delParentPos); //����˫��
						delParentPos = tmp; //���¸����
					}
				}
				else //delParentPos->_bf == 2
				{
					if (delParentPos->_right->_bf == -1)
					{
						Node* tmp = delParentPos->_right->_left; //��¼delParentPos������ת���µĸ����
						RotateRL(delParentPos); //����˫��
						delParentPos = tmp; //���¸����
					}
					else //delParentPos->_right->_bf == 1
					{
						Node* tmp = delParentPos->_right; //��¼delParentPos����ת���µĸ����
						RotateL(delParentPos); //����
						delParentPos = tmp; //���¸����
					}
				}
				//delParentPos���ĸ߶ȱ仯����Ӱ���丸����ƽ�����ӣ���Ҫ�������ϸ���ƽ������
				delPos = delParentPos;
				delParentPos = delParentPos->_parent;
				//break; //error
			}
			else
			{
				assert(false); //��ɾ��ǰ����ƽ�����Ӿ�������
			}
		}
		//����ʵ��ɾ��
		if (del->_left == nullptr) //ʵ��ɾ������������Ϊ��
		{
			if (del == delP->_left) //ʵ��ɾ��������丸��������
			{
				delP->_left = del->_right;
				if (del->_right)
					del->_right->_parent = parent;
			}
			else //ʵ��ɾ��������丸�����Һ���
			{
				delP->_right = del->_right;
				if (del->_right)
					del->_right->_parent = parent;
			}
		}
		else //ʵ��ɾ������������Ϊ��
		{
			if (del == delP->_left) //ʵ��ɾ��������丸��������
			{
				delP->_left = del->_left;
				if (del->_left)
					del->_left->_parent = parent;
			}
			else //ʵ��ɾ��������丸�����Һ���
			{
				delP->_right = del->_left;
				if (del->_left)
					del->_left->_parent = parent;
			}
		}
		delete del; //ʵ��ɾ�����
		return true;
	}

	////ɾ������
	//bool Erase(const K& key)
	//{
	//	Node* parent = nullptr; //Ѱ�Ҵ�ɾ�����ĸ����
	//	Node* cur = _root; //Ѱ�Ҵ�ɾ�����
	//	Node* delParentPos = nullptr; //���ʵ��ɾ�����ĸ�����λ��
	//	Node* delPos = nullptr; //���ʵ��ɾ�������������ӵ���λ�õĽ��
	//	while (cur)
	//	{
	//		if (key < cur->_kv.first) //����keyֵС�ڵ�ǰ����keyֵ
	//		{
	//			//���ý�����������
	//			parent = cur;
	//			cur = cur->_left;
	//		}
	//		else if (key > cur->_kv.first) //����keyֵ���ڵ�ǰ����keyֵ
	//		{
	//			//���ý�����������
	//			parent = cur;
	//			cur = cur->_right;
	//		}
	//		else //�ҵ��˴�ɾ�����
	//		{
	//			if (cur->_left == nullptr) //��ɾ������������Ϊ��
	//			{
	//				if (cur == _root) //��ɾ������Ǹ����
	//				{
	//					_root = _root ->_right;
	//					if (_root)
	//						_root->_parent = nullptr;
	//					delete cur;
	//					return true; //��������������ϸ���������ƽ������
	//				}
	//				else
	//				{
	//					if (cur == parent->_left) //��ɾ��������丸��������
	//					{
	//						parent->_left = cur->_right; //��������ָ��ָ���ɾ������������
	//						if (cur->_right)
	//							cur->_right->_parent = parent;
	//					}
	//					else //��ɾ��������丸�����Һ���
	//					{
	//						parent->_right = cur->_right; //��������ָ��ָ���ɾ������������
	//						if (cur->_right)
	//							cur->_right->_parent = parent;
	//					}
	//					delParentPos = parent;
	//					delPos = cur->_right; //ɾ�������������ӵ���λ�õĽ����cur->_right
	//				}
	//				delete cur;
	//				break; //�����ƽ������
	//			}
	//			else if (cur->_right == nullptr) //��ɾ������������Ϊ��
	//			{
	//				if (cur == _root) //��ɾ������Ǹ����
	//				{
	//					_root = _root->_left;
	//					if (_root)
	//						_root->_parent = nullptr;
	//					delete cur;
	//					return true; //��������������ϸ���������ƽ������
	//				}
	//				else
	//				{
	//					if (cur == parent->_left) //��ɾ��������丸��������
	//					{
	//						parent->_left = cur->_left; //��������ָ��ָ���ɾ������������
	//						cur->_left->_parent = parent;
	//					}
	//					else //��ɾ��������丸�����Һ���
	//					{
	//						parent->_right = cur->_left; //��������ָ��ָ���ɾ������������
	//						cur->_left->_parent = parent;
	//					}
	//					delParentPos = parent;
	//					delPos = cur->_left; //ɾ�������������ӵ���λ�õĽ����cur->_left
	//				}
	//				delete cur;
	//				break; //�����ƽ������
	//			}
	//			else //��ɾ������������������Ϊ��
	//			{
	//				//�滻��ɾ��
	//				//Ѱ�Ҵ�ɾ���������������keyֵ��С�Ľ�����ɾ��
	//				Node* minParent = cur;
	//				Node* minRight = cur->_right;
	//				while (minRight->_left)
	//				{
	//					minParent = minRight;
	//					minRight = minRight->_left;
	//				}
	//				cur->_kv.first = minRight->_kv.first; //����ɾ������key��ΪminRight��key
	//				cur->_kv.second = minRight->_kv.second; //����ɾ������value��ΪminRight��value
	//				//ע��һ��������������ʱminRight��_leftΪ��
	//				if (minRight == minParent->_left)
	//				{
	//					minParent->_left = minRight->_right;
	//					if (minRight->_right)
	//						minRight->_right->_parent = minParent;
	//				}
	//				else
	//				{
	//					minParent->_right = minRight->_right;
	//					if (minRight->_right)
	//						minRight->_right->_parent = minParent;
	//				}
	//				delParentPos = minParent;
	//				delPos = minRight->_right; //ɾ�������������ӵ���λ�õĽ����minRight->_right
	//				delete minRight;
	//				break; //�����ƽ������
	//			}
	//		}
	//	}
	//	if (delParentPos == nullptr) //û���ҵ���ɾ�����
	//	{
	//		return false;
	//	}
	//	//����ƽ������
	//	while (delParentPos != nullptr) //�һ·���µ������
	//	{
	//		if (delPos == delParentPos->_left) //delParent���������߶Ƚ���
	//		{
	//			delParentPos->_bf++; //delParent��ƽ������++
	//		}
	//		else if (delPos == delParentPos->_right) //delParent���������߶Ƚ���
	//		{
	//			delParentPos->_bf--; //delParent��ƽ������--
	//		}
	//		//�ж��Ƿ���½�������Ҫ������ת
	//		if (delParentPos->_bf == 0)//��Ҫ�������ϸ���ƽ������
	//		{
	//			//delParent���ĸ߶ȱ仯����Ӱ���丸����ƽ�����ӣ���Ҫ�������ϸ���ƽ������
	//			delPos = delParentPos;
	//			delParentPos = delParentPos->_parent;
	//		}
	//		else if (delParentPos->_bf == -1 || delParentPos->_bf == 1) //���½���
	//		{
	//			break; //delParent���ĸ߶�û�з��ͱ仯������Ӱ���丸��㼰���Ͻ���ƽ������
	//		}
	//		else if (delParentPos->_bf == -2 || delParentPos->_bf == 2) //��Ҫ������ת����ʱparent���Ѿ���ƽ���ˣ�
	//		{
	//			if (delParentPos->_bf == -2)
	//			{
	//				if (delParentPos->_left->_bf == -1)
	//				{
	//					Node* tmp = delParentPos->_left;
	//					RotateR(delParentPos); //�ҵ���
	//					delParentPos = tmp;
	//				}
	//				else //delParentPos->_left->_bf == 1
	//				{
	//					Node* tmp = delParentPos->_left->_right;
	//					RotateLR(delParentPos); //����˫��
	//					delParentPos = tmp;
	//				}
	//			}
	//			else //delPP->_bf == 2
	//			{
	//				if (delParentPos->_right->_bf == -1)
	//				{
	//					Node* tmp = delParentPos->_right->_left;
	//					RotateRL(delParentPos); //����˫��
	//					delParentPos = tmp;
	//				}
	//				else //delParentPos->_right->_bf == 1
	//				{
	//					Node* tmp = delParentPos->_right;
	//					RotateL(delParentPos); //����
	//					delParentPos = tmp;
	//				}
	//			}
	//			//delParent���ĸ߶ȱ仯����Ӱ���丸����ƽ�����ӣ���Ҫ�������ϸ���ƽ������
	//			delPos = delParentPos;
	//			delParentPos = delParentPos->_parent;
	//			//break;
	//		}
	//		else
	//		{
	//			assert(false); //�ڲ���ǰ����ƽ�����Ӿ�������
	//		}
	//	}
	//	return true;
	//}
	//�������
	void Inorder()
	{
		_Inorder(_root);
	}
	//�ж��Ƿ�ΪAVL��
	bool IsAVLTree()
	{
		int hight = 0; //����Ͳ���
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

		//1����subLΪ��ת���������
		RotateL(subL);

		//2����parentΪ��ת������ҵ���
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

	//��������Ӻ���
	void _Inorder(Node* root)
	{
		if (root == nullptr)
			return;
		_Inorder(root->_left);
		//cout << root->_kv.first << " ";
		cout << "<" << root->_kv.first << "," << root->_kv.second << ">" << endl;
		_Inorder(root->_right);
	}

	//���������Ƿ�ƽ��
	bool _IsBalanced(Node* root, int& hight)
	{
		if (root == nullptr) //������ƽ�������
		{
			hight = 0; //�����ĸ߶�Ϊ0
			return true;
		}
		//���ж�������
		int leftHight = 0;
		if (_IsBalanced(root->_left, leftHight) == false)
			return false;
		//���ж�������
		int rightHight = 0;
		if (_IsBalanced(root->_right, rightHight) == false)
			return false;
		//���ý���ƽ������
		if (rightHight - leftHight != root->_bf)
		{
			cout << "ƽ�����������쳣��" << root->_kv.first << endl;
		}
		//�����������ĸ߶��еĽϴ�ֵ+1��Ϊ��ǰ���ĸ߶ȷ��ظ���һ��
		hight = max(leftHight, rightHight) + 1;
		return abs(rightHight - leftHight) < 2; //ƽ�������������
	}
	//���������Ӻ���
	void _Destroy(Node* root)
	{
		if (root == nullptr)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}
	Node* _root;
};