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
	//构造函数
	AVLTree()
		:_root(nullptr)
	{}
	//析构函数
	~AVLTree()
	{
		_Destroy(_root);
	}
	//operator[]重载
	V& operator[](const K& key)
	{
		//调用插入函数插入键值对
		pair<Node*, bool> ret = Insert(make_pair(key, V()));
		//拿出从插入函数获取到的结点
		Node* node = ret.first;
		//返回该结点value的引用
		return node->_kv.second;
	}
	//修改函数
	bool Modify(const K& key, const V& value)
	{
		Node* ret = Find(key);
		if (ret == nullptr) //未找到指定key值的结点
		{
			return false;
		}
		ret->_kv.second = value; //修改结点的value
		return true;
	}
	//插入函数
	pair<Node*, bool>& Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr) //若AVL树为空树，则插入结点直接作为根结点
		{
			_root = new Node(kv);
			return make_pair(_root, true); //插入成功，返回新插入结点和true
		}
		//1、按照二叉搜索树的插入方法，找到待插入位置
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
				//插入失败（不允许key值冗余）
				return make_pair(cur, false); //插入失败，返回已经存在的结点和false
			}
		}

		//2、将待插入结点插入到树中
		cur = new Node(kv); //根据所给值构造一个新结点
		Node* newnode = cur; //记录新插入的结点
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

		//3、更新平衡因子，如果出现不平衡，则需要进行旋转
		while (cur != _root) //最坏一路更新到根结点
		{
			if (cur == parent->_left) //parent的左子树增高
			{
				parent->_bf--; //parent的平衡因子--
			}
			else if (cur == parent->_right) //parent的右子树增高
			{
				parent->_bf++; //parent的平衡因子++
			}
			//判断是否更新结束或需要进行旋转
			if (parent->_bf == 0) //更新结束（新增结点把parent左右子树矮的那一边增高了，此时左右高度一致）
			{
				break; //parent树的高度没有发生变化，不会影响其父结点及以上结点的平衡因子
			}
			else if (parent->_bf == -1 || parent->_bf == 1) //需要继续往上更新平衡因子
			{
				//parent树的高度变化，会影响其父结点的平衡因子，需要继续往上更新平衡因子
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2) //需要进行旋转（此时parent树已经不平衡了）
			{
				if (parent->_bf == -2)
				{
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
				break; //旋转后就一定平衡了，无需继续往上更新平衡因子(旋转后树高度变为插入之前了)
			}
			else
			{
				assert(false); //在插入前树的平衡因子就有问题
			}
		}

		return make_pair(newnode, true); //插入成功，返回新插入结点和true
	}
	//查找函数
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_kv.first) //key值小于该结点的值
			{
				cur = cur->_left; //在该结点的左子树当中查找
			}
			else if (key > cur->_kv.first) //key值大于该结点的值
			{
				cur = cur->_right; //在该结点的右子树当中查找
			}
			else //找到了目标结点
			{
				return cur; //返回该结点
			}
		}
		return nullptr; //查找失败
	}

	//删除函数
	bool Erase(const K& key)
	{
		//用于遍历二叉树
		Node* parent = nullptr;
		Node* cur = _root;
		//用于标记实际的删除结点及其父结点
		Node* delParentPos = nullptr;
		Node* delPos = nullptr;
		while (cur)
		{
			if (key < cur->_kv.first) //所给key值小于当前结点的key值
			{
				//往该结点的左子树走
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_kv.first) //所给key值大于当前结点的key值
			{
				//往该结点的右子树走
				parent = cur;
				cur = cur->_right;
			}
			else //找到了待删除结点
			{
				if (cur->_left == nullptr) //待删除结点的左子树为空
				{
					if (cur == _root) //待删除结点是根结点
					{
						_root = _root->_right; //让根结点的右子树作为新的根结点
						if (_root)
							_root->_parent = nullptr;
						delete cur; //删除原根结点
						return true; //根结点无祖先结点，无需进行平衡因子的更新操作
					}
					else
					{
						delParentPos = parent; //标记实际删除结点的父结点
						delPos = cur; //标记实际删除的结点
					}
					break; //删除结点有祖先结点，需更新平衡因子
				}
				else if (cur->_right == nullptr) //待删除结点的右子树为空
				{
					if (cur == _root) //待删除结点是根结点
					{
						_root = _root->_left; //让根结点的左子树作为新的根结点
						if (_root)
							_root->_parent = nullptr;
						delete cur; //删除原根结点
						return true; //根结点无祖先结点，无需进行平衡因子的更新操作
					}
					else
					{
						delParentPos = parent; //标记实际删除结点的父结点
						delPos = cur; //标记实际删除的结点
					}
					break; //删除结点有祖先结点，需更新平衡因子
				}
				else //待删除结点的左右子树均不为空
				{
					//替换法删除
					//寻找待删除结点右子树当中key值最小的结点作为实际删除结点
					Node* minParent = cur;
					Node* minRight = cur->_right;
					while (minRight->_left)
					{
						minParent = minRight;
						minRight = minRight->_left;
					}
					cur->_kv.first = minRight->_kv.first; //将待删除结点的key改为minRight的key
					cur->_kv.second = minRight->_kv.second; //将待删除结点的value改为minRight的value
					delParentPos = minParent; //标记实际删除结点的父结点
					delPos = minRight; //标记实际删除的结点
					break; //删除结点有祖先结点，需更新平衡因子
				}
			}
		}
		if (delParentPos == nullptr) //delParentPos没有被修改过，说明没有找到待删除结点
		{
			return false;
		}

		//记录待删除结点及其父结点（用于后续实际删除）
		Node* del = delPos;
		Node* delP = delParentPos;

		//更新平衡因子
		while (delPos != _root) //最坏一路更新到根结点
		{
			if (delPos == delParentPos->_left) //delParentPos的左子树高度降低
			{
				delParentPos->_bf++; //delParentPos的平衡因子++
			}
			else if (delPos == delParentPos->_right) //delParentPos的右子树高度降低
			{
				delParentPos->_bf--; //delParentPos的平衡因子--
			}
			//判断是否更新结束或需要进行旋转
			if (delParentPos->_bf == 0)//需要继续往上更新平衡因子
			{
				//delParentPos树的高度变化，会影响其父结点的平衡因子，需要继续往上更新平衡因子
				delPos = delParentPos;
				delParentPos = delParentPos->_parent;
			}
			else if (delParentPos->_bf == -1 || delParentPos->_bf == 1) //更新结束
			{
				break; //delParent树的高度没有发生变化，不会影响其父结点及以上结点的平衡因子
			}
			else if (delParentPos->_bf == -2 || delParentPos->_bf == 2) //需要进行旋转（此时delParentPos树已经不平衡了）
			{
				if (delParentPos->_bf == -2)
				{
					if (delParentPos->_left->_bf == -1)
					{
						Node* tmp = delParentPos->_left; //记录delParentPos右旋转后新的根结点
						RotateR(delParentPos); //右单旋
						delParentPos = tmp; //更新根结点
					}
					else //delParentPos->_left->_bf == 1
					{
						Node* tmp = delParentPos->_left->_right; //记录delParentPos左右旋转后新的根结点
						RotateLR(delParentPos); //左右双旋
						delParentPos = tmp; //更新根结点
					}
				}
				else //delParentPos->_bf == 2
				{
					if (delParentPos->_right->_bf == -1)
					{
						Node* tmp = delParentPos->_right->_left; //记录delParentPos右左旋转后新的根结点
						RotateRL(delParentPos); //右左双旋
						delParentPos = tmp; //更新根结点
					}
					else //delParentPos->_right->_bf == 1
					{
						Node* tmp = delParentPos->_right; //记录delParentPos左旋转后新的根结点
						RotateL(delParentPos); //左单旋
						delParentPos = tmp; //更新根结点
					}
				}
				//delParentPos树的高度变化，会影响其父结点的平衡因子，需要继续往上更新平衡因子
				delPos = delParentPos;
				delParentPos = delParentPos->_parent;
				//break; //error
			}
			else
			{
				assert(false); //在删除前树的平衡因子就有问题
			}
		}
		//进行实际删除
		if (del->_left == nullptr) //实际删除结点的左子树为空
		{
			if (del == delP->_left) //实际删除结点是其父结点的左孩子
			{
				delP->_left = del->_right;
				if (del->_right)
					del->_right->_parent = parent;
			}
			else //实际删除结点是其父结点的右孩子
			{
				delP->_right = del->_right;
				if (del->_right)
					del->_right->_parent = parent;
			}
		}
		else //实际删除结点的右子树为空
		{
			if (del == delP->_left) //实际删除结点是其父结点的左孩子
			{
				delP->_left = del->_left;
				if (del->_left)
					del->_left->_parent = parent;
			}
			else //实际删除结点是其父结点的右孩子
			{
				delP->_right = del->_left;
				if (del->_left)
					del->_left->_parent = parent;
			}
		}
		delete del; //实际删除结点
		return true;
	}

	////删除函数
	//bool Erase(const K& key)
	//{
	//	Node* parent = nullptr; //寻找待删除结点的父结点
	//	Node* cur = _root; //寻找待删除结点
	//	Node* delParentPos = nullptr; //标记实际删除结点的父结点的位置
	//	Node* delPos = nullptr; //标记实际删除结点后，重新链接到该位置的结点
	//	while (cur)
	//	{
	//		if (key < cur->_kv.first) //所给key值小于当前结点的key值
	//		{
	//			//往该结点的左子树走
	//			parent = cur;
	//			cur = cur->_left;
	//		}
	//		else if (key > cur->_kv.first) //所给key值大于当前结点的key值
	//		{
	//			//往该结点的右子树走
	//			parent = cur;
	//			cur = cur->_right;
	//		}
	//		else //找到了待删除结点
	//		{
	//			if (cur->_left == nullptr) //待删除结点的左子树为空
	//			{
	//				if (cur == _root) //待删除结点是根结点
	//				{
	//					_root = _root ->_right;
	//					if (_root)
	//						_root->_parent = nullptr;
	//					delete cur;
	//					return true; //根结点无需再向上更新子树的平衡因子
	//				}
	//				else
	//				{
	//					if (cur == parent->_left) //待删除结点是其父结点的左孩子
	//					{
	//						parent->_left = cur->_right; //父结点的左指针指向待删除结点的右子树
	//						if (cur->_right)
	//							cur->_right->_parent = parent;
	//					}
	//					else //待删除结点是其父结点的右孩子
	//					{
	//						parent->_right = cur->_right; //父结点的右指针指向待删除结点的右子树
	//						if (cur->_right)
	//							cur->_right->_parent = parent;
	//					}
	//					delParentPos = parent;
	//					delPos = cur->_right; //删除结点后，重新链接到该位置的结点是cur->_right
	//				}
	//				delete cur;
	//				break; //需更新平衡因子
	//			}
	//			else if (cur->_right == nullptr) //待删除结点的右子树为空
	//			{
	//				if (cur == _root) //待删除结点是根结点
	//				{
	//					_root = _root->_left;
	//					if (_root)
	//						_root->_parent = nullptr;
	//					delete cur;
	//					return true; //根结点无需再向上更新子树的平衡因子
	//				}
	//				else
	//				{
	//					if (cur == parent->_left) //待删除结点是其父结点的左孩子
	//					{
	//						parent->_left = cur->_left; //父结点的左指针指向待删除结点的左子树
	//						cur->_left->_parent = parent;
	//					}
	//					else //待删除结点是其父结点的右孩子
	//					{
	//						parent->_right = cur->_left; //父结点的右指针指向待删除结点的左子树
	//						cur->_left->_parent = parent;
	//					}
	//					delParentPos = parent;
	//					delPos = cur->_left; //删除结点后，重新链接到该位置的结点是cur->_left
	//				}
	//				delete cur;
	//				break; //需更新平衡因子
	//			}
	//			else //待删除结点的左右子树均不为空
	//			{
	//				//替换法删除
	//				//寻找待删除结点右子树当中key值最小的结点进行删除
	//				Node* minParent = cur;
	//				Node* minRight = cur->_right;
	//				while (minRight->_left)
	//				{
	//					minParent = minRight;
	//					minRight = minRight->_left;
	//				}
	//				cur->_kv.first = minRight->_kv.first; //将待删除结点的key改为minRight的key
	//				cur->_kv.second = minRight->_kv.second; //将待删除结点的value改为minRight的value
	//				//注意一个隐含条件：此时minRight的_left为空
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
	//				delPos = minRight->_right; //删除结点后，重新链接到该位置的结点是minRight->_right
	//				delete minRight;
	//				break; //需更新平衡因子
	//			}
	//		}
	//	}
	//	if (delParentPos == nullptr) //没有找到待删除结点
	//	{
	//		return false;
	//	}
	//	//更新平衡因子
	//	while (delParentPos != nullptr) //最坏一路更新到根结点
	//	{
	//		if (delPos == delParentPos->_left) //delParent的左子树高度降低
	//		{
	//			delParentPos->_bf++; //delParent的平衡因子++
	//		}
	//		else if (delPos == delParentPos->_right) //delParent的右子树高度降低
	//		{
	//			delParentPos->_bf--; //delParent的平衡因子--
	//		}
	//		//判断是否更新结束或需要进行旋转
	//		if (delParentPos->_bf == 0)//需要继续往上更新平衡因子
	//		{
	//			//delParent树的高度变化，会影响其父结点的平衡因子，需要继续往上更新平衡因子
	//			delPos = delParentPos;
	//			delParentPos = delParentPos->_parent;
	//		}
	//		else if (delParentPos->_bf == -1 || delParentPos->_bf == 1) //更新结束
	//		{
	//			break; //delParent树的高度没有发送变化，不会影响其父结点及以上结点的平衡因子
	//		}
	//		else if (delParentPos->_bf == -2 || delParentPos->_bf == 2) //需要进行旋转（此时parent树已经不平衡了）
	//		{
	//			if (delParentPos->_bf == -2)
	//			{
	//				if (delParentPos->_left->_bf == -1)
	//				{
	//					Node* tmp = delParentPos->_left;
	//					RotateR(delParentPos); //右单旋
	//					delParentPos = tmp;
	//				}
	//				else //delParentPos->_left->_bf == 1
	//				{
	//					Node* tmp = delParentPos->_left->_right;
	//					RotateLR(delParentPos); //左右双旋
	//					delParentPos = tmp;
	//				}
	//			}
	//			else //delPP->_bf == 2
	//			{
	//				if (delParentPos->_right->_bf == -1)
	//				{
	//					Node* tmp = delParentPos->_right->_left;
	//					RotateRL(delParentPos); //右左双旋
	//					delParentPos = tmp;
	//				}
	//				else //delParentPos->_right->_bf == 1
	//				{
	//					Node* tmp = delParentPos->_right;
	//					RotateL(delParentPos); //左单旋
	//					delParentPos = tmp;
	//				}
	//			}
	//			//delParent树的高度变化，会影响其父结点的平衡因子，需要继续往上更新平衡因子
	//			delPos = delParentPos;
	//			delParentPos = delParentPos->_parent;
	//			//break;
	//		}
	//		else
	//		{
	//			assert(false); //在插入前树的平衡因子就有问题
	//		}
	//	}
	//	return true;
	//}
	//中序遍历
	void Inorder()
	{
		_Inorder(_root);
	}
	//判断是否为AVL树
	bool IsAVLTree()
	{
		int hight = 0; //输出型参数
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

		//1、以subL为旋转点进行左单旋
		RotateL(subL);

		//2、以parent为旋转点进行右单旋
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

	//中序遍历子函数
	void _Inorder(Node* root)
	{
		if (root == nullptr)
			return;
		_Inorder(root->_left);
		//cout << root->_kv.first << " ";
		cout << "<" << root->_kv.first << "," << root->_kv.second << ">" << endl;
		_Inorder(root->_right);
	}

	//检测二叉树是否平衡
	bool _IsBalanced(Node* root, int& hight)
	{
		if (root == nullptr) //空树是平衡二叉树
		{
			hight = 0; //空树的高度为0
			return true;
		}
		//先判断左子树
		int leftHight = 0;
		if (_IsBalanced(root->_left, leftHight) == false)
			return false;
		//再判断右子树
		int rightHight = 0;
		if (_IsBalanced(root->_right, rightHight) == false)
			return false;
		//检查该结点的平衡因子
		if (rightHight - leftHight != root->_bf)
		{
			cout << "平衡因子设置异常：" << root->_kv.first << endl;
		}
		//把左右子树的高度中的较大值+1作为当前树的高度返回给上一层
		hight = max(leftHight, rightHight) + 1;
		return abs(rightHight - leftHight) < 2; //平衡二叉树的条件
	}
	//析构函数子函数
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