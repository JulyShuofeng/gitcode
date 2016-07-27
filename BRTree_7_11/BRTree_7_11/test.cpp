#include"RBTree.h"
#include<stdlib.h>
void Test()
{
	RBTree<int, int> rbt;
	int a[] = { 5, 2, 9, 6, 7, 3, 4, 0, 1, 8 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		rbt.Insert(a[i], i);
	}
	rbt.Inorder();
	cout<<rbt.CheckRBTree()<<endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}