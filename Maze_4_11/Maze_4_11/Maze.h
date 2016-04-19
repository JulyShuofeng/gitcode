#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#define N  10
#include<iostream>
#include<stack>
#include<cassert>
using namespace std;

struct Pos	 //��ͨ���±����λ��
{
	int _ROW;
	int _COL;
};

void GetMaze(int *a,int n)	//���ļ��ж����Թ���ͼ
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

bool CheckIsAccess(int *a,int n,Pos next)//����Ƿ�Ϊͨ·
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

bool MazePath(int *a,int n,Pos& entry,stack<Pos>& path)	   //̽������
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
		//�ж����������Ƿ�Ϊͨ· 
		next=cur;
		next._ROW--;// ��
		if(CheckIsAccess(a,n,next))
		{	
			cur=next;
			path.push(cur);
			continue;
		}
		next=cur;
		next._ROW++;//��
		if(CheckIsAccess(a,n,next))
		{
			cur=next;
			path.push(cur);
			continue;
		}
		next=cur;
		next._COL--;//��
		if(CheckIsAccess(a,n,next))
		{
			cur=next;
			path.push(cur);
			continue;
		}
		next=cur;
		next._COL++;//��
		if(CheckIsAccess(a,n,next))
		{
			cur=next;
			path.push(cur);
			continue;
		}
		//����
		cur=path.top();
		path.pop();
		
	}					   
}



void PrintMaze(int *a,int n)   //����Թ�
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