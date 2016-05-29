#include"HashTableBucket.h"

void Test1()
{
	HashTableBucket<int,int> ht1;
	ht1.Insert(1,1);
	ht1.Insert(2,2);
	ht1.Insert(3,3);
	ht1.Insert(4,4);
	ht1.PrintTables();
	cout<<ht1.Find(1)->_key<<endl;
	ht1.Remove(2);
	ht1.PrintTables();

}

void Test2()
{
	HashTableBucket<int,char> ht2;
	ht2.Insert(1,'a');
	ht2.Insert(2,'b');
	ht2.Insert(3,'c');
	ht2.Insert(4,'d');
	ht2.PrintTables();
	HashTableBucket<int,char> ht3(ht2);
	ht3.PrintTables();
	HashTableBucket<int,char> ht4=ht2;
	ht4.PrintTables();
}

int main()
{
	//Test1();
	Test2();
	getchar();
	return 0;
}

