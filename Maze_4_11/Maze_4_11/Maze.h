#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#define N  10
#include<iostream>
#include<stack>
#include<cassert>
using namespace std;

struct Pos	 //可通过下标访问位置
{
	int _ROW;
	int _COL;
};

void GetMaze(int *a,int n)	//从文件中读出迷宫地图
{
	FILE* fout=fopen("Maze.txt","r");
	assert(fout);
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; 
			)
		{
			char ch=fgetc(fout);
			if(ch=='0' || ch=='1')
			{
				a[i*n+j]=ch-'0';
				++j;
			}
			else
			{
				   continue;
			}
		}
	}
	fclose(fout);
}

bool CheckIsAccess(int *a,int n,Pos next)//检查是否为通路
{
	assert(a);
	if( (next._ROW>=0) && (next._ROW<n) && (next._COL>=0) && (next._COL<n) && (a[next._ROW*n+next._COL]==0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MazePath(int *a,int n,Pos& entry,stack<Pos>& path)	   //探索过程
{
	Pos cur=entry;
	path.push(cur);
	while(!path.empty())
	{
		Pos next=cur;
		a[cur._ROW*n+cur._COL]=2;
		
		if(next._ROW==n-1) /*|| next._ROW==0 || next._COL==n-1 ||  next._COL==0*/
		{
			return true;
		}
		//判断上下左右是否为通路 
		next=cur;
		next._ROW--;// 上
		if(CheckIsAccess(a,n,next))
		{	
			cur=next;
			path.push(cur);
			continue;
		}
		next=cur;
		next._ROW++;//下
		if(CheckIsAccess(a,n,next))
		{
			cur=next;
			path.push(cur);
			continue;
		}
		next=cur;
		next._COL--;//左
		if(CheckIsAccess(a,n,next))
		{
			cur=next;
			path.push(cur);
			continue;
		}
		next=cur;
		next._COL++;//右
		if(CheckIsAccess(a,n,next))
		{
			cur=next;
			path.push(cur);
			continue;
		}
		//回退
		cur=path.top();
		path.pop();
		
	}					   
}



void PrintMaze(int *a,int n)   //输出迷宫
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
		    cout<<a[i*n+j]<<" ";
		}
		cout<<endl;
	}	
}