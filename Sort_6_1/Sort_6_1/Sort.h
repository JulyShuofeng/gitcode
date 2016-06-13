#pragma once
#include<iostream>
#include<stack>
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

void BubbleSort(int *a,size_t n)//冒泡+优化
{
	assert(a);
	int end=n-1;
	while(end>0)
	{
		bool exchange=false;
		for(int i=0; i<end; i++)
		{
			if(a[i]>a[i+1])
			{	
				swap(a[i],a[i+1]);
				exchange=true;
			}
		}
		if(exchange==false)
		{
			break;
		}
		--end;
	}
}

void TestBubbleSort()
{
	int a[]={0,1,2,3,4,5,6,7,9,8};
	Print(a,10);
	BubbleSort(a,10);
	Print(a,10);
}

void InsertSort(int *a,size_t n) //插入排序
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

void ShellSort(int *a,size_t n)	 //希尔排序
{
	assert(a);
	size_t gap=n;
	while(gap>1)
	{
		gap=gap/3+1;
		for(size_t i=0; i<n-gap; i++) //间距为gap的插入
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

void SeclectSort1(int *a,size_t n)	 //选择排序
{
	assert(a);
	for(size_t end=n-1; end>0; --end)
	{	
		size_t maxindex=0;	//每次从0开始比
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

void  SeclectSort(int *a,size_t n)	 //优化版本
{
	assert(a);
	size_t left=0;
	size_t right=n-1;
	while(left<right)
	{
		size_t maxindex=left; //同时找出最大与最小
		size_t minindex=left;
		for(int i=left+1; i<=right; ++i)
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
		if(maxindex==left)	//修正maxindex位置防止冲突
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

void AdjustDown(int *a,size_t n,size_t parent)
{
	size_t child=parent*2+1;
	while(child<n)
	{
	   if(child+1<n && a[child]<a[child+1])
	   {
		   ++child;
	   }
	   if(a[child]>a[parent])
	   {
		   swap(a[child],a[parent]);
		   parent=child;
		   child=parent*2+1;
	   }
	   else
	   {
		   break;
	   }
	}
}

void HeapSort(int *a,size_t n)	//堆排序
{
   assert(a);
   //建堆  （大堆）
   for(int i=(n-2)/2; i>=0; i--)//从第一个非叶子节点开始   
   {
	   AdjustDown(a,n,i);
   }
   //选最大换到末尾，剩下进行向下调整
   for(int i=0; i<n; i++)
   {
	   swap(a[0],a[n-i-1]);
	   AdjustDown(a,n-i-1,0);
   }
}

void TestHeapSort()
{
	int a[]={9,5,4,2,3,6,8,7,1,0};
	Print(a,10);
	HeapSort(a,10);
	Print(a,10);
}

int GetMidIndex(int *a,int left,int right)	//三数取中法
{
	int mid=left+(right-left)/2;
	if(a[left]<a[mid])
	{
		if(a[mid]<a[right])
		{
			return mid;
		}
		else if(a[left]<a[right])
		{
			return right;
		}
		else
		{
			return left;
		}
	}
	else
	{
		if(a[mid]<a[right])
		{
			return mid;
		}
		else if(a[left]>a[right])
		{
		   return 	left;
		}
		else
		{
			return right;
		}
	}
}

int PartSort(int *a,int left,int right)		  //挖坑法
{
	 assert(a);
	 int key=a[GetMidIndex(a,left,right)];
	 //int key=a[left];
	 int begin=left;
	 int end=right;
	 swap(key,a[left]);
	 while(begin<end)
	 {										 //先比右
		 while( begin<end && a[end]>=key)  //从右向左找小于或等于key的值
		 {
			 --end;
		 }
		 if(begin<end)
		 {
			 a[begin++]=a[end];
		 }
		 while(begin<end && a[begin]<key ) //从左向右找大于key的值
		 {
			 ++begin;
		 }
		 if(begin<end)
		 {
			 a[end--]=a[begin];
		 }
		 
	 } 
	 //此时begin==end  为key合适位置  其左边都比它小 右边都比它大
	 a[begin]=key;
	 return end;
}

int PartSort1(int *a,int left,int right)
{
	 assert(a);
	 int key=a[GetMidIndex(a,left,right)];
	 swap(a[GetMidIndex(a,left,right)],a[right]);//此时不可与key交换  会破坏key的值  key值应该保存下来
	 int begin=left;
	 int end=right-1;
	 while(end>begin)
	 {  
		 while(end>begin && a[begin]<=key)
		 {
			 ++begin;
		 }
		/* if(end>begin)
		 {
			 swap(a[begin],a[end]);
		 }*/
		 while(end>begin && a[end]>=key)
		 {
			 --end;
		 }
		 if(end>begin)
		 {
			 swap(a[begin],a[end]);
		 }
	 }
	 if(a[begin]>a[right])
	 {
		 swap(a[begin],a[right]);
		 return begin;
	 }
	 else
	 {
		 return right;
	 }
}

int PartSort2(int *a,int left,int right)
{
	 assert(a);
	 int key=a[GetMidIndex(a,left,right)];
	 swap(a[right],a[GetMidIndex(a,left,right)]);
	 int prev=left-1;
	 int cur=left;
	 while(cur<right)
	 {
		if(a[cur]<key && ++prev!=cur)
		{
			swap(a[cur],a[prev]);
		}
		++cur;
	 }
	 swap(a[++prev],a[right]);
	 return prev;
}

void QuickSort(int *a,int left,int right)	   //递归
{
	assert(a);
	if(left<right)
	{
		if(right-left<13)
		{
			InsertSort(a+left,right-left+1);
			return;
		}
		int div=PartSort2(a,left,right);
		QuickSort(a,left,div-1);
		QuickSort(a,div+1,right);
	}  
}

void QuickSort_NonR(int *a,int left,int right)	  //非递归 又问题
{
     stack<int> s;
	 s.push(left);
	 s.push(right);
	 while(!s.empty())
	 {
		 int end=s.top();
		 s.pop();
		 int begin=s.top();
		 int div=PartSort2(a,begin,end);
		 if(begin<div-1)
		 {
			 s.push(begin);
			 s.push(div-1);
		 }
		 if(div+1<end)
		 {
			 s.push(div+1);
			 s.push(end);
		 }
	 }
}
	
void TestQuickSort()
{
	int a[]={9,5,4,3,8,6,2,7,1,0};
	Print(a,10);
	QuickSort(a,0,9);
	//QuickSort_NonR(a,0,9);
	//quick_sort(a,0,9);
	Print(a,10);
}

void Merge(int *a,int *tmp,int begin1,int end1,int begin2,int end2)//对分组的元素进行排序。比较a[i]和a[j]的大小，若a[i]≤a[j]，则将第一个有序表中的元素a[i]复制到tmp[k]中，并令i和k分别加上1；否则将第二个有序表中的元素a[j]复制到tmp[k]中，并令j和k分别加上1，如此循环下去，直到其中一个有序表取完
{
   int index=begin1;
   while(begin1<=end1 && begin2<=end2 )
   {
	   if(a[begin1]<=a[begin2])
	   {
		   tmp[index++]=a[begin1++];
	   }
	   else
	   {
		   tmp[index++]=a[begin2++];
	   }
   }
   while(begin1<=end1)
   {
	   tmp[index++]=a[begin1++];
   }
   while(begin2<=end2)
   {
	   tmp[index++]=a[begin2++];
   }
}

void _MergeSort(int *a,int *tmp,int left,int right)	 //利用递归实先把待排序区间[left,right]以中点二分，直到分出来的数组只剩一个元素。此时可认为其为有序。
{
	if(left<right)
	{
	   int mid=left+(right-left)/2;
	   _MergeSort(a,tmp,left,mid);		//[left,mid]
	   _MergeSort(a,tmp,mid+1,right); //[mid+1，right]
	   Merge(a,tmp,left,mid,mid+1,right);
	   memcpy(a+left,tmp+left,(right-left+1)*sizeof(int)); //另一个有序表中剩余的元素复制到tmp中从下标left到下标right的单元。
	   /*for(int i=0; i<=right; i++)
	   {
		   a[i]=tmp[i];
	   }*/
	}
	
}

void MergeSort(int *a,int n)	 //归并
{
	assert(a);
	int *tmp=new int[n];
	_MergeSort(a,tmp,0,n-1);
	delete[] tmp;
}

void TestMergeSort()
{
   int a[]={6,5,4,3,8,9,2,7,1,0};
   Print(a,10);
   MergeSort(a,10);
   Print(a,10);
}

int MaxDigit(int* a, int n)	   //通过数组中最大的数得出需要的位数
{
	int max =10;
	int digit = 1;
	for (int i = 0; i < n; i++)
	{
		while (a[i]>max)
		{
			digit++;
			max *= 10;
		}
	}
	return digit;
}

void LSDSort(int* a, int n) //基数排序
{
	assert(a);
	int count[10] = {0};	 //记录次数
	int start[10] = { 0 };
	int radix = 1;
	int  digit= MaxDigit(a, n);
	int *Base = new int[n];
	for (int i = 1; i <= digit; i++)
	{
		for (int i = 0; i < n; i++)
		{
			int k = (a[i] / radix) % 10;	   //从个位开始依次计算，count对应位置出现的个数
			count[k]++;
		}
		for (int j =1; j <10; j++)	  //每个位出现的起始位置	   （下标从1开始）
		{
			start[j] = start[j - 1] + count[j - 1];
		}
		for (int k = 0; k <n; k++)		  //根据start，将a中的数据放在Base中,已排好序
		{
			int num=( a[k] / radix)%10;
			Base[start[num]++] = a[k];
		}
		for (int i = 0; i < n; i++)
		{
			a[i] = Base[i];
		}
		radix = radix * 10;
	}
	delete[] Base;
}

void TestLSDSort()
{
	int a[] = { 9, 5, 4, 3, 8, 6, 2, 7, 1, 0 };
	Print(a, 10);
	LSDSort(a, 10);
	Print(a, 10);
}

void CountSort(int *a, int n)  //计数排序
{
	assert(a);
	int max = a[0];
	int min = a[0];
	for (int i = 0; i < n; i++)
	{
		if (a[i] < min)
		{
			min = a[i];
		}
		if (a[i]>max)
		{
			max = a[i];
		}
	}
	int range = max - min + 1;
	int *count = new int[range];
	memset(count, 0, sizeof(int)*range);
	for (int i = 0; i < n; i++)
	{
		count[a[i] - min]++;
		//把数组count中对应位置制成数字，代表这个位置有几个相同的数
        //列如制成1，代表这个位置有一个数
        //列如制成2，代表这个位置有两个相同的数
	}
	int j = 0;
	for (int i = 0; i < range; i++)
	{
		while (count[i]>0)
		{
			a[j++] = i + min;
			count[i]--;
		}
	}
	delete[] count;
}

void TestCountSort()
{
	int a[] = { 9, 5, 4, 3, 8, 6, 2, 7, 1, 0 };
	Print(a, 10);
	CountSort(a, 10);
	Print(a, 10);
}
