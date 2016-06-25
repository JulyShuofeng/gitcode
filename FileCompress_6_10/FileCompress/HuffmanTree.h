#pragma once
#include"Heap.h"
#include<iostream>
using namespace  std;

template  <class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode<T> *_left;
	HuffmanTreeNode<T> *_right;
	T _weight;

	HuffmanTreeNode(const T& x)
		:_left(NULL)
		, _right(NULL)
		, _weight(x)
	{}
};

template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;

public:
	HuffmanTree(const T* a, size_t n,const T invalid)
	{
		struct NodeCompare
		{
			bool operator() (const Node* left, const Node* right)
			{
				return left->_weight < right->_weight;
			}
		};

		Heap<Node* ,NodeCompare> minHeap;
		for (int i = 0; i < n; i++)
		{
			if (a[i] != invalid)
			{
				minHeap.Push(new Node(a[i]));
			}
		}
		while (minHeap.Size()>1)
		{
			Node *left = minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();
			Node* parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			parent->_right = right;
			minHeap.Push(parent);
		}
		_root = minHeap.Top();
	}

	~HuffmanTree()
	{
		Destory(_root);
		_root = NULL;
	}

	Node* _GetRoot()
	{
		return _root;
	}


protected:
	void Destory(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		Destory(root->_left);
		Destory(root->_right);
		delete root;
	}
//protected:

	Node* _root;

};