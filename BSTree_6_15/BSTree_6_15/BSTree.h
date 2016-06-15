#pragma once
#include<iostream>
#include<cassert>
using namespace std;
  
template<class K,class V>
struct BSTreeNode
{
	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>* _right;
	K _key;
	V _value;

	BSTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class K,class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
protected:
	Node* _root;
public:
	BSTree()
		:_root(NULL)
	{}

	~BSTree()
	{
		_Destory(_root);
		_root = NULL;
	}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)	  //小于key
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)		   //大于key
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		if (key > parent->_key)		  //大于当前树的所有结点
		{
			Node*  newNode = new Node(key, value);
			parent->_right = newNode;
		}
		else
		{
			Node*  newNode = new Node(key, value);
			parent->_left = newNode;
		}
		return true;
	}

	bool InsertR(const K& key, const V& value)			 //递归版
	{
		return _InsertR(_root, key, value);
	}

	void Inorder()				//中序遍历刚好从小到大
	{
		_Inorder(_root);
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else if (key>cur->_key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return  NULL;
	}

	Node* FindR(const K& key)		  //递归
	{
		return _FindR(_root,key);
	}

	bool Remove(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;
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
				break;
			}
		}
		if (cur == NULL)
		{
			return false;
		}
		Node* del = NULL;
		if (cur->_left == NULL)
		{
			if (parent == NULL)		 //删除的为根节点
			{
				_root = cur->_right;		 //cur左已经为空，直接用右去替换
			}
			else
			{
				del = cur;
				if (parent->_left == cur)
				{
					parent->_left = cur->_right;	 //因为cur为parent的左孩子，因此要删除它可直接将cur的右孩子赋给它
				}
				else
				{
					parent->_right = cur->_right;
				}
			}
		}
		else if (cur->_right == NULL)
		{
			if (parent == NULL)
			{
				_root = cur->_left;
			}
			else
			{
				del = cur;
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_left;
				}
			}
		}
		else			//cur->left、cur->right均不为空
		{
			Node* parent = cur;
			Node* firstleft = cur->_right;
			while (firstleft->_left!=NULL)	//找右子树的最左结点  
			{
				parent = firstleft;
				firstleft = firstleft->_left;
			}
			del = firstleft;
			cur->_key = firstleft->_key;
			cur->_value = firstleft->_value;
			if (parent->_left == firstleft)
			{
				parent->_left = firstleft->_right;
			}
			else	  // (parent->_right== firstleft
			{
				parent->_right = firstleft->_right;
			}
		}
		delete del;
		return true;
	}

	bool RemoveR(const K& key)
	{
		return _RemoveR(_root, key);
	}


protected:
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

	void _Inorder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_Inorder(root->_left);
		cout << root->_key << "----" << root->_value<<endl;
		_Inorder(root->_right);
	}
	
	bool _InsertR(Node*& root, const K& key, const V&  value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}
		if (root->_key > key)
		{
			return _InsertR(root->_left, key, value);
		}
		else if (root->_key < key)
		{
			return _InsertR(root->_right, key, value);
		}
		else
		{
			return false;
		}
	}

	Node* _FindR(Node* root, const K& key)
	{
		if (root == NULL)
		{
			return NULL;
		}
		if (root->_key > key)
		{
			return _FindR(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _FindR(root->_right, key);
		}
		else
		{
			return root;
		}
	}

	bool _RemoveR(Node*& root, const K& key)
	{
		if (root == NULL)
		{
			return false;
		}
		if (root->_key > key)
		{
			return _RemoveR(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _RemoveR(root->_right, key);
		}
		else
		{
			Node* del = root;
			if (root->_left == NULL)
			{
				root = root->_right;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
			}
			else
			{
				Node* firstleft = root->_right;//找右树第一个结点
				while (firstleft->_left != NULL)
				{
					firstleft = firstleft->_left;
				}
				swap(root->_key, firstleft->_key);
				swap(root->_value, firstleft->_value);
				return _RemoveR(root->_right, key);
			}
			delete del;
		}
		return true;
	}

};
