#include"BigData.h"
void TestData()
{
	
	BigData bd1("999999999999999999999");
	//                    9223372036854775808
	//BigData bd1(-9223372036854775807);
	cout << bd1;
	BigData bd2(-3);
	cout << bd2;
	cout << bd1/bd2 << endl;
	
}

int main()
{
	TestData();
	getchar();
	return 0;
}