#include<iostream>
#include<stack>
#include<cassert>

using namespace std;

enum Type
{
	OP_NUM,
	OP_SYMBOL,
};

enum SYMBOL
{
	ADD,
	SUB,
	MUL,
	DIV,
};

struct Cell
{
	Type _type;
	int _value;
};

int CountRNP(Cell *a,size_t size)
{
	assert(a);
	stack<int> s;
	for(size_t i=0; i<size; i++)
	{
		if(a[i]._type==OP_NUM)
		{
			s.push(a[i]._value);
		}
		else
		{
			int right=s.top();
			s.pop();
			int left=s.top();
			s.pop();
			switch(a[i]._value)
			{
			case ADD:
				s.push(left+right);
				break;
			case SUB:
				s.push(left-right);
				break;
			case MUL:
				s.push(left*right);
				break;
			case DIV:
				s.push(left/right);
				break;
			}
		}
	}
	return s.top();
}

