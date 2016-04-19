#include"SmartPtr.h"

void TestAutoPtr()
{
	AutoPtr<int> ap1(new int(1));
	//AutoPtr<int> ap2(ap1);
	//AutoPtr<int> ap3=ap1;
	cout<<*ap1<<endl;
}

void TestScopedPtr()
{
	//ScopedPtr<int> sp1(new int(2));
	//ScopedPtr<int> sp2(sp1);
	struct A
	{
		int _a;
	};
	ScopedPtr<A> sp2(new A());
	sp2->_a=10;
	cout<<(sp2->_a)<<endl;
}

void TestSharedPtr()
{
	SharedPtr<int> sp1(new int(6));
	SharedPtr<int>  sp2(sp1);
}

void TestScopedArray()
{
	ScopedArray<int> sa1(new int[10]);
	//sa1[0]=0;
	int i=0;
	for(i=0; i<10; i++)
	{
		sa1[i]=i;
		cout<<sa1[i]<<' ';
	}
}

void TestSharedArray()
{
	SharedArray<int> sa2(new int[5]);
	SharedArray<int> sa3(sa2);
	int i=0;
	/*for(i=0; i<10; i++)
	{
		sa3[i]=i;
		cout<<sa3[i]<<' ';
	}*/
}

int main()
{
	//TestAutoPtr();
	//TestScopedPtr();
	//TestScopedArray();
	TestSharedArray();
	getchar();
	return 0;
}