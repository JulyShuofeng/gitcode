#include"BinaryTreeThd.h"

void test()
{
  BinaryTreeThd<int> t;
  int array1[10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
  BinaryTreeThd<int> t1(array1,10,'#');
  t1.InOrderThreading();
  t1.InOrderThd();

   BinaryTreeThd<int> t2(array1,10,'#');
   t2.PrevThreading();
   t2.PrevThd();
}

int main()
{
	test();
	getchar();
	return 0;
}