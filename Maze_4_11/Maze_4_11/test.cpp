#include"Maze.h"

void TestMaze()
{
	int a[N][N]={};
	GetMaze((int*)a,N);
	PrintMaze((int*)a,N);
	stack<Pos> path;
	Pos entry={2,0};
	int ret=MazePath((int*)a,N,entry,path);
	cout<<"是否找到出口"<<ret<<endl;
	PrintMaze((int*)a,N);
}

int main()
{
	TestMaze();
	getchar();
	return 0;
}