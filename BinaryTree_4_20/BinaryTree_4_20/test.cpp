#include"BinaryTree.h"

void Test()
{
	int arr1[10]={1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int> t(arr1,10,'#');
	t.PrevOrder();
	t.InOrder();
	t.PostOrder();
	t.LevelOrder();
}


int main()
{
	Test();
	getchar();
	return 0;
}