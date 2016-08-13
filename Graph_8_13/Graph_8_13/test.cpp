#include"Graph.h"

void TestMat()
{
	string a[6] = { "西安", "北京", "上海", "杭州", "珠海" };
	GraphMatrix<string, int> gr(a, 6, false);
	gr.AddEdge("西安", "北京", 1200);
 	gr.AddEdge("上海", "杭州", 500);
	gr.AddEdge("西安", "上海", 1800);
}
int main()
{
	TestMat();
	getchar();
	return 0;
}