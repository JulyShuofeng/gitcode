#include"HashTable.h"

void Test()
{

	HashTable<int,int> ht(10);
	ht.Insert(89,89);
	ht.Insert(18,18);
	ht.Insert(49,49);
	ht.Insert(58,58);
	ht.Insert(9,9);
	ht.Print();
	ht.Find(18);
	int ret=ht.Find(9)->_key;
	cout<<ret<<endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}