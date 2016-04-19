#include"Stack.h"

void TestStack()
{
	/*Stack<int> s1;
	Stack<int> s2=s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	cout<<s1.Size()<<endl;
	while(!s1.Empty())
	{
		cout<<s1.Top()<<" ";
		s1.Pop();
	}*/
	Stack<string> s1;
	s1.Push("aaaaa");
	s1.Push("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
	s1.Push("cccccccccccc");
	//while(!s1.Empty())
	{
		//cout<<s1.Top()<<" ";
		//s1.Pop();
	}
}

void TestQueue()
{
	Queue<int> q1;
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);
	q1.Print();
	cout<<q1.Empty()<<endl;
	cout<<q1.Size()<<endl;
	cout<<q1.Back()<<endl;
	cout<<q1.Front()<<endl;
	//Queue<int> q2=q1;
	Queue<int> q3(q1);
	q3.Print();
	/*q1.Pop();
	q1.Print();*/

}

int main()
{
	TestStack();
	//TestQueue();
	getchar();
	return 0;
}

#include<iostream>

using namespace std;

long long Fib1(size_t n)//µÝ¹é
{
	return n<2 ? n : Fib1(n-1)+Fib1(n-2);
}

long long Fib2(size_t n)//·ÇµÝ¹é£¨µü´ú£©
{
	long long f1=0;
	long long f2=1;
	long long f=0;
	if(n<2)
	{
		return n;
	}
	for(int i=2; i<=n; i++)//notice!!!(<=)
	{
		f=f1+f2;
		f1=f2;
		f2=f;
	}
	return f;
}

int main()
{
	cout<<Fib1(5)<<endl;
	cout<<Fib2(60)<<endl;
	getchar();
	return 0;
}
