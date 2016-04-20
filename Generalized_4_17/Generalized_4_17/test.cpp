#include"Generalized.h"


void Test()
{
	Generalized s("(a,(c,c))");
	cout<<s.Depth()<<endl;
	s.Print();
	cout<<s.Size()<<endl;
	Generalized z(s);
	z.Print();
	Generalized w=z;
	w.Print();
}
int main()
{
	Test();
	getchar();
	return 0;
}


