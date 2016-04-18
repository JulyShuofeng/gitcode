#include<iostream>
using namespace std;

#pragma once

typedef int DataType;

struct Node
{ 
	DataType _data;
	struct Node* _next;
	Node(const DataType& d)
		:_data(d)
		,_next(NULL)
	{

	}
};

class sList
{
public:
	sList()
		:_head(NULL)
		,_tail(NULL)
	{

	}

	~sList()
	{
		if(_head==NULL)
		{
			return;
		}
		Node *cur=_head;
		while(cur->_next!=NULL)
		{
			Node *del=cur;
			cur=cur->_next;
			delete del;
		}
		delete cur;
	}

	sList(const sList& s)
		:_head(NULL)
		,_tail(NULL)
	{
		Node* cur=s._head;
		while(cur)
		{
			(cur->_data);
			cur=cur->_next;
		}
	}

	sList& operator=(sList& s)
	{
		swap(_head,s._head);
		swap(_tail,s._tail);
	}

	friend ostream& operator<<(ostream& os,const sList& s);

	void PushBack(const DataType& d);
	void PushFront(const DataType& d);
	void PopBack();
	void PopFront();
	Node* Find(const DataType& d);
	void Insert(Node* pos,const DataType& d);
	void Reverse();
	void Sort();
	void Remove(const DataType& d);
	void RemoveAll(const DataType& d);
	  
	void Erase(Node* pos);
	//sList Merge(sList s1,sList s2);
	Node* FindMidNode();
	//int CheckCross(sList s1,sList s2);
	Node* CheckCircle();
	int GetCircleLength(Node* meet);
	Node* GetCircleEntryNode(Node* meet);
	void DelkNode(int k);

private:
	Node *_head;
	Node *_tail;
};

ostream& operator<<(ostream& os,const sList& s)
{
	Node* cur=s._head;
	while(cur!=NULL)
	{
		os<<cur->_data<<"->";
		cur=cur->_next;
	}
	cout<<"over"<<endl;
	return os;
}