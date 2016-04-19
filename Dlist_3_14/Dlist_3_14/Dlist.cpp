#include"Dlist.h"

void Dlist::PushBack(const DataType& d)
{
	Node* newNode=new Node(d);
	if(_head==NULL)
	{
		_head=newNode;
		_tail=_head;
	}
	else
	{
		_tail->_next=newNode;
		newNode->_prev=_tail;
		_tail=newNode;
	}
}

 void Dlist::PopBack()
	{
		if(_head==NULL)
		{
			return;
		}
		else if(_head==_tail)
		{
			delete _head;
			_head=NULL;
			_tail=NULL;
		}
		else
		{
			_tail=_tail->_prev;
			delete _tail->_next;
			_tail->_next=NULL;
		}
	}

	void Dlist::PushFront(const DataType& d)
	{
		Node* newNode=new Node(d);
		if(_head==NULL)
		{
			_head=newNode;
			_tail=_head;
		}
		else
		{
			newNode->_next=_head;
			_head=newNode;
			_head->_prev=NULL;
		}
	}

	void Dlist::PopFront()
	{
		Node* del=_head;
		if(_head==NULL)
		{
			return;
		}
		else
		{
			_head=_head->_next;
			delete del;
			del=NULL;
			_head->_prev=NULL;
		}
	}

	Node* Dlist::Find(const DataType& d)
	{
		Node* cur=_head;
		while(cur)
		{
			if(cur->_data==d)
			{
				return cur;
			}
			cur=cur->_next;
		}
		return NULL;
	}

	void Dlist::Insert(Node* pos,const DataType& d)
	{
		Node* newNode=new Node(d);
		if(pos==NULL)
		{
			return;
		}
		if(pos==_tail)
		{
			_tail->_next=newNode;
			_tail=newNode;
		}
		else
		{
			newNode->_next=pos->_next;
			newNode->_prev=pos;
			pos->_next=newNode;
		}
	}

	void Dlist::Sort()
	{
		Node* cur=_head;
		Node* end=NULL;
		while(cur!=end)
		{
			while(cur && cur->_next!=end)
			{
				if(cur->_data < cur->_next->_data)
				{
					DataType tmp=cur->_data;
					cur->_data=cur->_next->_data;
					cur->_next->_data=tmp;
				}
				cur=cur->_next;
			}
			end=cur;
			cur=_head;
		}
	}

	void Dlist::Reverse()
	{
		Node* cur=_head;
		Node* prev=NULL;
		Node* newHead=NULL;
		if(_head==NULL || _head==_tail)
		{
			return;
		}
		while(cur)
		{
			prev=cur;
			cur=cur->_next;
			prev->_next=newHead;
			newHead=prev;
			prev->_prev=cur;	
		}
		_head=newHead;
	}

	void Dlist::Remove(const DataType& d)
	{
		Node* del=NULL;
		Node* cur=_head;
		Node* prev=NULL;
		while(cur)
		{
			if(cur->_data==d)
			{
				del=cur;
				if(cur==_head)
				{
					_head=_head->_next;
					_head->_prev=NULL;
				}
				else
				{
					prev->_next=cur->_next;
				}
				delete del;
				break;
			}
			prev=cur;
			cur=cur->_next;
		}
	}

	void Dlist::Erase(Node* pos)
	{
		if(pos==NULL)
		{
			return;
		}
		Node* cur=_head;
		Node* del=NULL;
		Node* prev=NULL;
		while(cur)
		{
			if(cur==pos)
			{
				del=cur;
				if(cur==_head)
				{
					_head=_head->_next;
					_head->_prev=NULL;
				}
				else
				{
					prev->_next=cur->_next;
				}
				delete del;
				break;
			}
			prev=cur;
			cur=cur->_next;
		}
	}

	void Test1()
	{
		Dlist l1;
		l1.PushBack(1);
		l1.PushBack(2);
		l1.PushBack(3);
		l1.PushBack(4);
		cout<<l1;
		//l1.PopBack();
		//l1.Sort();
		l1.Reverse();
		cout<<l1;
	}

	void Test2()
	{
		Dlist l2;
		l2.PushFront(1);
		l2.PushFront(2);
		l2.PushFront(3);
		l2.PushFront(4);
		//cout<<l2;
		//l2.PopFront();
		//l2.Insert(l2.Find(1),8);
		//l2.Sort();
		cout<<l2;
		//l2.Remove(4);
		l2.Erase(l2.Find(3));
		cout<<l2;
	}

int main()
{
	Test2();
	getchar();
	return 0;
}