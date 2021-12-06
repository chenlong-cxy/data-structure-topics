#pragma once
#include <iostream>
#include <assert.h>
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

	//插入函数
	pair<Node*, bool> Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr) //若红黑树为空树，则插入结点直接作为根结点
		{
			_root = new Node(kv);
			_root->_col = BLACK; //根结点必须是黑色
			return make_pair(_root, true); //插入成功
		}
		//1、按二叉搜索树的插入方法，找到待插入位置
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
				return make_pair(cur, false); //插入失败
			}
		}

		//2、将待插入结点插入到树中
		cur = new Node(kv); //根据所给值构造一个结点
		Node* newnode = cur; //记录新插入的结点（便于后序返回）
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

		//3、若插入结点的父结点是红色的，则需要对红黑树进行调整
		while (parent&&parent->_col == RED)
		{
			Node* grandfather = parent->_parent; //parent是红色，则其父结点一定存在
			if (parent == grandfather->_left) //parent是grandfather的左孩子
			{
				Node* uncle = grandfather->_right; //uncle是grandfather的右孩子
				if (uncle&&uncle->_col == RED) //情况1：uncle存在且为红
				{
					//颜色调整
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					//继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else //情况2+情况3：uncle不存在 + uncle存在且为黑
				{
					if (cur == parent->_left)
					{
						RotateR(grandfather); //右单旋

						//颜色调整
						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					else //cur == parent->_right
					{
						RotateLR(grandfather); //左右双旋

						//颜色调整
						grandfather->_col = RED;
						cur->_col = BLACK;
					}
					break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
				}
			}
			else //parent是grandfather的右孩子
			{
				Node* uncle = grandfather->_left; //uncle是grandfather的左孩子
				if (uncle&&uncle->_col == RED) //情况1：uncle存在且为红
				{
					//颜色调整
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;

					//继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else //情况2+情况3：uncle不存在 + uncle存在且为黑
				{
					if (cur == parent->_left)
					{
						RotateRL(grandfather); //右左双旋

						//颜色调整
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					else //cur == parent->_right
					{
						RotateL(grandfather); //左单旋

						//颜色调整
						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
				}
			}
		}
		_root->_col = BLACK; //根结点的颜色为黑色（可能被情况一变成了红色，需要变回黑色）
		return make_pair(newnode, true); //插入成功
	}

	//删除函数
	bool Erase(const K& key)
	{
		//用于遍历二叉树
		Node* parent = nullptr;
		Node* cur = _root;
		//用于标记实际的待删除结点及其父结点
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
						{
							_root->_parent = nullptr;
							_root->_col = BLACK; //根结点为黑色
						}
						delete cur; //删除原根结点
						return true;
					}
					else
					{
						delParentPos = parent; //标记实际删除结点的父结点
						delPos = cur; //标记实际删除的结点
					}
					break; //进行红黑树的调整以及结点的实际删除
				}
				else if (cur->_right == nullptr) //待删除结点的右子树为空
				{
					if (cur == _root) //待删除结点是根结点
					{
						_root = _root->_left; //让根结点的左子树作为新的根结点
						if (_root)
						{
							_root->_parent = nullptr;
							_root->_col = BLACK; //根结点为黑色
						}
						delete cur; //删除原根结点
						return true;
					}
					else
					{
						delParentPos = parent; //标记实际删除结点的父结点
						delPos = cur; //标记实际删除的结点
					}
					break; //进行红黑树的调整以及结点的实际删除
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
					break; //进行红黑树的调整以及结点的实际删除
				}
			}
		}
		if (delPos == nullptr) //delPos没有被修改过，说明没有找到待删除结点
		{
			return false;
		}

		//记录待删除结点及其父结点（用于后续实际删除）
		Node* del = delPos;
		Node* delP = delParentPos;

		//调整红黑树
		if (delPos->_col == BLACK) //删除的是黑色结点
		{
			if (delPos->_left) //待删除结点有一个红色的左孩子（不可能是黑色）
			{
				delPos->_left->_col = BLACK; //将这个红色的左孩子变黑即可
			}
			else if (delPos->_right) //待删除结点有一个红色的右孩子（不可能是黑色）
			{
				delPos->_right->_col = BLACK; //将这个红色的右孩子变黑即可
			}
			else //待删除结点的左右均为空
			{
				while (delPos != _root) //可能一直调整到根结点
				{
					if (delPos == delParentPos->_left) //待删除结点是其父结点的左孩子
					{
						Node* brother = delParentPos->_right; //兄弟结点是其父结点的右孩子
						//情况一：brother为红色
						if (brother->_col == RED)
						{
							delParentPos->_col = RED;
							brother->_col = BLACK;
							RotateL(delParentPos);
							//需要继续处理
							brother = delParentPos->_right; //更新brother（否则在本循环中执行其他情况的代码会出错）
						}
						//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
						if (((brother->_left == nullptr) || (brother->_left->_col == BLACK))
							&& ((brother->_right == nullptr) || (brother->_right->_col == BLACK)))
						{
							brother->_col = RED;
							if (delParentPos->_col == RED)
							{
								delParentPos->_col = BLACK;
								break;
							}
							//需要继续处理
							delPos = delParentPos;
							delParentPos = delPos->_parent;
						}
						else
						{
							//情况三：brother为黑色，且其左孩子是红色结点，右孩子是黑色结点或为空
							if ((brother->_right == nullptr) || (brother->_right->_col == BLACK))
							{
								brother->_left->_col = BLACK;
								brother->_col = RED;
								RotateR(brother);
								//需要继续处理
								brother = delParentPos->_right; //更新brother（否则执行下面情况四的代码会出错）
							}
							//情况四：brother为黑色，且其右孩子是红色结点
							brother->_col = delParentPos->_col;
							delParentPos->_col = BLACK;
							brother->_right->_col = BLACK;
							RotateL(delParentPos);
							break; //情况四执行完毕后调整一定结束
						}
					}
					else //delPos == delParentPos->_right //待删除结点是其父结点的左孩子
					{
						Node* brother = delParentPos->_left; //兄弟结点是其父结点的左孩子
						//情况一：brother为红色
						if (brother->_col == RED) //brother为红色
						{
							delParentPos->_col = RED;
							brother->_col = BLACK;
							RotateR(delParentPos);
							//需要继续处理
							brother = delParentPos->_left; //更新brother（否则在本循环中执行其他情况的代码会出错）
						}
						//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
						if (((brother->_left == nullptr) || (brother->_left->_col == BLACK))
							&& ((brother->_right == nullptr) || (brother->_right->_col == BLACK)))
						{
							brother->_col = RED;
							if (delParentPos->_col == RED)
							{
								delParentPos->_col = BLACK;
								break;
							}
							//需要继续处理
							delPos = delParentPos;
							delParentPos = delPos->_parent;
						}
						else
						{
							//情况三：brother为黑色，且其右孩子是红色结点，左孩子是黑色结点或为空
							if ((brother->_left == nullptr) || (brother->_left->_col == BLACK))
							{
								brother->_right->_col = BLACK;
								brother->_col = RED;
								RotateL(brother);
								//需要继续处理
								brother = delParentPos->_left; //更新brother（否则执行下面情况四的代码会出错）
							}
							//情况四：brother为黑色，且其左孩子是红色结点
							brother->_col = delParentPos->_col;
							delParentPos->_col = BLACK;
							brother->_left->_col = BLACK;
							RotateR(delParentPos);
							break; //情况四执行完毕后调整一定结束
						}
					}
				}
			}
		}
		//进行实际删除
		if (del->_left == nullptr) //实际删除结点的左子树为空
		{
			if (del == delP->_left) //实际删除结点是其父结点的左孩子
			{
				delP->_left = del->_right;
				if (del->_right)
					del->_right->_parent = delP;
			}
			else //实际删除结点是其父结点的右孩子
			{
				delP->_right = del->_right;
				if (del->_right)
					del->_right->_parent = delP;
			}
		}
		else //实际删除结点的右子树为空
		{
			if (del == delP->_left) //实际删除结点是其父结点的左孩子
			{
				delP->_left = del->_left;
				if (del->_left)
					del->_left->_parent = delP;
			}
			else //实际删除结点是其父结点的右孩子
			{
				delP->_right = del->_left;
				if (del->_left)
					del->_left->_parent = delP;
			}
		}
		delete del; //实际删除结点
		return true;
	}
	
	//判断是否为红黑树
	bool ISRBTree()
	{
		if (_root == nullptr) //空树是红黑树
		{
			return true;
		}
		if (_root->_col == RED)
		{
			cout << "error：根结点为红色" << endl;
			return false;
		}
		
		//找最左路径作为黑色结点数目的参考值
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

	//中序遍历
	void Inorder()
	{
		_Inorder(_root);
	}
private:
	//中序遍历子函数
	void _Inorder(Node* root)
	{
		if (root == nullptr)
			return;
		_Inorder(root->_left);
		cout << root->_kv.first << " ";
		_Inorder(root->_right);
	}

	//判断是否为红黑树的子函数
	bool _ISRBTree(Node* root, int count, int BlackCount)
	{
		if (root == nullptr) //该路径已经走完了
		{
			if (count != BlackCount)
			{
				cout << "error：黑色结点的数目不相等" << endl;
				return false;
			}
			return true;
		}

		if (root->_col == RED&&root->_parent->_col == RED)
		{
			cout << "error：存在连续的红色结点" << endl;
			return false;
		}
		if (root->_col == BLACK)
		{
			count++;
		}
		return _ISRBTree(root->_left, count, BlackCount) && _ISRBTree(root->_right, count, BlackCount);
	}

	//析构函数子函数
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
		Node* subRL = subR->_left;
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