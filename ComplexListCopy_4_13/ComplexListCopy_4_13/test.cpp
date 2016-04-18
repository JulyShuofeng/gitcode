#include"ComplexList.h" 

void Test()
{
	ComplexNode *node1=new ComplexNode;
	ComplexNode *node2=new ComplexNode;
	ComplexNode *node3=new ComplexNode;
	ComplexNode *node4=new ComplexNode;
	node1->_data=1;
	node2->_data=2;
	node3->_data=3;
	node4->_data=4;
	node1->_next=node2;
	node2->_next=node3;
	node3->_next=node4;
	node4->_next=NULL;
	node2->_random=node4;
	node1->_random=node3;
	node3->_random=NULL;
	node4->_random=NULL;
	ComplexNode *copyHead=Copy(node1);
	while(copyHead!=NULL)
	{
		cout<<copyHead->_data;
		copyHead=copyHead->_next;
	}
	deleteList(node1);
	deleteList(copyHead);
}

int main()
{
	Test();
	getchar();
	return 0;
}