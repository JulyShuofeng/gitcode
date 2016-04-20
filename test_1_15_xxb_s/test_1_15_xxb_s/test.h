#ifndef __TEST_H__
#define __TEST_H__

#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#define MAX 10
typedef int DataType;
typedef struct SeqList
{
	DataType arr[MAX];
	int size;
}SeqList, *pSeqList;

void InitSeqList(pSeqList pSeq);
void PrintSeqList(SeqList Seq);
void PushBack(pSeqList pSeq, DataType x);
void PopBack(pSeqList pSeq);
void PushFront(pSeqList pSeq, DataType x);
void PopFront(pSeqList pSeq);
void Insert(pSeqList pSeq, int pos, DataType x);
void Remove(pSeqList pSeq, DataType x);
void RemoveAll(pSeqList pSeq, DataType x);
int Find(pSeqList pSeq, DataType x);
void ReverseList(pSeqList pSeq);
void SortList(pSeqList pSeq);
DataType BinarySearch(pSeqList pSeq, DataType x);

void InitSeqList(pSeqList pSeq)
{
	memset(pSeq->arr,0,MAX);
	pSeq->size++;
}

void PrintSeqList(SeqList Seq)
{
	int i=0;
	for(i=0; i<Seq.size; i++)
	{
		printf("%d ",Seq.arr);
	}
	printf("over\n");
}

void PushBack(pSeqList pSeq, DataType x)
{
	if(pSeq->size>=MAX)
	{
		printf("The table is full!\n");
		return;
	}
	pSeq->arr[pSeq->size++]=x;
}

void PopBack(pSeqList pSeq)
{
	if(pSeq->size==0)
	{
		printf("The table is null!\n");
		return;
	}
	pSeq->size--;
}

void PushFront(pSeqList pSeq, DataType x)
{
	int i=0;
	if(pSeq->size>=MAX)
	{
		printf("The table is full!\n");
		return;
	}
	for(i=pSeq->size; i>0; i--)
	{
		pSeq->arr[i]=pSeq->arr[i-1];
	}
	pSeq->arr[0]=x;
	pSeq->size++;
}

void PopFront(pSeqList pSeq)
{
	int i=0;
	if(pSeq->size==0)
	{
		printf("The table is null!\n");
		return;
	}
	for(i=0; i<pSeq->size-1; i++)
	{
		pSeq->arr[i]=pSeq->arr[i+1];
	}
}

int Find(pSeqList pSeq, DataType x)
{
	int i=0;
	assert(pSeq);
	for(i=0; i<pSeq->size; i++)
	{
		if(x==pSeq->arr[i])
		{
			return i;
		}
		return -1;
	}
}

void Insert(pSeqList pSeq, int pos, DataType x)
{
	int i=0;
	assert(pSeq);
	assert((pos>=0) && (pos<=pSeq->size-1));
	if(pSeq->size>=MAX)
	{
		printf("The table is full!\n");
		return;
	}
	for(i=pSeq->size; i>pos; i--)
	{
		pSeq->arr[i]=pSeq->arr[i-1];
	}
	pSeq->arr[pos]=x;
	pSeq->size++;
}

void Remove(pSeqList pSeq, DataType x)
{
	int i=0;
	int pos=Find(pSeq,x);
	assert(pSeq);
	if(pos!=-1)
	{
		for(i=pos; i<pSeq->size; i++)
		{
			pSeq->arr[i]=pSeq->arr[i+1];
		}
		pSeq->size++;
	}
}

void RemoveAll(pSeqList pSeq, DataType x)
{
	int i=0;
	int j=0;
	int pos=Find(pSeq,x);
	if(pos!=-1)
	for(i=pos; i<pSeq->size; i++)
	{
		for(j=pos; j<pSeq->size; j++)
		{
			pSeq->arr[j]=pSeq->arr[j+1];
		}
		pSeq->size++;
	}
}

void ReverseList(pSeqList pSeq)
{
	int front=0;
	int back=pSeq->size-1;
	DataType tmp=0;
	assert(pSeq);
	while(back>front)
	{
		tmp=front;
		front=back;
		back=tmp;
		front++;
		back++;
	}
}

void SortList(pSeqList pSeq)
{
	int i=0;
	int j=0;
	DataType tmp=0;
	for(i=0; i<pSeq->size-1; i++)
	{
		for(j=0; j<pSeq->size-1-i; j++)
		{
			tmp=pSeq->arr[j];
			pSeq->arr[j]=pSeq->arr[j+1];
			pSeq->arr[j+1]=tmp;
		}
	}
}

DataType BinarySearch(pSeqList pSeq, DataType x)
{
	int low=0;
	int high=pSeq->size-1;
	int mid=(low+high)/2;
	while((high>=low) && (pSeq->arr[mid]!=x))
	{
		if(pSeq->arr[mid]>x)
		{
			high=mid-1;
		}
		else if(pSeq->arr[mid]<x)
		{
			low=mid+1;
		}
		mid=(high+low)/2;	
	}
	if(pSeq->arr[mid]==x)
		{
			return x;
		}
	else
	{
	  return -1;
	}
}


#endif