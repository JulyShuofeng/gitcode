#include"SmartPtr_4_4.h"

void TestSharedPtr()
{
	SharedPtr<int,DefaultDel<int> > sp1(new int(1));
	SharedPtr<int,Free<int> > sp2((int*)malloc(sizeof(int)));
}

void TestAutoPtr()
{
	AutoPtr<int> ap1(new int(1));
	AutoPtr<int> ap2(ap1);
	AutoPtr<int> ap3=ap2;
}

int main()
{
	//TestSharedPtr();
	TestAutoPtr();
	getchar();
	return 0;
}