#include<iostream>
#include<string>

using namespace std;

template<typename T>
struct Node
{
	Node<T>* _next;
	Node<T>* _prev;
	T _data;
public:
	Node(const T& d)
		:_data(d)
		,_next(NULL)
		,_prev(NULL)
	{}
};

template<typename T>
class Dlist
{
public:
	Dlist()
		:_head(NULL)
		,_tail(NULL)
	{}

	~Dlist()
	{
		Node<T>* cur=_head;
		while(cur)
		{
			Node<T>* del=cur;
			cur=cur->_next;
			delete del;
		}
	}

	Dlist(const Dlist& l)
		:_head(NULL)
		,_tail(NULL)
	{
		Node<T>* cur=l._head;
		while(cur)
		{
			Dlist<T>::PushBack(cur->_data);
			cur=cur->_next;
		}
	}

	void PushBack(const T& d);
	void PushFront(const T& d);
	void PopBack();
	void PopFront();
	Node<T>* Find(const T& d);
	void Insert(Node<T>* pos,const T& d);
	void Sort();
	void Reverse();
	void Remove(const T& d);
	void Erase(Node<T>* pos);
	void Print();

private:
	Node<T>* _head;
	Node<T>* _tail;
};

template<typename T>
void Dlist<T>::Print()
{
	Node<T>* cur=_head;
	while(cur)
	{
		cout<<cur->_data<<"<=>";
		cur=cur->_next;
	}
	cout<<"over"<<endl;;
}

template<typename T>
void Dlist<T>::PushBack(const T& d)
{
	Node<T>* newNode=new Node<T>(d);
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

template<typename T>
void Dlist<T>::PushFront(const T& d)
{
	Node<T>* newNode=new Node<T>(d);
	if(_head==NULL)
	{
		_head=newNode;
		_tail=_head;
	}
	else 
	{
		newNode->_next=_head;
		_head->_prev=newNode;
		_head=newNode;
		_head->_prev=NULL;
	}

}

template<typename T>
void Dlist<T>::PopBack()
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

template<typename T>
void Dlist<T>::PopFront()
{
	if(_head==NULL)
	{
		return;
	}
	else
	{
		_head=_head->_next;
		delete _head->_prev;
		_head->_prev=NULL;
	}
}

template<typename T>
Node<T>* Dlist<T>::Find(const T& d)
{
	Node<T>* cur=_head;
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

template<typename T>
void Dlist<T>::Insert(Node<T>* pos,const T& d)
{
	Node<T>* newNode=new Node<T>(d);
	if(pos==NULL)
	{
		return;
	}
	else if(pos==_tail)
	{
		Dlist<T>::PushBack(d);
	}
	else if(pos==_head)
	{
		Dlist<T>::PushFront(d);
	}
	else	
	{
		newNode->_next=pos->_next;
		newNode->_prev=pos;
		pos->_next=newNode;
		pos->_next->_prev=newNode;
	}

}

template<typename T>
void Dlist<T>::Sort()
{
	Node<T>* cur=_head;
	Node<T>* end=NULL;
	while(cur!=end)
	{
		while(cur!=NULL && cur->_next!=end)
		{
			if(cur->_data>cur->_next->_data)
			{
				swap(cur->_data,cur->_next->_data);
			}
			cur=cur->_next;
		}
		end=cur;
		cur=_head;
	}
}

template<typename T>
void Dlist<T>::Reverse()
{
	if(_head==NULL || _head==_tail)
	{
		return;
	}
	else
	{
		Node<T>* cur=_head;
		while(cur)
		{
			swap(cur->_next,cur->_prev);
			cur=cur->_prev;
		}
		swap(_head,_tail);
	}
}

template<typename T>
void Dlist<T>::Remove(const T& d)//with 3 points
{
	Node<T>* cur=_head;
	Node<T>* del=NULL;
	Node<T>* prev=_head;
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
				cur->_next->_prev=prev;
			}
		delete del;
		break;
		}
	prev=cur;
	cur=cur->_next;
	}	
}

template<typename T>
void Dlist<T>::Erase(Node<T>* pos)
{
	if(pos==NULL)
	{
		return;
	}
	else
	{
		Node<T>* cur=_head;
		Node<T>* del=NULL;
		Node<T>* prev=NULL;
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
					cur->_next->_prev=prev;
				}
				delete del;
				break;
			}
			prev=cur;
			cur-cur->_next;
		}
	}
}

void Test1()
{
	/*Dlist<int> L1;
	L1.PushBack(1);
	L1.PushBack(2);
	L1.PushBack(3);
	L1.PushBack(4);
	L1.Print();*/
	//L1.PopFront();
	//L1.Print();
	Dlist<int> L2;
	L2.PushFront(1);
	L2.PushFront(2);
	L2.PushFront(3);
	L2.PushFront(4);
	L2.Print();
	////L2.PopBack();
	////L2.Sort();
	//L2.Reverse();
	//L2.Print();
}

void Test2()
{
	Dlist<string> L3;
	L3.PushBack("abcdh");
	L3.PushBack("ef");
	L3.PushBack("h");
	L3.PushBack("ig");
	L3.PushBack("k");
	L3.Print();
	//L3.Remove("h");
	L3.Insert(L3.Find("h"),"sb");
	L3.Print();
	//L3.Erase(L3.Find(1));
	//L3.Print();
}

void Test3()
{
	Dlist<string> str;
	str.PushFront("aaaa");
	str.PushFront("bbbb");
	str.PushFront("cccc");
	str.PushFront("dddd");
	str.Print();
	str.Sort();
	str.Print();
}

int main()
{
	Test1();
	getchar();
	return 0;
}
