#pragma once
#include<iostream>
using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V> *_left;
	AVLTreeNode<K, V> *_right;
	AVLTreeNode<K, V> *_parent;
	K _key;
	V _value;
	int _bf;

	AVLTreeNode(const K& key, const V& value)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(value)
		, _bf(0)
	{}
};

template <class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	~AVLTree()
	{
		_Destory(_root);
		_root = NULL;
	}

	void InoderTree()
	{
		_InorderTree(_root);
		cout << endl;
	}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node* parent =NULL;
		Node* cur =_root;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key<key)
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
		if (parent->_key < key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		//检查树是否平衡
		//更新平衡因子，不满足条件时旋转
		while (parent)
		{
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == -1 || parent->_bf == 1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			else//-2 2
			{
				//旋转处理
				if (cur->_bf == 1)
				{
					if (parent->_bf == 2)
					{
						RotateL(parent);
					}
				   if (parent->_bf == -2)
					{
						RotateLR(parent);
					}
				}
				else		  
				{
					if (parent->_bf == -2)
					{
						RotateR(parent);
					}
					else
					{
						RotateRL(parent);
					}
				
				}
			    break;
			}
		}
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
		parent->_bf = subR->_bf = 0;
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
		parent->_bf = subL->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		RotateL(parent->_left);
		RotateR(parent);
		int bf = subLR->_bf;
		if (bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
		}
		else if (bf == 1)
		{
			subL->_bf = -1;
			parent->_bf = 0;
		}
	}

	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		RotateR(parent->_right);
		RotateL(parent);
		int bf = subRL->_bf;
		if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = 1;
		}
		else
		{
			subR->_bf = -1;
			parent->_bf = 1;
		}
	}

	bool IsBalance()
	{
		return _IsBalance(_root);
	}


protected:
	bool _IsBalance(Node* root)
	{
		if (root == NULL)
		{
			return true;
		}
		int left = _Height(root->_left);
		int right = _Height(root->_right);
		int bf = abs(right - left);
		if (right-left!=root->_bf || bf>=2 )
		{
			cout << root->_key << "平衡因子有误！" << endl;
			return false;
		}
		else if (bf != abs(root->_bf))
		{
			cout << root->_key<< "平衡因子有误！" << endl;
			return false;
		}
		return _IsBalance(root->_left) && _IsBalance(root->_right);
	}

	int _Height(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		int left = _Height(root->_left);
		int right = _Height(root->_right);
		return left > right ? left + 1 : right + 1;
	}

	void _InorderTree(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_InorderTree(root->_left);
		cout << root->_key<<"	";
		_InorderTree(root->_right);
	}

	void _Destory(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}
protected:
	Node* _root;

};