#include <iostream>
using namespace std;

template<class K>
struct BSTreeNode
{
	K _key;                 //���ֵ
	BSTreeNode<K>* _left;   //��ָ�� 
	BSTreeNode<K>* _right;  //��ָ��

	//����һ��ֵΪkey������ָ��Ϊ�յĽ��
	BSTreeNode(const K& key = 0)
		:_key(key)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	//���캯��
	BSTree()
		:_root(nullptr)
	{}

	//������
	Node* _Copy(Node* root)
	{
		if (root == nullptr) //����ֱ�ӷ���
			return nullptr;

		Node* copyNode = new Node(root->_key); //���������
		copyNode->_left = _Copy(root->_left); //����������
		copyNode->_right = _Copy(root->_right); //����������
		return copyNode; //���ؿ�������
	}
	//�������캯��
	BSTree(const BSTree<K>& t)
	{
		_root = _Copy(t._root); //����t����Ķ���������
	}

	//��ֵ��������غ���
	//�ִ�д��
	BSTree<K>& operator=(BSTree<K> t) //������������ֵ��ʱ���Զ����ÿ������캯��
	{
		swap(_root, t._root); //��������������Ķ���������
		return *this; //֧��������ֵ
	}

	////��ͳд��
	//const BSTree<K>& operator=(const BSTree<K>& t)
	//{
	//	if (this != &t) //��ֹ�Լ����Լ���ֵ
	//	{
	//		_root = _Copy(t._root); //����t����Ķ���������
	//	}
	//	return *this; //֧��������ֵ
	//}

	//�ͷ����н��
	void _Destory(Node* root)
	{
		if (root == nullptr) //���������ͷ�
			return;

		_Destory(root->_left); //�ͷ��������еĽ��
		_Destory(root->_right); //�ͷ��������еĽ��
		delete root; //�ͷŸ����
	}
	//��������
	~BSTree()
	{
		_Destory(_root); //�ͷŶ����������еĽ��
		_root = nullptr; //��ʱ�ÿ�
	}

	//���뺯��
	bool Insert(const K& key)
	{
		if (_root == nullptr) //����
		{
			_root = new Node(key); //ֱ������ֵΪkey�Ľ����Ϊ�����������ĸ����
			return true; //����ɹ�������true
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key) //keyֵС�ڵ�ǰ����ֵ
			{
				//���ý�����������
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key) //keyֵ���ڵ�ǰ����ֵ
			{
				//���ý�����������
				parent = cur;
				cur = cur->_right;
			}
			else //keyֵ���ڵ�ǰ����ֵ
			{
				return false; //����ʧ�ܣ�����false
			}
		}
		cur = new Node(key); //����ֵΪkey�Ľ��
		if (key < parent->_key) //keyֵС�ڵ�ǰparent����ֵ
		{
			parent->_left = cur; //��������ӵ�parent�����
		}
		else //keyֵ���ڵ�ǰparent����ֵ
		{
			parent->_right = cur; //��������ӵ�parent���ұ�
		}
		return true; //����ɹ�������true
	}
	//�ݹ���뺯�����Ӻ���
	bool _InsertR(Node*& root, const K& key) //ע������
	{
		if (root == nullptr) //����
		{
			root = new Node(key); //ֱ������ֵΪkey�Ľ����Ϊ���ĸ����
			return true; //����ɹ�������true
		}

		if (key < root->_key) //keyֵС�ڸ�����ֵ
		{
			return _InsertR(root->_left, key); //Ӧ�������뵽����������
		}
		else if (key > root->_key) //keyֵ���ڸ�����ֵ
		{
			return _InsertR(root->_right, key); //Ӧ�������뵽����������
		}
		else //keyֵ���ڸ�����ֵ
		{
			return false; //����ʧ�ܣ�����false
		}
	}
	//�ݹ���뺯��
	bool InsertR(const K& key)
	{
		return _InsertR(_root, key); //�����Ӻ������в���
	}
	//ɾ������������һ��
	bool Erase(const K& key)
	{
		Node* parent = nullptr; //��Ǵ�ɾ�����ĸ����
		Node* cur = _root; //��Ǵ�ɾ�����
		while (cur)
		{
			if (key < cur->_key) //keyֵС�ڵ�ǰ����ֵ
			{
				//���ý�����������
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key) //keyֵ���ڵ�ǰ����ֵ
			{
				//���ý�����������
				parent = cur;
				cur = cur->_right;
			}
			else //�ҵ��˴�ɾ�����
			{
				if (cur->_left == nullptr) //��ɾ������������Ϊ��
				{
					if (cur == _root) //��ɾ������Ǹ���㣬��ʱparentΪnullptr
					{
						_root = cur->_right; //�����������ĸ�����Ϊ�������Һ��Ӽ���
					}
					else //��ɾ����㲻�Ǹ���㣬��ʱparent��Ϊnullptr
					{
						if (cur == parent->_left) //��ɾ��������丸��������
						{
							parent->_left = cur->_right; //��������ָ��ָ���ɾ����������������
						}
						else //��ɾ��������丸�����Һ���
						{
							parent->_right = cur->_right; //��������ָ��ָ���ɾ����������������
						}
					}
					delete cur; //�ͷŴ�ɾ�����
					return true; //ɾ���ɹ�������true
				}
				else if (cur->_right == nullptr) //��ɾ������������Ϊ��
				{
					if (cur == _root) //��ɾ������Ǹ���㣬��ʱparentΪnullptr
					{
						_root = cur->_left; //�����������ĸ�����Ϊ���������Ӽ���
					}
					else //��ɾ����㲻�Ǹ���㣬��ʱparent��Ϊnullptr
					{
						if (cur == parent->_left) //��ɾ��������丸��������
						{
							parent->_left = cur->_left; //��������ָ��ָ���ɾ����������������
						}
						else //��ɾ��������丸�����Һ���
						{
							parent->_right = cur->_left; //��������ָ��ָ���ɾ����������������
						}
					}
					delete cur; //�ͷŴ�ɾ�����
					return true; //ɾ���ɹ�������true
				}
				else //��ɾ������������������Ϊ��
				{
					//�滻��ɾ��
					Node* minParent = cur; //��Ǵ�ɾ���������������ֵ��С���ĸ����
					Node* minRight = cur->_right; //��Ǵ�ɾ���������������ֵ��С�Ľ��
					//Ѱ�Ҵ�ɾ���������������ֵ��С�Ľ��
					while (minRight->_left)
					{
						//һֱ������
						minParent = minRight;
						minRight = minRight->_left;
					}
					cur->_key = minRight->_key; //����ɾ������ֵ��ΪminRight��ֵ
					//ע��һ��������������ʱminRight��_leftΪ��
					if (minRight == minParent->_left) //minRight���丸��������
					{
						minParent->_left = minRight->_right; //��������ָ��ָ��minRight������������
					}
					else //minRight���丸�����Һ���
					{
						minParent->_right = minRight->_right; //��������ָ��ָ��minRight������������
					}
					delete minRight; //�ͷ�minRight
					return true; //ɾ���ɹ�������true
				}
			}
		}
		return false; //û���ҵ���ɾ����㣬ɾ��ʧ�ܣ�����false
	}

	////�ݹ�ɾ���������Ӻ���������һ��
	//bool _EraseR(Node*& root, const K& key)
	//{
	//	if (root == nullptr) //����
	//		return false; //ɾ��ʧ�ܣ�����false

	//	if (key < root->_key) //keyֵС�ڸ�����ֵ
	//		return _EraseR(root->_left, key); //��ɾ������ڸ�������������
	//	else if (key > root->_key) //keyֵ���ڸ�����ֵ
	//		return _EraseR(root->_right, key); //��ɾ������ڸ�������������
	//	else //�ҵ��˴�ɾ�����
	//	{
	//		if (root->_left == nullptr) //��ɾ������������Ϊ��
	//		{
	//			Node* del = root; //��������
	//			root = root->_right; //������������Ϊ�������µĸ����
	//			delete del; //�ͷŸ����
	//		}
	//		else if (root->_right == nullptr) //��ɾ������������Ϊ��
	//		{
	//			Node* del = root; //��������
	//			root = root->_left; //������������Ϊ�������µĸ����
	//			delete del; //�ͷŸ����
	//		}
	//		else //��ɾ������������������Ϊ��
	//		{
	//			Node* minParent = root; //��Ǹ��������������ֵ��С���ĸ����
	//			Node* minRight = root->_right; //��Ǹ��������������ֵ��С�Ľ��
	//			//Ѱ�Ҹ��������������ֵ��С�Ľ��
	//			while (minRight->_left)
	//			{
	//				//һֱ������
	//				minParent = minRight;
	//				minRight = minRight->_left;
	//			}
	//			root->_key = minRight->_key; //��������ֵ��ΪminRight��ֵ
	//			//ע��һ��������������ʱminRight��_leftΪ��
	//			if (minRight == minParent->_left) //minRight���丸��������
	//			{
	//				minParent->_left = minRight->_right; //��������ָ��ָ��minRight������������
	//			}
	//			else //minRight���丸�����Һ���
	//			{
	//				minParent->_right = minRight->_right; //��������ָ��ָ��minRight������������
	//			}
	//			delete minRight; //�ͷ�minRight
	//		}
	//		return true; //ɾ���ɹ�������true
	//	}
	//}
	////�ݹ�ɾ������������һ��
	//bool EraseR(const K& key)
	//{
	//	return _EraseR(_root, key); //ɾ��_root����ֵΪkey�Ľ��
	//}

	////ɾ����������������
	//bool Erase(const K& key)
	//{
	//	Node* parent = nullptr; //��Ǵ�ɾ�����ĸ����
	//	Node* cur = _root; //��Ǵ�ɾ�����
	//	while (cur)
	//	{
	//		if (key < cur->_key) //keyֵС�ڵ�ǰ����ֵ
	//		{
	//			//���ý�����������
	//			parent = cur;
	//			cur = cur->_left;
	//		}
	//		else if (key > cur->_key) //keyֵ���ڵ�ǰ����ֵ
	//		{
	//			//���ý�����������
	//			parent = cur;
	//			cur = cur->_right;
	//		}
	//		else //�ҵ��˴�ɾ�����
	//		{
	//			if (cur->_left == nullptr) //��ɾ������������Ϊ��
	//			{
	//				if (cur == _root) //��ɾ������Ǹ���㣬��ʱparentΪnullptr
	//				{
	//					_root = cur->_right; //�����������ĸ�����Ϊ�������Һ��Ӽ���
	//				}
	//				else //��ɾ����㲻�Ǹ���㣬��ʱparent��Ϊnullptr
	//				{
	//					if (cur == parent->_left) //��ɾ��������丸��������
	//					{
	//						parent->_left = cur->_right; //��������ָ��ָ���ɾ����������������
	//					}
	//					else //��ɾ��������丸�����Һ���
	//					{
	//						parent->_right = cur->_right; //��������ָ��ָ���ɾ����������������
	//					}
	//				}
	//				delete cur; //�ͷŴ�ɾ�����
	//				return true; //ɾ���ɹ�������true
	//			}
	//			else if (cur->_right == nullptr) //��ɾ������������Ϊ��
	//			{
	//				if (cur == _root) //��ɾ������Ǹ���㣬��ʱparentΪnullptr
	//				{
	//					_root = cur->_left; //�����������ĸ�����Ϊ���������Ӽ���
	//				}
	//				else //��ɾ����㲻�Ǹ���㣬��ʱparent��Ϊnullptr
	//				{
	//					if (cur == parent->_left) //��ɾ��������丸��������
	//					{
	//						parent->_left = cur->_left; //��������ָ��ָ���ɾ����������������
	//					}
	//					else //��ɾ��������丸�����Һ���
	//					{
	//						parent->_right = cur->_left; //��������ָ��ָ���ɾ����������������
	//					}
	//				}
	//				delete cur; //�ͷŴ�ɾ�����
	//				return true; //ɾ���ɹ�������true
	//			}
	//			else //��ɾ������������������Ϊ��
	//			{
	//				//�滻��ɾ��
	//				Node* minRight = cur->_right; //��Ǵ�ɾ���������������ֵ��С�Ľ��
	//				//Ѱ�Ҵ�ɾ���������������ֵ��С�Ľ��
	//				while (minRight->_left)
	//				{
	//                  //һֱ������
	//					minRight = minRight->_left;
	//				}
	//				K minKey = minRight->_key; //��¼minRight����ֵ
	//				Erase(minKey); //minRight�����ɾ����㱻ɾ��
	//				cur->_key = minKey; //����ɾ������ֵ��Ϊ�����䱻ɾ���Ľ���ֵ����minRight
	//			}
	//		}
	//	}
	//	return false; //û���ҵ���ɾ����㣬ɾ��ʧ�ܣ�����false
	//}

	//�ݹ�ɾ���������Ӻ�������������
	bool _EraseR(Node*& root, const K& key)
	{
		if (root == nullptr) //����
			return false; //ɾ��ʧ�ܣ�����false

		if (key < root->_key) //keyֵС�ڸ�����ֵ
			return _EraseR(root->_left, key); //��ɾ������ڸ�������������
		else if (key > root->_key) //keyֵ���ڸ�����ֵ
			return _EraseR(root->_right, key); //��ɾ������ڸ�������������
		else //�ҵ��˴�ɾ�����
		{
			if (root->_left == nullptr) //��ɾ������������Ϊ��
			{
				Node* del = root; //��������
				root = root->_right; //������������Ϊ�������µĸ����
				delete del; //�ͷŸ����
			}
			else if (root->_right == nullptr) //��ɾ������������Ϊ��
			{
				Node* del = root; //��������
				root = root->_left; //������������Ϊ�������µĸ����
				delete del; //�ͷŸ����
			}
			else //��ɾ������������������Ϊ��
			{
				Node* minRight = root->_right; //��Ǹ��������������ֵ��С�Ľ��
				//Ѱ�Ҹ��������������ֵ��С�Ľ��
				while (minRight->_left)
				{
					//һֱ������
					minRight = minRight->_left;
				}
				K minKey = minRight->_key; //��¼minRight����ֵ
				_EraseR(root->_right, minKey); //ɾ������������ֵΪminkey�Ľ�㣬��ɾ��minRight
				root->_key = minKey; //��������ֵ��ΪminRight��ֵ
			}
			return true; //ɾ���ɹ�������true
		}
	}
	//�ݹ�ɾ����������������
	bool EraseR(const K& key)
	{
		return _EraseR(_root, key); //ɾ��_root����ֵΪkey�Ľ��
	}

	//���Һ���
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key) //keyֵС�ڸý���ֵ
			{
				cur = cur->_left; //�ڸý������������в���
			}
			else if (key > cur->_key) //keyֵ���ڸý���ֵ
			{
				cur = cur->_right; //�ڸý������������в���
			}
			else //�ҵ���ֵΪkey�Ľ��
			{
				return cur; //���ҳɹ������ؽ���ַ
			}
		}
		return nullptr; //��Ϊ�ջ����ʧ�ܣ�����nullptr
	}
	//�ݹ���Һ������Ӻ���
	Node* _FindR(Node* root, const K& key)
	{
		if (root == nullptr) //��Ϊ��
			return nullptr; //����ʧ�ܣ�����nullptr

		if (key < root->_key) //keyֵС�ڸ�����ֵ
		{
			return _FindR(root->_left, key); //�ڸ��������������в���
		}
		else if (key > root->_key) //keyֵ���ڸ�����ֵ
		{
			return _FindR(root->_right, key); //�ڸ��������������в���
		}
		else //keyֵ���ڸ�����ֵ
		{
			return root; //���ҳɹ������ظ�����ַ
		}
	}
	//�ݹ���Һ���
	Node* FindR(const K& key)
	{
		return _FindR(_root, key); //��_root���в���ֵΪkey�Ľ��
	}
	//����������Ӻ���
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left); //����������
		cout << root->_key << " "; //���������
		_InOrder(root->_right); //����������
	}
	//�������
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
private:
	Node* _root; //�����������ĸ����
};




////�����
//template<class K>
//struct BSTreeNode
//{
//	K _key;                 //���ֵ
//	BSTreeNode<K>* _left;   //��ָ�� 
//	BSTreeNode<K>* _right;  //��ָ��
//
//	//���캯��
//	BSTreeNode(const K& key = 0)
//		:_key(key)
//		, _left(nullptr)
//		, _right(nullptr)
//	{}
//};

////����������
//template<class K>
//class BSTree
//{
//	typedef BSTreeNode<K> Node;
//public:
//	//���캯��
//	BSTree();
//
//	//�������캯��
//	BSTree(const BSTree<K>& t);
//
//	//��ֵ��������غ���
//	BSTree<K>& operator=(BSTree<K> t);
//
//	//��������
//	~BSTree();
//
//	//���뺯��
//	bool Insert(const K& key);
//
//	//ɾ������
//	bool Erase(const K& key);
//
//	//���Һ���
//	Node* Find(const K& key);
//
//	//�������
//	void InOrder();
//private:
//	Node* _root; //ָ������������ĸ����
//};










//#include <iostream>
//using namespace std;
//template<class K>
//struct BSTreeNode
//{
//	K _key;
//	BSTreeNode<K>* _left;
//	BSTreeNode<K>* _right;
//	BSTreeNode(const K& key)
//		:_key(key)
//		, _left(nullptr)
//		, _right(nullptr)
//	{}
//};
//
//template<class K>
//class BSTree
//{
//	typedef BSTreeNode<K> Node;
//public:
//	//�ǵݹ�
//	bool Insert(const K& key)
//	{
//		if (_root == nullptr)
//		{
//			_root = new Node(key);
//			return true;
//		}
//		Node* parent = nullptr;
//		Node* cur = _root;
//		while (cur)
//		{
//			if (key > cur->_key)
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//			else if (key < cur->_key)
//			{
//				parent = cur;
//				cur = cur->_left;
//			}
//			else
//			{
//				return false;
//			}
//		}
//		cur = new Node(key);
//		if (cur = parent->_left) //error
//		{
//			parent->_left = cur;
//		}
//		else
//		{
//			parent->_right = cur;
//		}
//		return true;
//	}
//	bool Erase(const K& key)
//	{
//		Node* parent = nullptr;
//		Node* cur = _root;
//		while (cur)
//		{
//			if (key > cur->_key)
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//			else if (key < cur->_key)
//			{
//				parent = cur;
//				cur = cur->_left;
//			}
//			else
//			{
//
//			}
//		}
//	}
//	Node* Find(const K& key)
//	{
//		Node* cur = _root;
//		while (cur)
//		{
//			if (key > cur->_key)
//			{
//				cur = cur->_right;
//			}
//			else if (key < cur->_key)
//			{
//				cur = cur->_left;
//			}
//			else
//			{
//				return cur;
//			}
//		}
//		return nullptr;
//	}
//private:
//	Node* _root;
//};