#pragma once
 
#include<iostream>
#include<vector>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	//typedef BinaryTreeNode<T> Node;
	 T _data;
	 BinaryTreeNode<T> *_left;
	 BinaryTreeNode<T> *_right;

	 BinaryTreeNode(const T& x)
		 :_data(x)
		 ,_left(NULL)
		 ,_right(NULL)
	 {}
	 
};

template<class T>
class BinaryTree
{
public:
	
	BinaryTree()//无参构造
		:_root(NULL)
	{}

	BinaryTree( const T* a,size_t size,const T& invalid)
	{
		size_t index=0;
		_root=_CreatTree(a,size,index,invalid);
	}

	BinaryTree(const BinaryTree& tree)
	{
		_root=_Copy(tree._root);
	}

	~BinaryTree()
	{
		_Destory(_root);
	}

	BinaryTree& operator=(const BinaryTree tree)
	{
		swap(_root,tree._root);
		return *this;
	}

	void  PrevOrder()
	{
		_PrevOrder(_root);
		cout<<endl;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}
	   
	void LevelOrder()
	{
		_LevelOrder(_root);
		cout<<endl;
	}

	size_t Size()
	{
		return _Size(_root);
	}

	size_t Depth()
	{
		return _Depth(_root);
	}

protected:
	BinaryTreeNode<T>* _CreatTree(const T* a,size_t size,size_t &index,const T& invalid)
	{
		BinaryTreeNode<T>* root=NULL;
		if(index < size  &&  a[index]!=invalid)
		{
		   root=new	 BinaryTreeNode<T>(a[index]);
		   root->_left=_CreatTree(a,size,++index,invalid);
		   root->_right=_CreatTree(a,size,++index,invalid); 
		}
		return root;
	}

	void _PrevOrder(BinaryTreeNode<T>* root)//前序
	{
		if(root==NULL)
		{
			return;
		}
		cout<<root->_data<<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _InOrder(BinaryTreeNode<T>* root)//中序
	{
		if(root==NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}

	void _PostOrder(BinaryTreeNode<T>* root)//后序
	{
		if(root==NULL)
		{
			return;
		}
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_data<<" ";
	}

	void _LevelOrder(BinaryTreeNode<T>* root)//层序
	{		   
		if(root==NULL)
		{
			return;
		}
		vector<BinaryTreeNode<T>*> vec;
		vec.push_back(root);
		int cur=0;
		int end=1;
		while(cur<vec.size())
		{
			end=vec.size();
			while(cur<end)
			{			 
				cout<<vec[cur]->_data<<" ";
				if(vec[cur]->_left)
				{
					vec.push_back(vec[cur]->_left);
				}
				if(vec[cur]->_right)
				{
					vec.push_back(vec[cur]->_right);
				}
				cur++;
			}
		}
		
	}

	BinaryTreeNode<T>* _Copy(BinaryTreeNode<T>* root)
	{
		if(root==NULL)
		{
			return NULL;
		}

		BinaryTreeNode<T>* newroot=new BinaryTreeNode<T>(root->_data);
		newroot->_left=_Copy(root->_left);
		newroot->_right=_Copy(root->_right);
		return newroot;
	}

	void _Destory(BinaryTreeNode<T>* root)
	{
		if(root==NULL)
		{
			return;
		}

		BinaryTreeNode<T>* cur=root;
		BinaryTreeNode<T>* del=cur;
		if(cur->_left)
		{
			_Destory(cur->_left);
		}
		if(cur->_right)
		{
			_Destory(cur->_right);
		}
		delete del;

	}

	size_t _Depth(BinaryTreeNode<T> *root)
	{
		BinaryTreeNode<T> *cur=root;
		if(root==NULL)
		{
			return 0;
		}
		size_t dep=1;
		if(cur->_left)
		{
			_Depth(cur->_left);
			dep++;
		}
		if(cur->_right)
		{
			_Depth(cur->_right);
			dep++;
		}
		return dep;
	}

	size_t _Size(BinaryTreeNode<T> *root)
	{
		if(root==NULL)
		{
			return 0;
		}

		BinaryTreeNode<T> *cur=root;
		size_t size=1;
		while(cur!=NULL)
		{
			size+=_Size(root->_left);
			size+=_Size(root->_right);
		}
		return size;
	}

protected:
	BinaryTreeNode<T> *_root;											 
};											    