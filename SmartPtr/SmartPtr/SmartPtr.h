#pragma once
#include<iostream>

using namespace std;

template <class T>
class AutoPtr
{
public:
	AutoPtr(T* Ptr)
		:_Ptr(Ptr)
	{}

	~AutoPtr()
	{
		if(_Ptr!=NULL)
		{
			delete _Ptr;
		}
	}

	AutoPtr(AutoPtr<T>& ap)
	{
		_Ptr=ap._Ptr;
		ap._Ptr=NULL;
	}

	AutoPtr<T> operator=(AutoPtr<T>& ap)
	{
		if(&ap!=this)
		{
			delete _Ptr;
			_Ptr=ap._Ptr;
			ap._Ptr=NULL;
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
private:
	T* _Ptr;
};

template <class T>
class ScopedPtr
{
public:
	ScopedPtr(T* Ptr)
		:_Ptr(Ptr)
	{}

	~ScopedPtr()
	{
		if(_Ptr!=NULL)
		{
			delete _Ptr;
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
protected:
	T* _Ptr;
	ScopedPtr(ScopedPtr<T>& sp);
	ScopedPtr<T>& operator=(ScopedPtr<T>& sp);
};

template <class T>
class SharedPtr
{
public:
	SharedPtr(T* Ptr)
		:_Ptr(Ptr)
		,_Pcount(new long(1))
	{}

	~SharedPtr()
	{
		_Release();
	}

	SharedPtr(SharedPtr<T>& sp)
		:_Ptr(sp._Ptr)
		,_Pcount(sp._Pcount)
	{
		++(*_Pcount);
	}

	SharedPtr<T>& operator=(SharedPtr<T>& sp)
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
	void _Release()
	{
		if(--(*_Pcount)==0)
			{
				delete _Ptr;
				delete _Pcount;
			}
	}
};

template <class T>
class ScopedArray
{
public:
	ScopedArray(T* Ptr)
		:_Ptr(Ptr)
	{}

	~ScopedArray()
	{
		if(_Ptr!=NULL)
		{
			delete[] _Ptr;
		}
	}

	T& operator[](size_t index)
	{
		return _Ptr[index];
	}

protected:
	T* _Ptr;
	ScopedArray(const ScopedArray<T>& sa);
	ScopedArray<T>& operator=(const ScopedArray<T>& sa);
};

template <class T>
class SharedArray
{
public:
	SharedArray(T* Ptr)
		:_Ptr(Ptr)
		,_Pcount(new long(1))
	{}

	~SharedArray()
	{
		_Release();
	}

	SharedArray(SharedArray<T>& sa)
		:_Ptr(sa._Ptr)
		,_Pcount(sa._Pcount)
	{
		++(*_Pcount);
	}

	SharedArray<T>& operator=(SharedArray<T>& sa)
	{
		if(this!=&sa)
		{
			_Release();
			_Ptr=sa._Ptr;
			_Pcount=sa._Pcount;
			++(*_Pcount);
		}
	}

	T& operator[](size_t index)
	{
		return _Ptr[index];
	}

protected:
	T* _Ptr;
	long* _Pcount;
	void _Release()
	{
		if(--*(_Pcount)==0)
			{
				delete _Ptr;
				delete _Pcount;
			}
	}
};