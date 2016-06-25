#pragma once
#include<iostream>
#include<string>
#include"HuffmanTree.h"

using namespace std;
typedef unsigned long LongType;


struct charInfo
{

	unsigned char _ch;	  //字符
	LongType _count; //	出现的次数
	string _code;  //字符对应的编码

	charInfo(LongType count = 0)
		:_count(count)
	{}

	bool operator!=(const charInfo& info)const
	{
		return _count != info._count;
	}

	charInfo operator+(const charInfo& info)
	{
		return charInfo(_count + info._count);
	}

	bool  operator<(const charInfo& info)const
	{
		return _count < info._count;
	}
};

class FileCompress
{
public:
	FileCompress()
	{
		for (size_t  i = 0; i < 256; ++i)
		{
			_infos[i]._ch = i;
			_infos[i]._count = 0;
		}
	}

	void Compress(const char* filename)
	{
		FILE *fOut = fopen(filename, "rb");
		assert(fOut);
		//统计文件中字符出现的次数
		char ch = fgetc(fOut);
		while (!feof(fOut))
		{
			_infos[(unsigned char)ch]._count++;
			ch = fgetc(fOut);
		}
		//建树
		charInfo invalid;
		HuffmanTree<charInfo> tree(_infos, 256,invalid);
		//生成哈夫曼编码
		string code;
		GeneratHuffmanTreeCode(tree._GetRoot(), code);
		//读取源文件字符压缩，将哈夫曼编码写进对应的位
		string compressFilename = filename;
		compressFilename += ".compress";
		FILE* fIn = fopen(compressFilename.c_str(), "wb");
		fseek(fOut, 0, SEEK_SET);
		ch = fgetc(fOut);
		char value = 0;
		int size = 0;
		while (!feof(fOut))
		{
			string& code = _infos[(unsigned char)ch]._code;
			for (size_t i = 0; i < code.size(); ++i)
			{
				value <<= 1;
				if (code[i] == '1')
				{
					value |= 1;
				}
				
				if (++size == 8)
				{
					fputc(value, fIn);
					value = 0;
					size = 0;
				}
			}
			ch = fgetc(fOut);
		}
		if (size> 0)	   //补位
		{
			value <<= (8 - size);
			fputc(value, fIn);
		}
		//写配置文件
		string configFile = filename;
		configFile += ".config";
		FILE* fconfig = fopen(configFile.c_str(), "wb");
		string line;
		char buffer[128];
		for (size_t i = 0; i < 256; ++i)
		{
			if (_infos[i]._count>0)
			{
				line += _infos[i]._ch;
				line += ",";
				_itoa(_infos[i]._count, buffer, 10);
			   line += buffer;
				line += '\n';	
			}
			fputs(line.c_str(), fconfig);
			line.clear();
		}
		fclose(fOut);
		fclose(fconfig);
		fclose(fIn);
	}

	bool ReadLine(FILE* fOut, string& line)
	{
		char ch = fgetc(fOut);
		if (feof(fOut))
		{
			return false;
		}
		while (!feof(fOut) && ch!='\n')
		{
			line += ch;
			ch = fgetc(fOut);
		}
		return true;
	}

	void Uncompress(const char* filename)
	{
		//读配置文件，得字符个数
		string configFile = filename;
		configFile += ".config";
		FILE* fconfig = fopen(configFile.c_str(), "rb");
		assert(fconfig);
		string line;
		LongType charCount = 0;
		while (ReadLine(fconfig,line))
		{
			if (line.empty())
			{
				line += '\n';
			}
			else
			{
				unsigned char ch = line[0];
				_infos[ch]._count = atoi(line.substr(2).c_str());
				line.clear();
			}	
		}
		//	  构建树
		charInfo invalid;
		HuffmanTree<charInfo> tree(_infos, 256, invalid);
		charCount = tree._GetRoot()->_weight._count;
		//读取压缩文件，还原
		string compressFile = filename;
		compressFile += ".compress";
		FILE* fOut = fopen(compressFile.c_str(), "rb");
		assert(fOut);

		string uncompressFile = filename;
		uncompressFile += ".uncompress";
		FILE* fIn = fopen(uncompressFile.c_str(), "wb");
		assert(fIn);

		HuffmanTreeNode<charInfo>* root = tree._GetRoot();
		HuffmanTreeNode<charInfo>* cur = root;

		char ch = fgetc(fOut);
		int pos = 7;
		while (1)
		{
				if (ch & 1 << pos)
				{
					cur = cur->_right;
				}
				else
				{
					cur = cur->_left;
				}

				if (pos-- == 0)  //一个字节的八个位读完了
				{
					pos = 7;//读下一个字符   
					ch = fgetc(fOut);
				}
			
				if (cur->_left == NULL && cur->_right == NULL) //到叶子节点
				{
					fputc(cur->_weight._ch, fIn);
					if (--charCount == 0)
					{
						break;
					}
					cur = root;
				}
		}
		fclose(fOut);
		fclose(fIn);
	}


	void GeneratHuffmanTreeCode(HuffmanTreeNode<charInfo>* root, string code)
	{
		if (root == NULL)
		{
			return;
		}
		if (root->_left == NULL && root->_right == NULL)
		{
			_infos[root->_weight._ch]._code = code;
			return;
		}
		GeneratHuffmanTreeCode(root->_left, code + '0');
		GeneratHuffmanTreeCode(root->_right, code + '1');
	}
	
protected:
	charInfo _infos[256];
};

