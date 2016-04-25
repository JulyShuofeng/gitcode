#pragma once
#include<iostream>
  
using namespace std;

enum PointTag
{
	THREAD,
	LINK,
}; 

template<class T>
struct BinaryTreeNode_Thd
{
	T _data;
	BinaryTreeNode_Thd<T>* _left;
	BinaryTreeNode_Thd<T>* _right;
	PointTag _leftTag;
	PointTag _rightTag;

	 BinaryTreeNode_Thd(const T& x)
	  :_data(x)
	  ,_left(NULL)
	  ,_right(NULL)
	  ,_leftTag(LINK)
	  ,_rightTag(LINK)
  {}
};

template<class T>
class BinaryTreeThd
{
	typedef BinaryTreeNode_Thd<T> Node;
public:
 	BinaryTreeThd()	 //无参构造
		:_root(NULL)
	{}

	 BinaryTreeThd(const T* a,size_t size,const T& invalid)
	 {
		 size_t index=0;
		 _root=_CreatTree(a,size,index,invalid);
	 }

	 void InOrderThreading()
	 {
	 	Node* prev=NULL;
		_InOrderThreading(_root,prev);
	 }

protected:

	Node* _CreatTree(const T* a,size_t size,size_t& index,const T &invalid)
	{
		Node* root=NULL;
		if(index<size && a[index]!=invalid)
		{
		   root=new Node(a[index]);
		   root->_left=_CreatTree(a,size,index+1,invalid);
		   root->_right=_CraetTree(a,size,index+1,invalid);
		}
		return root;
	}

	 void _InOrderThreading(Node* cur,Node* prev)
	 {
		if(root==NULL)
		{
			return;
		}
		_InOrderThreading(cur->_left,prev);
		if(cur->_left==NULL)
		{
			cur->_leftTag=THREAD;
			cur->_left=prev;
		}
		if(prev!=NULL && prev->_right==NULL)
		{
			prev->_rightTag=THREAD;
			cur->left=prev;
		}
		prev=cur;
		_InOrderThreading(cur->_right,prev);
	 }

protected:
	Node* _root;
};