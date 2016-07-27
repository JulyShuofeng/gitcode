#include"BTree.h"

void Test()
{
	BTree<int> bt;
	int arr[] = { 53, 75, 139, 49, 145, 36, 101 };
	for (size_t i = 0; i <7; ++i)
	{
		bt.Insert(arr[i]);
	}
	bt.Inorder();
}
int main()
{
	Test();
	getchar();
	return 0;
}