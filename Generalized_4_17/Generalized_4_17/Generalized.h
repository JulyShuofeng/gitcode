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
		,_value(value)
	{
		 if(_type==VALUE)
		 {
			 _value=value;		 
		 }
		 else  if(_type=SUB)
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
	 
	 ~ Generalized()
	 {
		 //_Clear(_head);
	 }

	 int Depth()
	 {
		return  _Depth(_head);
	 }

	 void Print()
	 {

		 _Print(_head);
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
				 
				 cur->_sublink=_CreateList(str);
				 cur=cur->_next;
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
		if( ch>='0'&&ch<='9' ||  ch>='a'&&ch<='z'  ||  ch>='A'&&ch<='z')
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

	int _Depth(GeneralizedNode* head)
	{
		int dep=1;
		GeneralizedNode* cur=head;
		while(cur!=NULL)
		{
			if(cur->_type==SUB)
			{
				if(_Depth((cur->_sublink)+1) > dep)
				{
					dep=_Depth(cur->_sublink)+1 ;
				}
			}
			cur=cur->_next;
		}
		return dep;
	}

	 //int _Depth(GeneralizedNode* head){             //深度的计算，找到子表个数最多
  //      GeneralizedNode* begin = head;
  //      int depth = 0;
  //      int max = 0;
 
  //      while (begin){
  //      if (begin->_type == HEAD)
  //          return 1;
  //      else if (begin->_type == VALUE){
  //          begin = begin->_next;
  //      }
  //      else if (begin->_type == SUB){
  //          depth = _Depth(begin->_sublink);
  //          if (depth > max)
  //              max = depth;
  //          begin = begin->_next;
  //      }
  //      }
  //      return max+1;
  //  }

	void _Clear(GeneralizedNode* head)
	{
		GeneralizedNode* cur = head;
		while(cur != NULL)
		{
			GeneralizedNode* del = cur;	
			cur = cur->_next;
 			if(cur->_type == SUB)
				{
                    _Clear(cur->_sublink);
                }
            delete del;
		}
    }

	void _Print(GeneralizedNode* head)
	{
		GeneralizedNode* cur=head;
		
		cur=cur->_next;
		while(cur)
		{  
			if(cur->_type==HEAD)
			{
				cout<<"（";
			}
			else if(cur->_type==VALUE)
			{
				cout<<cur->_value; 
				if(cur!=NULL)	
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

};