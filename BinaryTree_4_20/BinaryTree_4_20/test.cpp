#include"BinaryTree.h"

void Test()
{
	int arr1[10]={1,2,3,'#','#',4,'#','#',5,6};
	int arr2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
	BinaryTree<int> t(arr2,15,'#');
	t.PrevOrder();
	//cout<<t.Depth()<<endl;
	cout<<t.Size()<<endl;
	//t.PostOrder();
	cout<<"*************" <<endl;
	/*BinaryTree<int> t1(t);
	t1.PrevOrder();
	t1.PostOrder();*/
	//t.InOrder();
	//t.LevelOrder();
	//BinaryTree<int> t2=t;
	//t2.PrevOrder();
}


int main()
{
	Test();
	getchar();
	return 0;
}