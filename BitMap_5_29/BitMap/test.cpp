#include"BitMap.h"
#include"BloomFilter.h"

void Test()
{
	BitMap bm(100);
	bm.Set(1);
	bm.Set(15);
	bm.Set(64);
	bm.Set(76);
	cout<<"1?	"<<":"<<bm.Test(1)<<endl;
	cout<<"15?	"<<":"<<bm.Test(15)<<endl;
	cout<<"64?	"<<":"<<bm.Test(64)<<endl;
	cout<<"76?	"<<":"<<bm.Test(76)<<endl;
	cout<<"18?	"<<":"<<bm.Test(18)<<endl;
	bm.Reset(15);
	cout<<"15?	"<<":"<<bm.Test(15)<<endl;
}

int main()
{
	Test();
	getchar();
	return 0;
}