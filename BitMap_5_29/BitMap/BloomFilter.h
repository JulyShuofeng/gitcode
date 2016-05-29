#pragma once
#include<iostream>
#include"BitMap.h"
using namespace std;

template<class K=string>
class BloomFilter
{
public:

	BloomFilter(size_t n)
		:_bm
	{}
	void Set(const K& key)
	{
		size_t HashFunc1=_HashFunc1(key);
		size_t HashFunc2=_HashFunc2(key);
		size_t HashFunc3=_HashFunc5(key);
		size_t HashFunc4=_HashFunc4(key);
		size_t HashFunc5=_HashFunc5(key);

	}


protected:
	BitMap _bm;
	size_t _capacity;
};