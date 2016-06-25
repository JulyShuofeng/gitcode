#include"AVLTree.h"

void Test()
{
	AVLTree<int, int> avlt;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
    //int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	//int a[] = { 5, 3, 4,1,7,8 };
	for (int i = 0; i <sizeof(a)/sizeof(a[0]); ++i)
	{
		avlt.Insert(a[i], i);
	}
	avlt.InoderTree();
	cout << avlt.IsBalance() << endl;
	
}

int main()
{
	Test();
	getchar();
	return 0;
}