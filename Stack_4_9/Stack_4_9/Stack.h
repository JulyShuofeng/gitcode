#include<iostream>
#include<cassert>
using namespace std;

template<class T>
class Stack
{
public:
	Stack()
		:_a(NULL)
		,_top(0)
		,_capacity(0)
	{}

	~Stack()
	{
		if(_a)
		{
			delete[] _a;
		}
	}

	Stack(const Stack<T>& s)
		:_top(s._top)
		,_capacity(s._capacity)
	{
		_a=new T[s._top*sizeof(T)];
		for(size_t i=0; i<s._top; i++)
		{
			_a[i]=s._a[i];
		}
	}

	Stack<T>& operator=(Stack<T>& s)
	{
		if(&s!=this)
		{
			delete[] _data;
			_data=new T[s._top*sizeof(T)];
			for(size_t i=0; i<s._top; i++)
			{
				_a[i]=s._a[i];
			}
			_top=s._top;
			_capacity=s._capacity;
		}
		return *this;
	}

	void Push(const T& d)
	{
		_CheckCapacity();
		_a[_top++]=d;
	}

	void Pop()
	{
		assert(_top>0);
		_top--;
	}

	bool Empty()
	{
		return (_top==0);
	}

	T& Top()
	{
		assert(_top>0);
		return _a[_top-1];
	}

	size_t Size()
	{
		return _top;
	}

protected:
	T* _a;
	size_t _top;
	size_t  _capacity;

	void _CheckCapacity()
	{
		if(_top==_capacity)
		{
			_capacity=2*_capacity+3;
			T* tmp=new T[_capacity];
			for(size_t i=0; i<_top; i++)
			{
				tmp[i]=_a[i];
			}
			delete[] _a;
			_a=tmp;
		}
	}
};


template<class T>
struct Node
{
	T _data;
	Node<T>* _next;
public:
	Node(const T& d)
		:_data(d)
		,_next(NULL)
	{}
};
template<class T>
class Queue
{
public:
	Queue()
		:_head(NULL)
		,_tail(NULL)
	{}

	~Queue()
	{
		if(_head==NULL)
		{
			return;
		}
		Node<T>* cur=_head;
		while(cur->_next!=NULL)
		{
			Node<T>* del=cur;
			cur=cur->_next;
			delete del;
		}
		delete cur;
	}

	Queue(const Queue<T>& q)
		:_head(NULL)
		,_tail(NULL)
	{
		Node<T>* cur=q._head;
		while(cur)
		{
			Push(cur->_data);
			cur=cur->_next;
		}
	}

	Queue<T>& operator=(Queue<T> q)
	{
		swap(_head,q._head);
		swap(_tail,q._tail);
	}

	void Push(const T &x)
	{
		Node<T>* newNode=new Node<T>(x);
		if(_head==NULL)
		{
			_head=newNode;
			_tail=_head;
		}
		else
		{
			_tail->_next=newNode;
			_tail=newNode;
		}
	}

	void Pop()
	{
		Node<T>* del=_head;
		if(_head==NULL)
		{
			return;
		}
		_head=_head->_next;
		delete del;
		del=NULL;
	}

	bool Empty()
	{
		return (_head==NULL);
	}

	size_t Size()
	{
		Node<T>* cur=_head;
		size_t count=0;
		while(cur)
		{
			count++;
			cur=cur->_next;
		}
		return count;
	}

	T& Front()
	{
		Node<T>* cur=_head;
		return cur->_data;
	}
	
	T& Back()
	{
		Node<T>* cur=_tail;
		return cur->_data;
	}
	
	void Print()		
	{
		Node<T>* cur=_head;
		while(cur)
		{
			cout<<cur->_data<<" ";
			cur=cur->_next;
		}
		cout<<endl;
	}

protected:
	Node<T>* _head;
	Node<T>* _tail;
};
