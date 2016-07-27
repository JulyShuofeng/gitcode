#pragma once
#include<iostream>
using namespace std;

template <class K,int M=3>
struct BTreeNode
{
	K _key[M];		  //ֻ��M-1������һ���������
	BTreeNode<K, M>* _subs[M + 1];		//��������
	BTreeNode<K, M>* _parent;			 
	size_t _size;			//�ؼ��ֵĸ���

	BTreeNode()
		:_size(0)
		, _parent(NULL)
	{
		for (size_t i = 0; i < M + 1; i++)
		{
			_subs[i] = NULL;
		}
	}

};

//template<class K,class V>
//struct Pair
//{
//	K _first;
//	V _second;
//	
//	Pair(const K& key, const V& value)
//		:_first(key)
//		, _secode(value)
//	{}
//};

template <class K,int M=3>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree()
		:_root(NULL)
	{}

	pair<Node*, int> Find(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			int i = 0;
			while (cur->_size > i && cur->_key[i] < key)
			{
				++i;
			}
			if (cur->_key[i] == key)
			{
				return pair<Node*, int>(cur, i);
			}
			parent = cur;
			cur = cur->_subs[i];
		}
		return pair<Node*, int>(parent, -1);
	}

	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node;
			_root->_key[0] = key;
			_root->_size = 1;
			return true;
		}
		pair<Node*, int> ret = Find(key);
		if (ret.second != -1)
		{
			return false;
		}
		Node* cur = ret.first;
		K newkey = key;
		Node* sub = NULL;
		while (1)
		{
			InsertKey(cur, newkey, sub);
			if (cur->_size < M)
			{
				return true;
			}
			int div = M / 2;			  //�м�λ��
			//����
			Node* tmp = new Node;
			size_t index = 0;
			//����key
			for (size_t i = div + 1; i < cur->_size; ++i)		 //�����Ұ����䵽�½ڵ�
			{
				tmp->_key[index++] = cur->_key[i];
				tmp->_size++;
				cur->_key[i] = K();//�����ѳ�ȥ��λ��������λ
			}
			//����subs
			index = 0;
			for (size_t i = div + 1; i < cur->_size +1; ++i)	   //���ӱ�key��һ��
			{
				tmp->_subs[index++] = cur->_subs[i];
				if (cur->_subs[i])
				{
					cur->_subs[i]->_parent = tmp;
				}
			}
			cur->_size = (cur->_size) - (tmp->_size) - 1;
			if (cur->_parent == NULL)			   //cur->parentΪ�գ�˵��curΪ���ڵ�
			{
				_root = new Node;
				_root->_key[0] = cur->_key[div];
				cur->_key[div] = K();
				_root->_subs[0] = cur;//С��λ��0��λ��
				_root->_subs[1] = tmp;//���λ��1��λ��
				cur->_parent = _root;
				tmp->_parent = _root;
				
				_root->_size = 1;
				
			   return true;
			}
			else
			{
				newkey = cur->_key[div];
				cur->_key[div] = K();
				
				sub = tmp;
				cur = cur->_parent;
			}
		}
		return true;
	}

	void InsertKey(Node* cur, K& key, Node* sub)
	{
		int end = cur->_size - 1;//��������һ��key���±�
		while (end >= 0)
		{
			if (cur->_key[end] > key)
			{
				cur->_key[end + 1] = cur->_key[end];
				cur->_subs[end + 2] = cur->_subs[end + 1];
			}
			else
			{
				break;
			}
			--end;
		}
		cur->_key[end + 1] = key;
		cur->_subs[end + 2] = sub;	  //����ʱΪ��
		if (sub)
		{
			sub->_parent = cur;
		}
		++(cur->_size);
	}

	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

protected:
	void _Inorder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		size_t i = 0;
		for (i=0; i < root->_size; ++i)
		{
			_Inorder(root->_subs[i]);		  //�ȵݹ��ٴ�ӡ
			cout << root->_key[i] << " ";
			
		}
		_Inorder(root->_subs[i]);
	}

protected:
	Node* _root;
	
};

