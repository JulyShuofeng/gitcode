#include"Sort.h"

int check()
{
	union UN
	{
		int i;
		char c;
	}un;
	un.i=1;
	return (un.c==1);
}
int main()
{
	//TestBubbleSort();
	////TestInsertSort();
	////TestShelltSort();
	//TestSeclectSort();
	//cout<<check();
	//TestHeapSort();
	//TestQuickSort();
	TestMergeSort();
	getchar();
	 return 0;
}