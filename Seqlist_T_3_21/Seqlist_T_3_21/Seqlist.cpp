#include<iostream>
#include<cassert>
#include<string>
#include<stdlib.h>

using namespace std;

template<typename T>

class Seqlist
{
private:
	T* _data;
	int _size;
	int _capacity;
public:
	void _CheckCapacity()
	{
		if(_size==_capacity)
		{
			T* tmp=new T[2*_capacity+4];
	      //memcpy(tmp,_data,_size*sizeof(T));
			for(int i=0; i<_size; i++)
			{
					tmp[i]=_data[i];
			}
			delete[] _data;
			_data=tmp;
			_capacity=2*_capacity+3;
		}
	}

public:
	Seqlist()
		:_data(NULL)
		,_size(0)
		,_capacity(0)
	{}

	~Seqlist()
	{
		if(_data!=NULL)
		{
			delete[] _data;
		}
	}


	/*Seqlist(const Seqlist& s)
		:_size(s._size)
		,_capacity(s._capacity)
	{
		_data=new T[_capacity];
		memcpy(_data,s._data,_size*sizeof(T));
	}*/

	/*Seqlist operator=(const Seqlist& s)
	{
		if(this!=&s)
		{
			delete[] _data;
			_data=new T[s._capacity];
			memcpy(_data,s._data,s._size*sizeof(T));
			
			_size=s._size;
			_capacity=s._capacity;
		}
		return *this;
	}
*/
	void Print()
	{
		int i=0;
		for(i=0; i<_size; i++)
		{
			cout<<_data[i]<<' ';
		}
		cout<<endl;
	}

	void PushBack(const T& t);
	void PushFront(const T& t);
	void PopBack();
	void PopFront();
	void Insert(int pos,const T& t);
	void Sort();

};

template<typename T>
void Seqlist<T>::PushBack(const T& t)
{
	_CheckCapacity();
	_data[_size]=t;
	_size++;
}

template<typename T>
void Seqlist<T>::PushFront(const T& t)
{
	_CheckCapacity();
	int start=_size-1;
	while(start>=0)
	{
		_data[start+1]=_data[start];
		start--;
	}
	_data[0]=t;
	_size++;
}

template<typename T>
void Seqlist<T>::PopBack()
{
	if(_data==NULL)
	{
		return;
	}
	_data[_size--];
}

template<typename T>
void Seqlist<T>::PopFront()
{
	if(_data==NULL)
	{
		return;
	}
	int i=0;
	for(i=0; i<_size; i++)
	{
		_data[i]=_data[i+1];
	}
	_size--;
}

template<typename T>
void Seqlist<T>::Insert(int pos,const T& t)
{
	assert(0<=pos && pos<_size);
	_CheckCapacity();
	int i=0;
	for(i=_size; i>pos; i--)
	{
		_data[i]=_data[i-1];
	}
	_data[pos]=t;
	_size++;
}

template<typename T>
void Seqlist<T>::Sort()
{
	int i=0;
	int j=0;
	for(i=0; i<_size-1; i++)
	{
		for(j=0; j<_size-i-1; j++)
		{
			if(_data[j]>_data[j+1])
			{
				swap(_data[j],_data[j+1]);
			}
		}
	}

}

//void Test1()
//{
//	Seqlist<string> s1;
//	s1.PushBack("ce");
//	s1.PushBack("w");
//    s1.PushBack("ww");
//    s1.PushBack("dd");
//    s1.PushBack("dd");
//	s1.Print();
//	//cout<<sizeof(s1)<<endl;
//	//s1.PopBack();
//	//s1.PopFront();
//	//s1.Sort();
//	//.Print();
//	//s1.Print();
//}
//
//void Test2()
//{
//	Seqlist<double> s2;
//	s2.PushFront(1.3);
//	s2.PushFront(2.7);
//	s2.PushFront(3.00);
//	s2.PushFront(4.3);
//	s2.Print();
//	
//	
//	
//	/*s3.PushBack(2);
//	s3.PushBack(1);
//	s3.PushBack(9);
//	s3.PushBack(7);
//	s3.Print();*/
//	
//	////s2.PopBack();
//	//s2.PopFront();
//	//s2.Print();
//}
//
////void Test3()
////{
////	Seqlist<int> s3;
////	s3.PushBack(2);
////	s3.PushBack(1);
////	s3.PushBack(9);
////	s3.PushBack(7);
////	s3.Print();
////	//s3.PopFront();
////	//s3.Insert(2,8);
////	s3.Sort();
////	s3.Print();
////
////}

template <class T, template <class> class Container = Seqlist > 
class Stack
{
public:
	void Push_Back(const T& d)
	{
		con.PushBack(d);
	}

	void Pop_Back()
	{
		con.PopBack();
	}

	void Push_Front(const T& d)
	{
		con.PushFront(d);
	}

	void Pop_Front()
	{
		con.PopFront(d);
	}

private:
	Container<T> con;
};


void Test()
{
	Stack<int> s;
	s.Push_Back(1);
	s.Push_Back(2);
	s.Push_Back(3);

}

int main()
{
	Test();
	getchar();
	return 0;
}

//int main()
//{
//	//Test1();
//	/*Seqlist<string> s1;
//	s1.PushBack("ceyyyylllllllllllllllllllllllllllllllllllllllllllllllllll");
//	s1.PushBack("w");
//	s1.PushBack("a");
//	s1.PushBack("dd");
//	s1.Print();*/
//	//cout<<sizeof(string);
//	//string s1("12345");
//	string s2("123456789123456789");
//	printf("%p\n",&s2);
//	//string s2(s1);
//	//printf("%p\n",s1.c_str());
//	//printf("%p\n",s2.c_str());
//	system("pause");
//	//getchar();
//	return 0;
//}