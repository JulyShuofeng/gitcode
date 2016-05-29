#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class K,class V>
struct HashTableNode
{
	K _key;
	V _value;
	HashTableNode<K,V> *_next;
	HashTableNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_next(NULL)
	{}
};

template<class K,class V>
class HashTableBucket
{
	typedef HashTableNode<K,V> Node;
public:
	HashTableBucket()
		:_size(0)
	{}
	HashTableBucket(size_t capacity)
		:_size(0)
	{
		_tables.resize(_GetNextPrime(_capacity));
	}

	HashTableBucket(const HashTableBucket& ht)
		:_size(0)
	{
		_tables.resize(ht._tables.size());
		for(size_t i=0; i<ht._tables.size(); i++)
		{
			Node* cur =ht._tables[i];
			while(cur)
			{
				Insert(cur->_key,cur->_value);
				cur=cur->_next;
			}
		}
	}

	 HashTableBucket& operator=(const HashTableBucket& ht)
	 {
		 if(this!=&ht)
		 {
			 HashTableBucket tmp(ht);
			 _tables.swap(tmp._tables);
			 _tables.swap(tmp._size);
		 }
		 return *this;

	 }

	~HashTableBucket()
	{
		for(size_t i=0; i<_tables.size(); i++)
		{
			Node* cur=_tables[i];
			while(cur)
			{
				Node* del=cur;
				cur=cur->_next;
				delete del;
				_tables[i]=NULL;
			}
		}
	}

	bool Insert(const K& key,const V& value)
	{
		_CheckExpand();
		size_t index=_HashFunc(key,_tables.size());
		Node* cur=_tables[index];
		while(cur)	 //查是否存在，防止冗余
		{
			if(cur->_key==key)
			{
				return false;
			}
			cur=cur->_next;
		}
		Node* tmp=new Node(key,value);
		tmp->_next=_tables[index];
		_tables[index]=tmp;
		return true;
	}

	Node* Find(const K& key)
	{
		size_t index=_HashFunc(key,_tables.size());
		Node* cur=_tables[index];
		while(cur)
		{
			if(cur->_key==key)
			{
				return cur;
			}
			cur=cur->_next;
		}
		return NULL;
	}

	bool Remove(const K& key)
	{
		size_t index=_HashFunc(key,_tables.size());
		Node* cur=_tables[index];
		if(cur==NULL)
		{
			return false;
		}
		if(cur->_key==key)
		{
			_tables[index]=cur->_next;
			delete cur;
			return true;
		}
		Node* prev=cur;	 //记住前一个结点
		cur=cur->_next;;
		while(cur)
		{
			if(cur->_key==key)
			{
				prev->_next=cur->_next;		//连接到下一个
				delete	cur;
				return true;
			}
			prev=cur;
			cur=cur->_next;
		}
		return false;
	}

	void PrintTables()
	{
		for(size_t i=0; i<_tables.size(); i++)
		{
			Node* cur=_tables[i];
			while(cur)
			{

				cout<<"["<<cur->_key<<"-"<<cur->_value<<"]"<<"	";
				cur=cur->_next;
			}
		
		}
		cout<<endl;
	}
protected:
	size_t _HashFunc(const K& key,const size_t size)
	{
		 return key%size;
	}

	size_t _GetNextPrime(size_t size)
	{
		// 使用素数表对齐做哈希表的容量，降低哈希冲突

     const int _PrimeSize = 28;

     static const unsigned long _PrimeList [_PrimeSize] =

    {

        53ul,         97ul,         193ul,       389ul,       769ul,

        1543ul,       3079ul,       6151ul,      12289ul,     24593ul,

        49157ul,      98317ul,      196613ul,    393241ul,    786433ul,

        1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,

        50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,

        1610612741ul, 3221225473ul, 4294967291ul

    };
	 for(size_t i=0; i<_PrimeSize; ++i)
	 {
		 if(_PrimeList[i]>size)
		 {
			 return _PrimeList[i];
		 }
	 }
	 return _PrimeList[_PrimeSize-1];
	}

	void _CheckExpand()
	{
		if(_size==_tables.size())
		{
			size_t newcapacity=_GetNextPrime(_size);
			vector<Node*> newtables;
			newtables.resize(newcapacity);
			for(size_t i=0; i<_tables.size(); ++i)
			{
				Node* cur=_tables[i];
				while(cur)
				{
					Node* tmp=cur;	 //头插结点
					cur=cur->_next;
					size_t index=_HashFunc(tmp->_key,newtables.size());
					tmp->_next=newtables[index];
					newtables[index]=tmp;
				}
				_tables[i]=NULL;
			}
			_tables.swap(newtables);
		}
	}
protected:
	vector<Node*> _tables;
	size_t _size;  //略显鸡肋
};
