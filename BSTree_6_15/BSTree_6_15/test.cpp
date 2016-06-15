#include"BSTree.h"

void Test1()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int, int> bst;
	for (int i = 0; i < (sizeof(a) / sizeof(a[0])); ++i)
	{
		bst.Insert(a[i], i);
	}
	bst.Inorder();
	//cout << bst.Find(10)->_key << endl;
	cout << "------------------------------------------" << endl;
	cout<<bst.Remove(8)<<endl;
	bst.Inorder();
}

void Test2()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int, int> bst;
	for (int i = 0; i < (sizeof(a) / sizeof(a[0])); ++i)
	{
		bst.InsertR(a[i], i);
	}
	bst.Inorder();
	cout << bst.FindR(0)->_key << endl;
	cout << bst.RemoveR(3) << endl;
}


int main()
{
	//Test1();	 
	Test2();
	getchar();
	
	return 0;
}