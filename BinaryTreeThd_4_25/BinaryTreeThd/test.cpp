#include"BinaryTreeThd.h"

void test()
{
  BinaryTreeThd<int> t;
  int array1 [10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
  BinaryTreeThd<int> t1(array1,10,'#');
  //t1.InOrderThreading();

}

int main()
{
	test();
	//getchar();
	return 0;
}