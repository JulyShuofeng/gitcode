#pragma once
#include<iostream>
#include<vector>

using namespace std;
template <class T>
class Heap
{
public:
	Heap()
	{}

	Heap(const T* a,size_t size)
	{
		for(size_t i=0; i<size; i++)
		{
			_a.push_back(a[i]);
		}
		//����
		for(int i=(_a.size()-2)/2; i>=0; --i)
		{
		    _AdjustDown(i);
		}
		
	}

protected:
	void AdjustDown(size_t parent)
	{
		//ָ������
		size_t child=parent*2-1;
		while(child<_a.size())
		{
			if(_a[child]<_a[child+1])//ѡ����������һ��
			{
				++child;
			}
			if(_a[child]>_a[parent])
			{
				swap(_a[child],_a[parent]);
				parent=child;
				child=parent*2+1;
			}
			else  //�������
			{
			   break;
			}
		}
	}
protected:
	vector<T> _a;

};