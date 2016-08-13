#pragma once
#include<iostream>
#include<assert.h>
#include<string>
#include<vector>
using namespace std;

template<class V, class W>
class GraphMatrix
{
public:
	GraphMatrix(V* a, size_t size, bool isdirection)
		:_size(size)
		, _vertexs(new V[size])
		, _isdirection(isdirection)
	{
		//��̬������λ����
		_edges = new W*[size];
		for (size_t i = 0; i < size; ++i)
		{
			_edges[i] = new W[size];
			memset(_edges[i], 0, sizeof(W*)*size);
			_vertexs[i] = a[i];//��ʼ������
		}
	}

	void AddEdge(const V& src, const V& dst,const W& w)	 //w��ʾȨֵ
	{
		size_t srcIndex = GetVertexIndex(src);
		size_t dstIndex = GetVertexIndex(dst);
		if (!_isdirection)
		{
			_edges[srcIndex][dstIndex] = w;
			_edges[dstIndex][srcIndex] = w;
		}
		else
		{
			_edges[srcIndex][dstIndex] = w;
		}
	}

	int GetVertexIndex(const V& v)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_vertexs[i] == v)
			{
				return i;
			}
		}
		assert(false);
		return -1;
	}
protected:
	
	V* _vertexs;//���㼯��
	W** _edges;//����
	size_t _size;//�������
	bool _isdirection;//�Ƿ�Ϊ����ͼ	 ��ʼ������Ϊfalse��ʾ����
};

template<class V,class W>
class GraphLink
{
protected:
	vector<V> _vertexs;
	vector<>

};