#pragma once
#include<iostream>
using namespace std;

enum Color
{
	RED,
	BLACK,
};
template <class K,class V>
struct RBTreeNode
{
	RBTreeNode<K, V> *_left;
	RBTreeNode<K, V>  *_right;
	RBTreeNode<K, V> *_parent;
	K _key;
	V _value;
	Color _col;

	RBTreeNode(const K& key, const V& value)
		:_col(RED)
		, _key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template<class K,class V>
class RBTree
{
	typedef    RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root()
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_col = BLACK;
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key, value);
		if (key < parent->_key)
		{
			parent->_left = cur;
			cur->_parent=parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		//进行结点颜色调整
		while (cur != _root && parent->_col == RED)//满足此条件的结点其父节点一定存在	 
		{
			Node* grandpa = parent->_parent;
			if (parent==grandpa->_left )
			{
				Node* uncle =  grandpa->_right;
				if (uncle&&uncle->_col == RED)
				{
					uncle->_col = BLACK;
					parent->_col = BLACK;
					grandpa->_col = RED;
					cur = grandpa;
					parent = cur->_parent;
				}
				else	//
				{															   //旋转
					if (cur == parent->_right)				 //3
					{
						RotateL(parent);
						swap(cur, parent);
					}
					RotateR(grandpa);
					parent->_col = BLACK;
					grandpa->_col = RED;
				}
			}
			else
			{
				Node* uncle = grandpa->_left;
				if (uncle&&uncle->_col == RED)
				{
					uncle->_col = BLACK;
					parent->_col = BLACK;
					grandpa->_col = RED; 
					cur = grandpa;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}
					RotateL(grandpa);
					parent->_col = BLACK;
					grandpa->_col = RED;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subR->_left;
		if (subRL != NULL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		Node* ppNode = parent->_parent;
		subR->_parent = ppNode;
		if (ppNode == NULL)
		{
			_root = subR;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
		}
		parent->_parent = subR;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR != NULL)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		Node* ppNode = parent->_parent;
		subL->_parent = ppNode;
		if (ppNode == NULL)
		{
			_root = subL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
		}
		parent->_parent = subL;
	}

	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

	bool CheckRBTree()
	{
		if (_root&& _root->_col == RED)
		{
			cout << "根节点必须为黑" << endl;
			return false;
		}
		int NodeNum = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				++NodeNum;
			}
			cur = cur->_left;
		}
		int count = 0;
		return _CheckRBTree(_root, NodeNum, count);
	}


protected:
	Node* _root;

	void _Inorder(Node* root)
	{
		if (root == NULL)
		{
			return ;
		}
		_Inorder(root->_left);
		cout << root->_key << "	";
		_Inorder(root->_right);
	}

	bool _CheckRBTree(Node* root,const int NodeNum, int count)
	{
		  //检查每个结点从该结点到所以后代的简单路径上含有相同数目的黑结点
		if (root == NULL)
		{
			return true;
		}
		Node* parent = root->_parent;
		if (root->_col == RED && root->_parent && parent->_col == RED)
		{
			cout << "违反了规则3" << endl;
			return false;
		}
		if (root->_col == BLACK)
		{
			++count;
		}
		if (root->_left == NULL && root->_right == NULL && NodeNum != count)
		{
			cout << "违反了规则4" << endl;
			return false;
		}
		return _CheckRBTree(root->_left, NodeNum, count) && _CheckRBTree(root->_left, NodeNum, count);
	}
};
