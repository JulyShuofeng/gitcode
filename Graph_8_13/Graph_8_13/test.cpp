#include"Graph.h"

void TestMat()
{
	string a[6] = { "����", "����", "�Ϻ�", "����", "�麣" };
	GraphMatrix<string, int> gr(a, 6, false);
	gr.AddEdge("����", "����", 1200);
 	gr.AddEdge("�Ϻ�", "����", 500);
	gr.AddEdge("����", "�Ϻ�", 1800);
}
int main()
{
	TestMat();
	getchar();
	return 0;
}