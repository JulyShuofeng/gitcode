#pragma once
#include<iostream>
#include<string>

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
struct _HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};
template<>
struct _HashFunc<string>
{
	size_t operator()(const string& str)
	{
		return 	_HashFunc(str.c_str());
	}
};

template <class K,class V,class HashFunc=_HashFunc<K>>
class HashTable
{
	typedef   HashTableNode<K,V> Node;
public:
	HashTable(size_t capcity=10)
		:_tables(new Node[capcity])
		,_states(new States[capcity])
		,_capcity(capcity)
	{
		for(size_t i=0; i<_capcity; i++)
		{
			_states[i]=EMPTY;
		}
	}

	~HashTable()
	{
		if(_states!=EXITS)
		{
			delete []_tables;
			delete []_states;
		}
	}

	bool Insert(const K& key,const V& value)
	{

	}

	Node* Find(const K& key)
	{

	}

	size_t _HashFunc(const char *str) //×Ö·û´®¹þÏ£Ëã·¨
	{
		unsigned int seed = 131; // 31 131 1313 13131 131313
        unsigned int hash = 0;
		while(*str)
		{
			hash = hash * seed + (unsigned int)(*str++);
		}
		 return (hash & 0x7FFFFFFF);
	}
protected:
	Node *_tables;	  //¹þÏ£±í
	size_t _size;	  //ÔªËØ¸öÊý
	size_t _capcity;//ÈÝÁ¿
	State *_states;	//×´Ì¬±í

};
