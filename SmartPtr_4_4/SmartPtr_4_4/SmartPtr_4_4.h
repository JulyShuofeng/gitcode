#pragma once
#include<iostream>

using namespace std;

template <class T,class D>
class SharedPtr
{
public:
	SharedPtr(T* Ptr)
		:_Ptr(Ptr)
		,_Pcount(new long(1))
	{}

	SharedPtr(T* Ptr,D del)
		:_Ptr(Ptr)
		,_Pcount(new long(1))
		,_del(del)
	{}

	~SharedPtr()
	{
		_Release();
	}

	SharedPtr(SharedPtr<T,D>& sp)
		:_Ptr(sp._Ptr)
		,_Pcount(sp._Pcount)
	{
		++(*_Pcount);
	}

	SharedPtr<T,D>& operator=(SharedPtr<T,D>& sp)
	{
		if(&sp!=this)
		{
			_Release();
		    _Ptr=sp._Ptr;
		    _Pcount=sp._Pcount;
		    ++(*_Pcount);
		}	
	}

	T& operator*()
	{
		return *_Ptr;
	}

	T* operator->()
	{
		return _Ptr;
	}

	long UseCount()
	{
		return *_Pcount;
	}

	T* GetPtr()
	{
		return _Ptr;
	}

protected:
	T* _Ptr;
	long *_Pcount;
	D _del;

	void _Release()
	{
		if(--(*_Pcount)==0)
			{
				_del(_Ptr);
				delete _Pcount;
			}
	}
};

template<class T>
struct DefaultDel
{
	void operator()(T* ptr)
	{
		delete ptr;
	}
};

template<class T>
struct Free
{
	void operator()(T* ptr)
	{
		free(ptr);
	}
};

template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr)
		:_Ptr(ptr)
		,_owner(true)
	{}

	~AutoPtr()
	{
		if(_owner)
		{
			delete _Ptr;
		}
	}

	AutoPtr(AutoPtr<T>& ap)
		:_Ptr(ap._Ptr)
		,_owner(ap._owner)
	{
		ap._owner=false;
	}
	
	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		if(&ap!=this)
		{
			_Ptr=ap._Ptr;
			_owner=ap._owner;
			ap._owner=false;
		}
		return *this;
	}

	T& operator*()
	{
		return *_Ptr;
	}

	T* operator->()
	{
		return _Ptr;
	}

protected:
	T* _Ptr;
	bool _owner;
};
