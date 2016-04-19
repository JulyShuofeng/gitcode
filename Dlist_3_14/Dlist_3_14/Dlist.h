#include<iostream>
using namespace std;

#pragma once

typedef int DataType;

struct Node
{
	Node* _next;
	Node* _prev;
	DataType _data;
	Node(const DataType& d)
		:_data(d)
		,_prev(NULL)
		,_next(NULL)
	{

	}
};

class Dlist
{
public:
	Dlist()
		:_head(NULL)
		,_tail(NULL)
	{

	}

	~Dlist()
	{
		Node* cur=_head;
		while(cur)
		{
			Node* del=cur;
			cur=cur->_next;
			delete del;
		}
	}

	friend ostream& operator<<(ostream& os,const Dlist& l);

	void PushBack(const DataType& d);
	void PopBack();
	void PushFront(const DataType& d);
	void PopFront();
	Node* Find(const DataType& d);
	void Insert(Node* pos,const DataType& d);
	void Sort();
	void Reverse();
	void Remove(const DataType& d);
	void Erase(Node* pos);


private:
	Node* _head;
	Node* _tail;
};

ostream& operator<<(ostream& os,const Dlist& l)
{
	Node* cur=l._head;
	while(cur)
	{
		os<<cur->_data<<"<->";
		cur=cur->_next;
	}
	os<<"over"<<endl;
	return os;
}