#include"Stack_app.h" 

void TestRNP()
{
	Cell a[]={{OP_NUM,12},{OP_NUM,3},{OP_NUM,4},{OP_SYMBOL,ADD},{OP_SYMBOL,MUL},{OP_NUM,6},{OP_SYMBOL,SUB},{OP_NUM,8},{OP_NUM,2},{OP_SYMBOL,DIV},{OP_SYMBOL,ADD}};
	int ret=CountRNP(a,sizeof(a)/sizeof(Cell));
	cout<<"result="<<ret<<endl;
}

int main()
{
	TestRNP();
	getchar();
	return 0;
}