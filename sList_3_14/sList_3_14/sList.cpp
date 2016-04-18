#include"sList.h"

void sList::PushBack(const DataType& d)
{
	Node* newNode=new Node(d);
	if(_head==NULL)
	{
		_head=newNode;
		_tail=_head;
	}
	else
	{
		_tail->_next=newNode;
		_tail=newNode;
	}
}

void sList::PushFront(const DataType& d)
{
	Node* newNode=new Node(d);
	if(_head==NULL)
	{
		_head=newNode;
		_tail=_head;
	}
	else
	{
		newNode->_next=_head;
		_head=newNode;
	}

}

void sList::PopBack()
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
		Node* cur=_head;
		while(cur->_next!=_tail)
		{
			cur=cur->_next;
		}
		delete _tail;
		_tail=cur;
		cur->_next=NULL;
	}
}

void sList::PopFront()
{
	if(_head==NULL)
	{
		return;
	}
	else
	{
		Node* del=_head;
		_head=_head->_next;
		delete del;
		del=NULL;
	}
}

Node* sList::Find(const DataType& d)
{
	Node* cur=_head;
	while(cur!=NULL)
	{
		if(cur->_data==d)
		{
			return cur;
		}
		cur=cur->_next;
	}
	return NULL;
}

void sList::Insert(Node* pos,const DataType& d)
{
	if(pos==NULL)
	{
		return;
	}
	Node* newNode=new Node(d);
	if(pos==_tail)
	{
		_tail->_next=newNode;
		_tail=newNode;
	}
	else
	{
		newNode->_next=pos->_next;
		pos->_next=newNode;
	}
}
	
void sList::Reverse()
{
	if((_head==NULL) || (_head==_tail))
	{
		return;
	}
	Node* cur=_head;//therr point
	Node* prev=NULL;
	Node* newHead=NULL;
	while(cur)
	{
		prev=cur;
		cur=cur->_next;
		prev->_next=newHead;
		newHead=prev;
		_head=newHead;
	}
}

void sList::Sort()
{
	Node* cur=_head;
	Node* end=NULL;
	while(cur!=end)
	{
		while(cur && cur->_next!=end)
		{
		if(cur->_data  <  cur->_next->_data)
		{
			DataType tmp=cur->_data;
			cur->_data=cur->_next->_data;
			cur->_next->_data=tmp;
		}
		cur=cur->_next;
		}
	end=cur;
	cur=_head;
	}
}

void sList::Remove(const DataType& d)
{
	Node* cur=_head;
	Node* del=NULL;
	Node* prev=NULL;
	while(cur!=NULL)
	{
		if(cur->_data==d)
		{
			del=cur;
			if(cur==_head)
			{
				_head=_head->_next;
			}
			else
			{
				prev->_next=cur->_next;
			}
			delete del;
			break;
		}
		prev=cur;
		cur=cur->_next;
	}
}
void sList::RemoveAll(const DataType& d)
{
	Node* cur=_head;
	Node* del=NULL;
	Node* prev=NULL;
	while(cur!=NULL)
	{
		if(cur->_data==d)
		{
			del=cur;
			if(cur==_head)
			{
				_head=_head->_next;
				_head=cur;
			}
			else
			{
				prev->_next=cur->_next;
				cur=prev->_next;
			}
			delete del;
		}
		else
		{
			prev=cur;
		    cur=cur->_next;
		}
	}
}

void sList::Erase(Node* pos)
{
	if(pos==NULL)
	{
		return;
	}
	Node* del=NULL;
	Node* cur=_head;
	Node* prev=NULL;
	while(cur!=NULL)
	{
		if(pos==cur)
		{
			del=cur;
			{
				if(pos==_head)
				{
					_head=_head->_next;
				}
				else				
				{
					prev->_next=cur->_next;
				}
				delete del;
				break;
			}
		}
		prev=cur;
		cur=cur->_next;
	}
	
}

Node* sList::FindMidNode()
{
	Node* Slow=_head;
	Node* Fast=_head;
	if(Fast==NULL || Fast->_next==NULL)
	{
		return NULL;
	}
	else
	{
		while(Fast && Fast->_next)
		{
			Slow=Slow->_next;
			Fast=Fast->_next->_next;
		}
		return Slow;
	}
}

Node* sList::CheckCircle()
{
	Node* Slow=_head;
	Node* Fast=_head;
	while(Fast && Fast->_next)
	{
		Slow=Slow->_next;
		Fast=Fast->_next->_next;
		if(Fast==Slow)
		{
			return Slow;
		}
	}
	return NULL;
}

int GetCircleLength(Node* meet)
{
	Node* Start=meet;
	int count=0;
	do
	{
		count++;
		Start=Start->_next;
	}
	while(Start!=meet);
	return count;
}

Node* sList::GetCircleEntryNode(Node* meet)
{
	Node* entry=_head;
	while(entry!=meet)
	{
		entry=entry->_next;
		meet=meet->_next;
	}
	return entry;
}


void Test1()
{
	sList s1;
	sList s2;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	//cout<<s1;
	s2.PushFront(1);
	s2.PushFront(2);
	s2.PushFront(3);
	s2.PushFront(4);
	cout<<s2;
	//s2.PopBack();
	s2.PopFront();
	cout<<s2;
}

void Test2()
{
	sList s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(2);
	s1.PushBack(5);
	cout<<s1;
	//s1.Insert(s1.Find(2),0);
	//s1.Reverse();
	//s1.Sort();
	s1.RemoveAll(2);
	//s1.Erase(s1.Find(1));
	//Node* ret=s1.FindMidNode();
	//cout<<(ret->_data);
	cout<<s1;
}

int main()
{
	Test2();
	getchar();
	return 0;
}