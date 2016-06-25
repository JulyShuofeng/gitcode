
#include"FileCompress.h"
#include<windows.h>

void TestFileCompress()
{
	FileCompress fc;
	int begin1 = GetTickCount();
	fc.Compress("Input.BIG");
	int end1 = GetTickCount();
	cout << "压缩用时：" << end1 - begin1 << "ms"<<endl;
	int begin2 = GetTickCount();
	fc.Uncompress("Input.BIG");
	int end2 = GetTickCount();
	cout << "解压用时：" << end2 - begin2 << "ms" << endl;
}

void Test()
{
	FileCompress fc;
	fc.Compress("hello");
	fc.Uncompress("hello");
}
void TestHuffmanTree()
{
	int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	HuffmanTree<int> t(a, sizeof(a) / sizeof(a[0]), -1);

}

int main()
{
	//TestHuffmanTree();
	TestFileCompress();

	//Test();
	getchar();
	return 0;
}