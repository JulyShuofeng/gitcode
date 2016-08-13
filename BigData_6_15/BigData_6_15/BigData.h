#pragma once
#include<iostream>
#include<cassert>
#include<string>
using namespace std;
#define UN_INIT 0xcccccccc
#define MIN_INIT64  0x8000000000000000
#define MAX_INIT64 0x7fffffffffffffff
typedef long long INT64;
class BigData
{
public:
	BigData(INT64 value=UN_INIT)
		:_value(value)
	{
		if (_value == 9223372036854775808)
		{
			_strData = "+9223372036854775808";
			return;
		}
		char Symbol = '+';
		if (_value < 0)
		{
			Symbol = '-';
		}
		{
			INT64 num = _value;
			char ret = 0;
			int index = 1;
			_strData.append(1, Symbol);//在字符串结尾追加一个符号位
			while (num)
			{
				if (num < 0)
				{
					num = 0 - num;
				}
				ret = num % 10 + '0';
				_strData.append(1, ret);
				num = num / 10;
			}
		}
		//将逆置的字符串交换
		char* left = (char*)_strData.c_str() + 1;		//加1跳过符号位
		char* right = left + _strData.size() - 2;	   
		while (left < right)
		{
			char tmp = *left;
			*left = *right;
			*right = tmp;
			left++;
			right--;
		}
	}

	BigData(const char *cData)
		:_value(0)
	{
		if (cData == NULL)
		{
			assert(false);
			return;
		}

		char* ptr = (char*)cData;
		char cSymbol = cData[0];   //“0000”  ""

		if (cSymbol == '-' || cSymbol == '+')
		{
			ptr++;
		}
		else if (cSymbol >= '0' && cSymbol <= '9')
		{
			cSymbol = '+';
		}
		else
		{
			return;
		}

		while (*ptr == '0')
		{
			++ptr;
		}

		_strData.resize(strlen(cData) + 1);
		_strData[0] = cSymbol;

		_value = 0;
		int iCount = 1;

		while (*ptr >= '0' && *ptr <= '9')
		{
			_value = _value * 10 + (*ptr - '0');
			_strData[iCount++] = *ptr;
			++ptr;
		}

		_strData.resize(iCount);

		if (cSymbol == '-')
		{
			_value = 0 - _value;
		}
	}

	friend ostream& operator<<(ostream& _cout, const BigData& bigdata);

	bool IsINIT64Overflow()const
	{
		string tmp("9223372036854775807");

		if (_strData[0] == '-')
		{
			tmp = "-9223372036854775808";
		}

		if (_strData.size() < tmp.size())
		{
			return true;
		}
		else if (_strData.size() == tmp.size() && _strData<tmp)
		{
			return true;
		}

		return false;
	}

	BigData operator+( BigData bigdata)
	{
		if (IsINIT64Overflow() && bigdata.IsINIT64Overflow())
		{

			if (_strData[0] != bigdata._strData[0])//若异号，则肯定不会溢出
			{
				return BigData(_value + bigdata._value);
			}
			else
			{
				if (_strData[0] == '+'&&MAX_INIT64 - _value >= bigdata._value || _strData[0] == '-'&&_value >= MIN_INIT64 - bigdata._value)
				{
					return BigData(_value + bigdata._value);
				}
			}
		}
			BigData tmp(*this);
			return BigData(Add(tmp._strData, bigdata._strData).c_str());
	}

	BigData operator-(BigData bigdata)
	{
		if (IsINIT64Overflow() && bigdata.IsINIT64Overflow())
		{
			if (_strData[0] == bigdata._strData[0]) //若同号，则肯定不会溢出
			{
				return BigData(_value - bigdata._value);
			}
			else
			{
				if (_strData[0] == '+'&&MAX_INIT64 + bigdata._value>= _value || _strData[0] == '-'&&_value > MIN_INIT64 + bigdata._value)
					return BigData(_value - bigdata._value);
			}
		}
		string ret;
		BigData tmp(*this);
		if (_strData[0] == bigdata._strData[0])
		{
			ret=Sub(_strData, bigdata._strData).c_str();
		}
		else
		{
			char flag = _strData[0];
			if (_strData[0] == '-' && bigdata._strData[0]=='+')
			{
				_strData[0] = '+';
			}
			if (_strData[0] == '+' && bigdata._strData[0] == '-')
			{
				bigdata._strData[0] = '+';
			}
			ret= Add(_strData, bigdata._strData).c_str();
			ret[0] =flag;
		}
		return BigData(ret.c_str());
	}

	BigData operator*(BigData bigdata)
	{
		if (IsINIT64Overflow() && bigdata.IsINIT64Overflow())
		{
			if (_strData[0] == bigdata._strData[0])
			{
				if (_strData[0] == '+'&&_value <= MAX_INIT64 / bigdata._value || _strData[0] == '-'&&_value >= MAX_INIT64 / bigdata._value)
				{
					return BigData(_value*bigdata._value);
				}
			}
			else
			{
				if (_strData[0] == '+' && MIN_INIT64 / _value <= bigdata._value || _strData[0] == '-' && _value >= MIN_INIT64 / bigdata._value)
				{
					return BigData(_value*bigdata._value);
				}
			}
		}
		BigData tmp(*this);
		return BigData((char*)Mul(tmp._strData, bigdata._strData).c_str());
	}

	BigData operator/(BigData bigdata)
	{
		if ('0' == bigdata._strData[1])      //检查除数是否为零
		{
			assert(false);
			return BigData(INT64(0));
		}
		if (IsINIT64Overflow() && bigdata.IsINIT64Overflow())
		{
				return BigData(_value / bigdata._value);
		}
		if (_strData.size() < bigdata._strData.size() || (_strData.size() == bigdata._strData.size() && strcmp(_strData.c_str() + 1, bigdata._strData.c_str() + 1) < 0))
		{
			return BigData(INT64(0));
		}
		//除数为1或者-1
		if (bigdata._strData == "+1" || bigdata._strData == "-1")
		{
			string ret = _strData;
			if (_strData[0] != bigdata._strData[0])
			{
				ret[0] = '-';
			}
			else
			{
				ret[0] = '+';
			}
			return BigData(ret.c_str());
		}
		//left = right
		if (strcmp(_strData.c_str() + 1, bigdata._strData.c_str() + 1) == 0)
		{
			string tmp = "+1";
			if (_strData[0] != bigdata._strData[0])
			{
				tmp[0] = '-';
			}
			return BigData(tmp.c_str());
		}
		return BigData(Div(_strData, bigdata._strData).c_str());
	}
 protected:
	string Add(string& left, string& right)
	{
		int leftsize = left.size();
		int rightsize = right.size();
		char cSymbol = '+';
		string strRet;
		if (left[0] != right[0])//符号不等
		{
			if (left[0] == '+')
			{
				right[0] = '+';
				return Sub(left, right);
			}
			else
			{
				left[0] = '+';
				return Sub(right, left);
			}
		}
		else
		{
			if (left[0] == '+')
			{
				cSymbol = '+';
			}
			if (left[0] == '-')
			{
				cSymbol = '-';
			}
		}
		if (leftsize < rightsize)		
		{
			swap(left, right);
			swap(leftsize, rightsize);
		}
		strRet.resize(leftsize + 1);	  //交换后left为大数
		memset((void*)strRet.c_str(), '0', strRet.size()*sizeof(char));
		strRet[0] = cSymbol;
		int cstep = 0;				   //进位
			
		//逐位相加
		for (int i = 1; i < leftsize; ++i)	 //跳过符号位从1开始
		{
			char cRet = left[leftsize - i] - '0' + cstep;//从低位开始取
			if (i < rightsize)
			{
				cRet +=right[rightsize - i] - '0';
			}
			strRet[leftsize - i + 1] = cRet % 10 + '0';
			cstep = cRet / 10;//计算进位
			
		}
		strRet[1] = cstep + '0';//处理最高位的进位
		return strRet;
	}


	string Sub(string& s1, string& s2)
	{
		int leftSize = s1.size();
		int rightSize = s2.size();
		char symbol = s1[0];
		if (leftSize<rightSize || leftSize == rightSize&&strcmp(s1.c_str() + 1, s2.c_str() + 1)<0)
		{
			swap(leftSize, rightSize);
			swap(s1, s2);
			if (symbol = '+')
				symbol = '-';
			else
				symbol = '+';
		}
		string ret;
		ret.resize(leftSize);
		memset((void*)ret.c_str(), '0', ret.size()*sizeof(char));
		ret[0] = symbol;
		char cret;
		for (int dx = 1; dx<leftSize; ++dx)
		{
			cret = s1[leftSize - dx] - '0';
			if (dx<rightSize)
			{
				cret -= (s2[rightSize - dx] - '0');
			}
			if (cret<0)
			{
				s1[leftSize - dx - 1] -= 1;
				cret += 10;
			}
			ret[leftSize - dx] = cret + '0';
		}
		return ret;
	}

	string Mul(string& s1, string& s2)
	{
		int leftsize = s1.size();
		int rightsize = s2.size();
		if (leftsize > rightsize)
		{
			swap(leftsize, rightsize);
			swap(s1, s2);
		}
		char symbol = '+';
		if (s1[0] != s2[0])
		{
			symbol = '-';
		}
		string ret;
		ret.resize(leftsize + rightsize - 1,'0');//相乘后只需一个符号位
		//memset((void*)ret.c_str(), '0', ret.size()*sizeof(char));
		ret[0] = symbol;
		int len = ret.size();
		int offset = 0;			//错位
		char cstep = 0;
		for (int Lindex = 1; Lindex< leftsize; ++Lindex)		  //控制多少次
		{
			char cleft= s1[leftsize - Lindex] - '0';		//记下该数
			cstep = 0;
			if (cleft == 0)
			{
				offset++;
				continue;
			}
			for (int Rindex = 1; Rindex < rightsize; ++Rindex)		  //控制乘rightsize次  用left的每一位一次乘right
			{
				char cRet = cleft*(s2[rightsize - Rindex] - '0');
				cRet += ret[len - Rindex - offset] - '0';
				cRet += cstep;
				cstep = cRet / 10;
				ret[len - Rindex - offset] = cRet % 10 + '0';		//单次相乘结果
			}
			ret[len - rightsize - offset] += cstep;
			offset++;
		}
		return ret;
	}

	char loopmove(char* pleft, int Lsize, const char* pright, int Rsize)
	{
		assert(pleft != NULL && pright != NULL);
		char pret = '0';
		while (1)   //被除数>除数
		{
			if (!IsLeftString(pleft, Lsize, pright, Rsize))
			{
				break;
			}
			for (int i = 0; i < Rsize; i++)
			{
				char ret = pleft[Lsize - i - 1] - '0';
				ret -= pright[Rsize - i - 1] - '0';
				if (ret < 0)
				{
					pleft[Lsize - i - 2] -= 1;
					ret += 10;
				}
				pleft[Lsize - i - 1] = ret + '0';
			}
			while (*pleft == '0' && Lsize > 0)
			{
				pleft++;
				Lsize--;
			}
			pret++;
		}
		return pret;
	}

	bool IsLeftString(const char* pleft, int Lsize, const char* pright, int Rsize) //判断被除数大于或等于除数
	{
		if (Lsize > Rsize || (Lsize == Rsize && strcmp(pleft, pright) >= 0))
		{
			return true;
		}
		return false;
	}

	string Div(string left, string right)      //字符串相除
	{
		string ret;
		ret.resize(1, '+');
		if (left[0] != right[0])       //确定商的符号
		{
			ret[0] = '-';
		}
		char* pleft = (char*)(left.c_str() + 1);
		char* pright = (char*)(right.c_str() + 1);
		int len = right.size() - 1;        //因为有符号位
		for (int i = 0; i < left.size() - 1;)
		{

			if (!(IsLeftString(pleft, len, pright, right.size() - 1)))
			{
				ret.append(1, '0');
				len++;
			}
			else
			{
				ret.append(1, loopmove(pleft, len, pright, right.size() - 1));
				while (*pleft == '0' && len > 0)
				{
					pleft++;
					i++;
					len--;
				}
				len++;
			}
			if (len > right.size())//pLeft比pRight大一位结果为0，则pLeft中含有0
			{
				pleft++;
				len--;
				i++;
			}
			if (len + i > left.size() - 1)
			{
				break;
			}
		}
		return ret;
	}

private:
	INT64 _value;
	string _strData;
};

ostream& operator<<(ostream& _cout, const BigData& bigdata)
{
	if ((bigdata.IsINIT64Overflow()))
	{
		_cout << bigdata._value << endl;
	}
	else
	{
		char *pData = (char*)bigdata._strData.c_str();
		if ('+' == bigdata._strData[0])
		{
			pData++;
			_cout << pData << endl;
		}
		else
		{
			_cout << pData << endl;
		}
	}
	return _cout;
}