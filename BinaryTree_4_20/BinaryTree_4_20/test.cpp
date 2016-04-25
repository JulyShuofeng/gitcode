#include"BinaryTree.h"

void Test()
{
	int arr1[10]={1,2,3,'#','#',4,'#','#',5,6};
	int arr2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
	BinaryTree<int> t(arr1,10,'#');
	//t.PrevOrder();
	//t.Prev_Order();
	//t.In_Order();
	//t.Level_Order();
	//cout<<t.Depth()<<endl;
	//cout<<t.Size()<<endl;
	//t.PostOrder();
	cout<<"*************" <<endl;
	//BinaryTree<int> t1(t);
	//t1.PrevOrder();
	t.PostOrder();
	t.Post_Order();
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