#pragma once
#include<iostream>
#include<vector>

using namespace std;

template<class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T *a,size_t size)
		:_a(new T[size*(size+1)/2])
		,_size(size*(size+1)/2)
		,_n(size)
	{
		size_t index=0;
		for(size_t i=0; i<_n; i++)
		{
			for(size_t j=0; j<_n; j++)
			{
				if(i>=j)
				{
					_a[index++]=a[i*size+j];
				}
				else
				{
					break;
				}
			}
		}
	}

	~SymmetricMatrix()
	{
		if(_a)
		{
			delete[] _a;
			_a=NULL;
			_size=0;
		}
	}

	void Display()
	{
		for(size_t i=0; i<_n; i++)
		{
			for(size_t j=0; j<_n; j++)
			{
				if(i>=j)
				{
					 cout<<_a[i*(i+1)/2+j]<<" ";
				}
				else
				{
					cout<<_a[j*(j+1)/2+i]<<" ";
				}
			}
			cout<<endl;
		}
	}

protected:			  
	 T * _a;
	 size_t _size;
	 size_t _n;
};


template<class T>
struct Triple	//三元组
{
	 T _value;
	 size_t _row;
	 size_t _col;
	 Triple(const T& value=T(),size_t row=0,size_t col=0)
		 :_value(value)
		 ,_row(row)
		 ,_col(col)
	 {}
};

template<class T>
class SparseMatrix
{
public:
	SparseMatrix(T* a,size_t m,size_t n,const T& invalid)
		:_rowsize(m)
		,_colsize(n)
		,_invalid(invalid)
	{
		for(size_t i=0; i<m; i++)
		{
			for(size_t j=0; j<n; j++)
			{
				if(a[i*n+j]!=invalid)
				{
					_a.push_back(Triple<T>(a[i*n+j],i,j));
				}
			}
		}
	}

	 SparseMatrix()
        :_rowsize(0)
        ,_colsize(0)
    {}

	void Display()
	{
		size_t index=0;
		for(size_t i=0; i<_rowsize; i++)
		{
			for(size_t j=0; j<_colsize; j++)
			{
				if(index<_a.size() && _a[index]._row==i && _a[index]._col==j)
				{
					cout<<_a[index]._value<<" ";
					index++;
				}
				else
				{
					cout<<_invalid<<" ";
				}
			}
			cout<<endl;
		}
	}

	SparseMatrix<T> Transport()
	{
		SparseMatrix<T> tmp;
		tmp._colsize=_rowsize;
		tmp._rowsize=_colsize;
		tmp._invalid=_invalid;
		for(size_t i=0; i<_colsize; i++)   //遍历每一列
		{
			size_t index=0;
			while(index<_a.size()) //遍历原始三元组
			{
				
				 if(_a[index]._col==i)	//若两者相等
				 {		 
					Triple<T> t( _a[index]._value,_a[index]._col, _a[index]._row);
                    tmp._a.push_back(t);;//存入新的三元组
					/*Triple<T> tp;
                    tp._col = _a[index]._row;
                    tp._row = _a[index]._col;
                    tp._value = _a[index]._value;
                    tmp._a.push_back(tp);*/
                }
				 index++;
			}
		}
		return tmp;
	}

	 SparseMatrix<T> FastTransport()
	 {
		 SparseMatrix<T> tmp;
		 tmp._colsize=_rowsize;
		 tmp._rowsize=_colsize;
		 tmp._invalid=_invalid;
		 int *rowcounts=new int[tmp._rowsize];//每一列中非零元素的个数
		 int *rowstart=new int[tmp._rowsize];//每一列第一个非零元素在三元组中的位置
		 memset(rowcounts,0,(sizeof(int)* _colsize));//初始化
		 memset(rowstart,0,(sizeof(int)* _colsize));

		 size_t index=0;
		 while(index<_a.size())
		 {						   
			 rowcounts[_a[index]._col]++; //遍历将每一列的非零元素个数存入rowcounts
			 ++index;
		 }
		 rowstart[0]=0;
		 for(size_t i=1; i<_colsize; i++)
		 {
			 rowstart[i]=rowstart[i-1]+rowcounts[i-1];	//将每一列非零元素的起始位置存入rowsart
		 }
		 index=0;
		 tmp._a.resize(_a.size());
		 while(index<_a.size())
		 {
			 size_t rowIndex=_a[index]._col;
			 int &start=rowstart[rowIndex];
			 Triple<T> tp;
             tp._col = _a[index]._row;
             tp._row = _a[index]._col;
             tp._value = _a[index]._value;
             tmp._a[start++]=tp;	 
			 index++;
		 }
		 return tmp;
	 }
protected:
	vector<Triple<T> > _a;
	size_t _rowsize;
	size_t _colsize;
	T _invalid;
};