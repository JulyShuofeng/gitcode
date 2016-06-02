#pragma once
#include<iostream>
#include"BitMap.h"
using namespace std;

static size_t BKDRHash(const char *str)  
{  
    register size_t hash = 0;  
    while (size_t ch = (size_t)*str++)  
    {         
        hash = hash * 131 + ch;   // Ҳ���Գ���31��131��1313��13131��131313..  
        // ����˵���˷��ֽ�Ϊλ���㼰�Ӽ����������Ч�ʣ��罫��ʽ���Ϊ��hash = hash << 7 + hash << 1 + hash + ch;  
        // ����ʵ��Intelƽ̨�ϣ�CPU�ڲ��Զ��ߵĴ���Ч�ʶ��ǲ��ģ�  
        // �ҷֱ������100�ڴε������������㣬���ֶ���ʱ�������Ϊ0�������Debug�棬�ֽ��λ�����ĺ�ʱ��Ҫ��1/3����  
        // ��ARM����RISCϵͳ��û�в��Թ�������ARM�ڲ�ʹ��Booth's Algorithm��ģ��32λ�����˷����㣬����Ч��������йأ�  
        // ������8-31λ��Ϊ1��0ʱ����Ҫ1��ʱ������  
        // ������16-31λ��Ϊ1��0ʱ����Ҫ2��ʱ������  
        // ������24-31λ��Ϊ1��0ʱ����Ҫ3��ʱ������  
        // ������Ҫ4��ʱ������  
        // ��ˣ���Ȼ��û��ʵ�ʲ��ԣ���������Ȼ��Ϊ����Ч���ϲ�𲻴�          
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
    if(!*str)        // �����ɱ�����ӣ��Ա�֤���ַ������ع�ϣֵ0  
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
		// ʹ���������������ϣ������������͹�ϣ��ͻ

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