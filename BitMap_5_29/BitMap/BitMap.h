#pragma once
#include<iostream>
#include<vector>
using namespace std;

class BitMap
{
public:
	BitMap(size_t n)
		:_size(0)
	{
		_a.resize((n>>5)+1);
	}

	void Set(size_t x)
	{
		size_t index=x>>5;
		size_t num=x%32;
		_a[index]|=1<<num;
	}

	void Reset(size_t x)
	{
		size_t index=x>>5;
		size_t num=x%32;
		_a[index]&=~(1<<num);
	}

	bool Test(size_t x)
	{
		size_t index=x>>5;
		size_t num=x%32;
		return _a[index]&(1<<num);
	}
protected:
	vector<size_t> _a;
	size_t _size;
};