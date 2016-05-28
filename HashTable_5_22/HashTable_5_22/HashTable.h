#pragma once
#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;

enum State
{
	 EMPTY,
	 DELETE,
	 EXITS,
};

template<class K,class V>
struct HashTableNode
{
	K _key;
	V _value;
	HashTableNode(const K& key=K(),const V& value=V())
		:_key(key)
		,_value(value)
	{}
};

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)		 //基本类型
	{
		return key;
	}
};
static size_t  Hashstr(const char * str)//字符串哈希算法
{
    unsigned int seed = 131; // 31 131 1313 13131 131313
    unsigned int hash = 0;
    while (*str)
    {
        hash = hash * seed + (unsigned int)(*str++);
    }
    return (hash & 0x7FFFFFFF);
}
template<>
struct HashFunc<string>
{
	size_t operator()(const string& str)
	{
		return 	Hashstr(str.c_str());
	}
};

template <class K,class V,class HF=HashFunc<K> >
class HashTable
{
	typedef   HashTableNode<K,V> Node;
public:
	HashTable(size_t capacity=10)
		:_tables(new Node[capacity])
		,_states(new State[capacity])
		,_capacity(capacity)
	{
		for(size_t i=0; i<_capacity; i++)
		{
			_states[i]=EMPTY;
		}
	}

	HashTable(const HashTable<K,V> &ht)	//拷贝构造
		:_tables(NULL)
		,_states(NULL)
		,_size(0)
		,_capacity(0)
	{
		HashTable<K,V> tmp(ht._capacity);
		for(size_t i=0; i<ht._states[i]; i++)
		{
			if(ht._states[i]==EXITS)
			{
				tmp.Insert(ht._tables[i]);	
			}
		}
		this->Swap(tmp);
	}

	~HashTable()
	{
		if(_tables)
		{
			delete []_tables;
			delete []_states;
			_size=0;
			_capacity=0;
		}
	}

	void Swap(HashTable<K,V> &ht)	 //交换
	{
		swap(ht._tables,this->_tables);
		swap(ht._states,this->_states);
		swap(ht._size,this->_size);
		swap(ht._capacity,this->_capacity);
	}

	bool Insert(const K& key,const V& value)	//插入
	{
		_CheckCapacity();
		size_t index=_HashFunc(key);	 //哈希函数
		size_t i=0;
		while(_states[index]==EXITS)
		{
			if(_tables[index]._key==key && _tables[index]._value==value)   //防止冗余
			{
			   return false;
			}
			index =_HashFunc(key)+i*i;
			index%=_capacity;
			++i;
			/*if(index>=_capacity)
			{
				index=index-_capacity;
			}*/
		}
		 _tables[index]._key=key;
		 _tables[index]._value=value;
		 _states[index]=EXITS;
		 _size++;
		 return true;
	}

	Node* Find(const K& key)
	{
		 size_t index=_HashFunc(key);
		 size_t i=0;
		 while(_states[index]!=EMPTY)
		 {
			 if(_tables[index]._key==key)
			 {
				 if(_states[index]!=DELETE)
				 {
					 return &(_tables[index]);	  //why
				 }
				 else
				 {
					 return NULL;
				 }
			 }
				  index=_HashFunc(key)+i*i;
				  index%=_capacity;
				  ++i;
		 }
		 return NULL;
	}

	void Print()
	{
	    for (size_t i = 0; i < _capacity; ++i)
		{
			cout<<i<<":";
			if(_states[i]==EXITS)
			{
				cout<<_tables[i]._key<<"-"<<_tables[i]._value<<"		";
			}
			else
			{
				cout<<"NULL"<<"	";
			}
		}
		cout<<endl;
	}
		
	
protected:
	Node *_tables;	  //哈希表
	size_t _size;	  //元素个数
	size_t _capacity;//容量
	State *_states;	//状态表

protected:

	size_t _HashFunc(const K& key) 
	{
		HF ht;
		return ht(key)%_capacity;
	   // return index+(2*i-1);
	}

	void _CheckCapacity()
	{
		if(_size*10/_capacity==7)
		{
		   HashTable<K,V> tmp(2*_capacity);
		   for(size_t i=0; i<_capacity; i++)
		   {
			   if(_states[i]==EXITS)
			   {
				   tmp.Insert(_tables[i]._key,_tables[i]._value);
			   }
		   }
		   this->Swap(tmp);
		}
	}

};										
