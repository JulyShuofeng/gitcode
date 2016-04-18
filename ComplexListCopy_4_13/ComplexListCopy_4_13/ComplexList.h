#pragma once
#include<iostream>
#include<cassert>
#define DataType int
using namespace std;

 struct ComplexNode
{
	DataType _data;
	struct ComplexNode * _next;
	struct ComplexNode * _random;
};

 //class ComplexList
 //{	 
 //public:
	// ComplexList()
	//	 :_head(NULL)
	//	 ,_tail(NULL)
	// {}

	// ~ComplexList()
	// {
	//	 if(_head==NULL)
	//	 {
	//		  return;
	//	 }
	//	 ComplexNode *cur =_head;
	//	 while(cur->_next!=NULL)
	//	 {
	//		 ComplexNode *del=cur;
	//		 cur=cur->_next;
	//		 delete del;
	//	 }
	//	 delete cur;
	// }

	// ComplexList(const ComplexList& L)
	//	 :_head(L._head)
	//	 ,_tail(L._tail)
	// {
	//	 ComplexNode *cur=_head;
	//	 while(cur!=NULL)
	//	 {
	//		 PushBack(cur->_data);
	//		 cur=cur->_next;
	//	 }
	// }

	// ComplexList& operator=(ComplexList L)
	// {
	//	 swap(_head,L._head);
	//	 swap(_tail,L._tail);
	// }

	// void PushBack(const DataType& d);
	// void PopBack();
	// void CopyNode();
	// void ConnectRandom();
	// ComplexNode* SplitList();
	// ComplexNode* Copy();

 //protected:
	// ComplexNode *_head;
	// ComplexNode *_tail;

 //};

//void ComplexList::PushBack(const DataType& d)
//{		
//	ComplexNode *newNode=new ComplexNode(d); 
//	if(_head==NULL)
//	{
//		return;
//	}
//	else
//	{
//		_tail->_next =newNode;
//		_tail=newNode;
//	}
//}

/*void ComplexList::PopBack()
{
	if(_head==NULL)
	{
		return;
	}
	else if(_head==_tail)
	{
		 delete _head;
		 _head=NULL;
		 _tail=NULL;
		 return;
	}
	else
	{
		ComplexNode *cur=_head;
		while(cur->_next!=_tail)
		{
			cur=cur->_next;
		}
		delete _tail;
		_tail=cur;
		cur->_next=NULL;
	}
}*/						  

void CopyNode(ComplexNode *pHead)
{
	ComplexNode *pNode=pHead;
	while(pNode!=NULL)
	{
		ComplexNode *pCopy=new ComplexNode;
		pCopy->_data=pNode->_data;
		pCopy->_next=pNode->_next;
		pCopy->_random=NULL;
		pNode->_next=pCopy;
		pNode=pCopy->_next;
	}
}


void ConnectRandom(ComplexNode *pHead)
{
	ComplexNode *pNode=pHead;
	while(pNode!=NULL)
	{
		ComplexNode *pCopy=pNode->_next;
		if(pNode->_random!=NULL)
		{
			pCopy->_random=pNode->_random->_next;
		}
		pNode=pCopy->_next;
	}
}

ComplexNode* SplitList(ComplexNode *pHead)
{
	/*ComplexNode *pNode=pHead;
	ComplexNode *pCopy=NULL;
	ComplexNode *pCopyHead=pHead->_next;
	if(pNode!=NULL)
	{
		pCopyHead=pCopy=pNode;
		pNode->_next=pCopy->_next;
		pNode=pNode->_next;
	}
	while(pNode!=NULL)
	{
		pCopy->_next=pNode->_next;
		pCopy=pCopy->_next;
		pNode->_next=pCopy->_next;
		pNode=pNode->_next;
	}
	return pCopyHead;*/

	ComplexNode *pCloneHead = pHead->_next;
    ComplexNode *tmp;	   
    ComplexNode *cur = pHead;
        while(cur->_next)
		{
            tmp = cur->_next;
            cur->_next =tmp->_next;
            cur = tmp;
        }
        return pCloneHead;
}

ComplexNode* Copy(ComplexNode *pHead)
{
	  if (pHead==NULL)
	  {
		  return NULL;
	  }
	  CopyNode(pHead);
	  ConnectRandom(pHead);
	  return   SplitList(pHead);
}	 

void deleteList(ComplexNode* pHead)
{
	while(pHead!=NULL)
    {
		ComplexNode* cur = pHead->_next;
        delete pHead;
        pHead = cur;
    }
}