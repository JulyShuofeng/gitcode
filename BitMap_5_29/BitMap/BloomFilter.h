#pragma once
#include<iostream>
#include"BitMap.h"
using namespace std;

static size_t BKDRHash(const char *str)  
{  
    register size_t hash = 0;  
    while (size_t ch = (size_t)*str++)  
    {         
        hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..  
        // 有人说将乘法分解为位运算及加减法可以提高效率，如将上式表达为：hash = hash << 7 + hash << 1 + hash + ch;  
        // 但其实在Intel平台上，CPU内部对二者的处理效率都是差不多的，  
        // 我分别进行了100亿次的上述两种运算，发现二者时间差距基本为0（如果是Debug版，分解成位运算后的耗时还要高1/3）；  
        // 在ARM这类RISC系统上没有测试过，由于ARM内部使用Booth's Algorithm来模拟32位整数乘法运算，它的效率与乘数有关：  
        // 当乘数8-31位都为1或0时，需要1个时钟周期  
        // 当乘数16-31位都为1或0时，需要2个时钟周期  
        // 当乘数24-31位都为1或0时，需要3个时钟周期  
        // 否则，需要4个时钟周期  
        // 因此，虽然我没有实际测试，但是我依然认为二者效率上差别不大          
    }  
    return hash;  
}  
struct _HashFunc1
{
	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
};
  


static size_t SDBMHash(const char*str)  
{  
    register size_t hash = 0;  
    while (size_t ch = (size_t)*str++)  
    {  
        hash = 65599 * hash + ch;         
        //hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
    }  
    return hash;  
}  
struct _HashFunc2
{
	size_t operator()(const string& key)
	{
		return 	SDBMHash(key.c_str());
	}
};
 


static size_t RSHash(const char *str)  
{  
    register size_t hash = 0;  
    size_t magic = 63689;     
    while (size_t ch = (size_t)*str++)  
    {  
        hash = hash * magic + ch;  
        magic *= 378551;  
    }  
    return hash;  
}  
struct _HashFunc3
{
	size_t operator()(const string& key)
	{
		return 	RSHash(key.c_str());
	}
};
 


static size_t APHash(const char *str)  
{      register size_t hash = 0;  
    size_t ch;  
    for (long i = 0; ch = (size_t)*str++; i++)  
    {  
        if ((i & 1) == 0)  
        {  
            hash ^= ((hash << 7) ^ ch ^ (hash >> 3));  
        }  
        else  
        {  
            hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));  
        }  
    }      return hash;  
}  
struct _HashFunc4
{
	size_t operator()(const string& key)
	{
		return APHash(key.c_str()); 
	}
};
  

 static size_t JSHash(const char *str)  
{  
    if(!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
        return 0;  
    register size_t hash = 1315423911;  
    while (size_t ch = (size_t)*str++)  
    {  
        hash ^= ((hash << 5) + ch + (hash >> 2));  
    }      return hash;  
}  

struct _HashFunc5
{
	size_t operator()(const string& key)
	{
		return  JSHash(key.c_str());
	}
};
  
 


template<class K=string>
class BloomFilter
{
public:

	BloomFilter(size_t n)
		:_bm(_GetNextPrime(n))
		,_capacity(_GetNextPrime(n))
	{}

	void Set(const K& key)
	{
		size_t HashFunc1=_HashFunc1()(key);
		size_t HashFunc2=_HashFunc2()(key);
		//size_t HashFunc3=_HashFunc5()(key);
		size_t HashFunc4=_HashFunc4()(key);
		size_t HashFunc5=_HashFunc5()(key);
		_bm.Set(HashFunc1%_capacity);
		_bm.Set(HashFunc2%_capacity);
		//_bm.Set(HashFunc3%_capacity);
		_bm.Set(HashFunc4%_capacity);
		_bm.Set(HashFunc5%_capacity);
	}

	bool Test(const K& key)
	{
		size_t hash1=_HashFunc1()(key);
		if(!_bm.Test(hash1%_capacity))
		{
			return false;
		}
		size_t hash2=_HashFunc2()(key);
		if(!_bm.Test(hash2%_capacity))
		{
			return false;
		}
		//size_t hash3=_HashFunc3()(key);
		/*if(!_bm.Test(hash3%_capacity))
		{
			return false;
		}*/
		size_t hash4=_HashFunc4()(key);
		if(!_bm.Test(hash4%_capacity))
		{
			return false;
		}
		size_t hash5=_HashFunc5()(key);
		if(!_bm.Test(hash5%_capacity))
		{
			return false;
		}
		return true;
	}
protected:
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

protected:
	BitMap _bm;
	size_t _capacity;
};