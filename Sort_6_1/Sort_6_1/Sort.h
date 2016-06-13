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

void BubbleSort(int *a,size_t n)//ð��+�Ż�
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

void HeapSort(int *a,size_t n)	//������
{
   assert(a);
   //����  ����ѣ�
   for(int i=(n-2)/2; i>=0; i--)//�ӵ�һ����Ҷ�ӽڵ㿪ʼ   
   {
	   AdjustDown(a,n,i);
   }
   //ѡ��󻻵�ĩβ��ʣ�½������µ���
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

int GetMidIndex(int *a,int left,int right)	//����ȡ�з�
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

int PartSort(int *a,int left,int right)		  //�ڿӷ�
{
	 assert(a);
	 int key=a[GetMidIndex(a,left,right)];
	 //int key=a[left];
	 int begin=left;
	 int end=right;
	 swap(key,a[left]);
	 while(begin<end)
	 {										 //�ȱ���
		 while( begin<end && a[end]>=key)  //����������С�ڻ����key��ֵ
		 {
			 --end;
		 }
		 if(begin<end)
		 {
			 a[begin++]=a[end];
		 }
		 while(begin<end && a[begin]<key ) //���������Ҵ���key��ֵ
		 {
			 ++begin;
		 }
		 if(begin<end)
		 {
			 a[end--]=a[begin];
		 }
		 
	 } 
	 //��ʱbegin==end  Ϊkey����λ��  ����߶�����С �ұ߶�������
	 a[begin]=key;
	 return end;
}

int PartSort1(int *a,int left,int right)
{
	 assert(a);
	 int key=a[GetMidIndex(a,left,right)];
	 swap(a[GetMidIndex(a,left,right)],a[right]);//��ʱ������key����  ���ƻ�key��ֵ  keyֵӦ�ñ�������
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

void QuickSort(int *a,int left,int right)	   //�ݹ�
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

void QuickSort_NonR(int *a,int left,int right)	  //�ǵݹ� ������
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

void Merge(int *a,int *tmp,int begin1,int end1,int begin2,int end2)//�Է����Ԫ�ؽ������򡣱Ƚ�a[i]��a[j]�Ĵ�С����a[i]��a[j]���򽫵�һ��������е�Ԫ��a[i]���Ƶ�tmp[k]�У�����i��k�ֱ����1�����򽫵ڶ���������е�Ԫ��a[j]���Ƶ�tmp[k]�У�����j��k�ֱ����1�����ѭ����ȥ��ֱ������һ�������ȡ��
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

void _MergeSort(int *a,int *tmp,int left,int right)	 //���õݹ�ʵ�ȰѴ���������[left,right]���е���֣�ֱ���ֳ���������ֻʣһ��Ԫ�ء���ʱ����Ϊ��Ϊ����
{
	if(left<right)
	{
	   int mid=left+(right-left)/2;
	   _MergeSort(a,tmp,left,mid);		//[left,mid]
	   _MergeSort(a,tmp,mid+1,right); //[mid+1��right]
	   Merge(a,tmp,left,mid,mid+1,right);
	   memcpy(a+left,tmp+left,(right-left+1)*sizeof(int)); //��һ���������ʣ���Ԫ�ظ��Ƶ�tmp�д��±�left���±�right�ĵ�Ԫ��
	   /*for(int i=0; i<=right; i++)
	   {
		   a[i]=tmp[i];
	   }*/
	}
	
}

void MergeSort(int *a,int n)	 //�鲢
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

int MaxDigit(int* a, int n)	   //ͨ���������������ó���Ҫ��λ��
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

void LSDSort(int* a, int n) //��������
{
	assert(a);
	int count[10] = {0};	 //��¼����
	int start[10] = { 0 };
	int radix = 1;
	int  digit= MaxDigit(a, n);
	int *Base = new int[n];
	for (int i = 1; i <= digit; i++)
	{
		for (int i = 0; i < n; i++)
		{
			int k = (a[i] / radix) % 10;	   //�Ӹ�λ��ʼ���μ��㣬count��Ӧλ�ó��ֵĸ���
			count[k]++;
		}
		for (int j =1; j <10; j++)	  //ÿ��λ���ֵ���ʼλ��	   ���±��1��ʼ��
		{
			start[j] = start[j - 1] + count[j - 1];
		}
		for (int k = 0; k <n; k++)		  //����start����a�е����ݷ���Base��,���ź���
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

void CountSort(int *a, int n)  //��������
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
		//������count�ж�Ӧλ���Ƴ����֣��������λ���м�����ͬ����
        //�����Ƴ�1���������λ����һ����
        //�����Ƴ�2���������λ����������ͬ����
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
