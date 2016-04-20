#pragma once
#include<iostream>
#include<cassert>
using namespace std;

enum Type
{
	HEAD,//头
	VALUE, //值
	SUB, //子表
};

struct GeneralizedNode
{
	Type _type;
	GeneralizedNode* _next;
	union
	{
		char _value;
		GeneralizedNode* _sublink;
	};

	GeneralizedNode(Type type=HEAD,char value=0)
		:_type(type)
		,_next(NULL)
	{
		 if(_type==VALUE)
		 {
			 _value=value;		 
		 }
		 else  if(_type==SUB)
		 {
			 _sublink=NULL;
		 }
	}
};

class Generalized
{
public:
	 Generalized(const char* str)
		 :_head(NULL)
	 {
		 _head=_CreateList(str);
	 }

	 Generalized()
		 :_head(new GeneralizedNode())
	 {}
	 
	 ~ Generalized()
	 {
		 _Clear(_head);
		 _head=NULL;
	 }
					 
	 size_t Depth()	   //深度
	 {
		return  _Depth(_head);
	 }

	 void Print()
	 {

		 _Print(_head);
		 cout<<endl;
	 }

	 size_t Size()		 
	 {
		  return _Size(_head);
	 }

	 Generalized(const Generalized &g)
	 {
		 _head=_Copy(g._head);
	 }

	 Generalized& operator=( Generalized g)
	 {
		 swap(this->_head,g._head);
		 return *this;
	 }

protected:
	GeneralizedNode* _head;

	GeneralizedNode* _CreateList(const char* &str)
	{
		 assert(str && *str=='(');
		 ++str;
		 GeneralizedNode* head=new GeneralizedNode(HEAD);
		 GeneralizedNode* cur=head;
		 while(*str)
		 {
			 if(_Isvalue(*str))
			 {
				 cur->_next=new GeneralizedNode(VALUE,*str);
				 cur=cur->_next;
				 str++;
			 }
			 else if(*str=='(')
			 {
				 cur->_next=new GeneralizedNode(SUB);
				 cur=cur->_next;
				 cur->_sublink=_CreateList(str);
				 
			 }
			 else if(*str==')')
			 {	
				  ++str;			 
				  return head;
				  
			 }
			 else
			 {
				 ++str;
			 }
		 }
		 assert(false);
		 return head;
	}

	bool _Isvalue(char ch)
	{
		if( (ch>='0'&&ch<='9') ||  (ch>='a'&&ch<='z')  ||  (ch>='A'&&ch<='z'))
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	/*int _Depth(GeneralizedNode* head)
	 {			 
		 GeneralizedNode* cur=head;
		 int max=0;
		 if(!cur)
		 {
			 return 1;
		 }
		 if(cur->_type==VALUE)
		 {
			 return 0;
		 }
		 for( max=0;cur;cur=cur->_next)	  
		 {						  
			 int dep=_Depth(cur->_next);
			 if(dep>max)
			 {
				 max=dep;
			 }
		 }
		 return max+1;
	 }*/

	size_t _Depth(GeneralizedNode* head)
	{
		size_t dep=1;
		GeneralizedNode* cur=head;
		while(cur!=NULL)
		{
			if(cur->_type==SUB)
			{
				if(_Depth(cur->_sublink)+1> dep)
				{
					dep=_Depth(cur->_sublink)+1 ;
				}
			}
			cur=cur->_next;
		}
		return dep;
	}

	void _Clear(GeneralizedNode* head)
	{
		GeneralizedNode* cur = head;
		while(cur != NULL)
		{
			GeneralizedNode* del = cur;	
			cur = cur->_next;
 			if(del->_type == SUB)
				{
                    _Clear(del->_sublink);
                }
            delete del;
		}
    }

	void _Print(GeneralizedNode* head)
	{
		GeneralizedNode* cur=head;
		while(cur)
		{  
			if(cur->_type==HEAD)
			{
				cout<<"(";
			}
			else if(cur->_type==VALUE)
			{
				cout<<cur->_value; 
				if(cur->_next)	
				{	
					cout<<"," ;
				}
			}
			else 
			{
				_Print(cur->_sublink);
				if(cur->_next)
				{
					cout<<",";
				}
			}
			
			cur=cur->_next;
		}
		cout<<")";
	}

	size_t _Size(GeneralizedNode* head)
	{
		GeneralizedNode* cur=head;
		size_t size=0;
		while(cur)
		{
			if(cur->_type==VALUE)
			{
				++size;
			}
			else if(cur->_type==SUB)
			{
				size+=_Size(cur->_sublink);		
			}
			cur=cur->_next;
		}
		return size;
	}

	 GeneralizedNode* _Copy(GeneralizedNode* head)
	 {
		 GeneralizedNode* newHead=new GeneralizedNode(HEAD);
		 assert(head->_type==HEAD);
		 GeneralizedNode* cur=head->_next;
		 GeneralizedNode* newcur=newHead;
		 while(cur)
		 {
			 if(cur->_type==VALUE)
			 {
				 newcur->_next=new GeneralizedNode(VALUE,cur->_value);
				 newcur=newcur->_next ;
			 }
			 else if(cur->_type==SUB)
			 {
				 newcur->_next=new GeneralizedNode(SUB);
				 newcur=newcur->_next;
				 newcur->_sublink=_Copy(cur->_sublink);
			 }
			 cur=cur->_next;
		 }
		 return newHead;
	 }

};