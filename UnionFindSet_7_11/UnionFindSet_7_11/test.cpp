#include<iostream>
using namespace std;
class UnionFindSet
{
public:
	UnionFindSet(int N)
		:_a(new int[N])
		, _n(N)
	{
		memset(_a, -1, N*sizeof(int));
	}

	int FindRoot(int x)
	{
		while (_a[x]>=0)	//根为负，大于零说明不是根
		{
			x = _a[x];
		}
		return x;
	}

	void Union(int x1, int x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		_a[root1] += _a[root2];
		_a[root2] = root1;
	}

	int Count()
	{
		int count = 0;
		for (size_t i = 1; i < _n; i++)		   //从1开始，0空着
		{
			if (_a[i] < 0)
			{
				++count;
			}
		}
		return count;
	}
protected:
	int *_a;
	int _n;
};
 
int Friends(int n, int m, int r[][2])	  //小米笔试题3
{
	UnionFindSet un(n+1);	//从1开始存
	for (size_t i = 0; i < m; i++)
	{
		int x1 = r[i][0];
		int x2 = r[i][1];
		un.Union(x1, x2);
	}
	return un.Count();
}
int main()
{
	int r[][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 } };
	int ret=Friends(5, 3, r);
	cout << "朋友圈个数：" << ret << endl;
	getchar();
	return 0;
}