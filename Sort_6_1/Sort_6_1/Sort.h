#pragma once
#include<iostream>
#include<cassert>
using namespace std;

void Print(int *a,size_t n)
{
	for(size_t i=0; i<n; i++)
	{
		cout<<a[i]<<"	 ";
	}
	cout<<endl;
}

void BubbleSort(int *a,size_t n)//ð��+�Ż�
{
	assert(a);
	int end=n-1;
	while(end>0)
	{
		bool exchange=false;
		for(size_t i=0; i<end; i++)
		{
			if(a[i]>a[i+1])
			{	
				exchange=true;
				if(exchange==true)
				{
				  swap(a[i],a[i+1]);
				}					
			}
		}
		--end;
	}
}

void TestBubbleSort()
{
	int a[]={2,5,4,9,3,6,8,7,1,0};
	Print(a,10);
	BubbleSort(a,10);
	Print(a,10);
}

void InsertSort(int *a,size_t n) //��������
{
   assert(a);
   for(size_t i=0; i<n-1; i++) 
   {
	   int end=i;
	   int tmp=a[end+1];
	   while(end>=0 && a[end]>tmp)
	   {
		   a[end+1]=a[end];
		   --end;
	   }
	   a[end+1]=tmp;
   }
}

void TestInsertSort()
{
	int a[]={2,5,4,9,3,6,8,7,1,0};
	Print(a,10);
	InsertSort(a,10);
	Print(a,10);
}

void ShellSort(int *a,size_t n)	 //ϣ������
{
	assert(a);
	size_t gap=n;
	while(gap>1)
	{
		gap=gap/3+1;
		for(size_t i=0; i<n-gap; i++) //���Ϊgap�Ĳ���
		{
			size_t end=i;
			int tmp=a[end+gap];
			while(end>=0 && tmp<a[end])
			{
			   a[end+gap]=a[end];
			   end-=gap;
			}
			a[end+gap]=tmp;
		}
	}
}

void TestShelltSort()
{
	int a[]={2,5,4,9,3,6,8,7,1,0};
	Print(a,10);
	ShellSort(a,10);
	Print(a,10);
}

void SeclectSort1(int *a,size_t n)	 //ѡ������
{
	assert(a);
	for(size_t end=n-1; end>0; --end)
	{	
		size_t maxindex=0;	//ÿ�δ�0��ʼ��
		for(size_t i=1; i<=end; ++i)
		{
			if(a[i]>a[maxindex])
			{
				maxindex=i;
			}
		}
		swap(a[maxindex],a[end]);
	}
}

void  SeclectSort(int *a,size_t n)	 //�Ż��汾
{
	assert(a);
	size_t left=0;
	size_t right=n-1;
	while(left<right)
	{
		size_t maxindex=left; //ͬʱ�ҳ��������С
		size_t minindex=left;
		for(size_t i=left+1; i<=right; ++i)
		{
			if(a[i]>a[maxindex])
			{
				maxindex=i;
			}
			if(a[i]<a[minindex])
			{
				minindex=i;
			}
		}
		swap(a[left],a[minindex]);
		if(maxindex==left)	//����maxindexλ�÷�ֹ��ͻ
		{
		   maxindex=minindex;
		}
		swap(a[right],a[maxindex]);
		left++;
		right--;
	}
}

void TestSeclectSort()
{
	int a[]={9,5,4,2,3,6,8,7,1,0};
	Print(a,10);
	SeclectSort(a,10);
	Print(a,10);
}

void HeapSort(int *a,size_t n)
{

}
