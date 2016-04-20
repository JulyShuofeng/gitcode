#include"test.h"

void Test()
{
	SeqList myseq;
	InitSeqList(&myseq);
	PrintSeqList(myseq);
	PushBack(&myseq,1);
	PushBack(&myseq,2);
	PushBack(&myseq,3);
	PopBack(&myseq);
}

int main()
{
	Test();
	system("pause");
	return 0;
}