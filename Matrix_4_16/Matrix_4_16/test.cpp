#include"Matrix.h"	 

void SymmetricTest()
{
	int a[5][5]=
	{
		{0,1,1,1,1},
		{1,0,1,1,1},
		{1,1,0,1,1},
		{1,1,1,0,1},
		{1,1,1,1,0}
	} ;
	SymmetricMatrix<int> m((int*)a,5);
	m.Display();
}

void SparseTest()
{
	int a[5][5]=
	{
		{1,0,3,0,0},
		{0,2,0,4,0},
		{0,0,0,5,0},
		{6,0,0,0,7},
		{0,0,0,0,0}
	};
	SparseMatrix<int> sm((int*)a,5,5,0)	;
	sm.Display();
	cout<<"****************************"  <<endl;
	//sm.Transport().Display();
	SparseMatrix<int> s=sm.FastTransport();
	s.Display();

}

int main()
{	
	//SymmetricTest();
	SparseTest();
	getchar();
	return 0;
}