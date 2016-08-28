#pragma once

#include<iostream>
#include<string>
#include<map>
#include<vector>
#include <algorithm>

#include<unordered_map>
#include<thread>
#include<mutex>

#include<time.h>
#include<stdarg.h>
#include<assert.h>

#ifdef _WIN32
#include<windows.h>
#else
#include<pthread.h>
#endif//_WIN32


using namespace std;

typedef long long LongType;

template<class T>		  //单例---父类
class Singleton
{
public:
	static T* GetInstance()
	{
		assert(_sInstance);
		return _sInstance;
	}

protected:
	static T* _sInstance;
};

template<class T>
T* Singleton<T>::_sInstance = new T;

class SaveAdapter	//保存适配器
{
public:
	virtual void Save(const char* format, ...) = 0;
};

class ConsoleSaveAdapter :public SaveAdapter
{
public:
	virtual void Save(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		vfprintf(stdout, format, args);
		va_end(args);
	}
};

class FileSaveAdapter :public SaveAdapter
{
public:
	FileSaveAdapter(const char* filename)
	{
		_fout = fopen(filename, "w");
		assert(_fout);
	}

	~FileSaveAdapter()
	{
		if (_fout)
		{
			fclose(_fout);
		}
	}

	virtual void Save(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		vfprintf(_fout, format, args);
		va_end(args);
	}

protected:
	//防拷贝
	FileSaveAdapter(FileSaveAdapter&);
	FileSaveAdapter& operator=(FileSaveAdapter&);

protected:
	FILE* _fout;
};

//配置管理
enum ConfigOptions
{
	NONE = 0,
	PERFORMANCE_PROFILER = 1,
	SAVE_TO_CONSOLE = 2,
	SAVE_TO_FILE = 4,
	SORT_BY_COSTTIME = 8,
	SORT_BY_CALLCOUNT = 16,
};

class ConfigManager : public Singleton<ConfigManager>
{
public:
	void SetOptions(int options)
	{
		_options = options;
	}

	void AddOptions(int options)
	{
		_options |= options;
	}

	void DelOption(int options)
	{
		_options &= (~options);
	}

	int GetOptions()
	{
		return _options;
	}

protected:
	friend class Singleton<ConfigManager>;

	ConfigManager()
		:_options(NONE)
	{}

	ConfigManager(const ConfigManager&);
	ConfigManager& operator=(const ConfigManager&);

protected:
	int _options;
};

struct PPNode		  //PerformanceProfiler Node 
{
	string _filename;
	string _function;
	size_t _line;
	string _desc;

	PPNode(const char* filename, const char* function, size_t line, const char* desc)
		:_filename(filename)
		, _function(function)
		, _line(line)
		, _desc(desc)
	{}

	bool operator==(const PPNode& node) const
	{
		if (_line == node._line&&_function == node._function&&_filename == node._filename)
		{
			return true;
		}
		return false;
	}
};

struct PPSection
{
	PPSection()
	:_totalcostTime(0)
	, _totalcallCount(0)
	, _totalbeginTime(0)
	{}

	void PPSection::Begin(int id)
	{
		if (id == -1)//id==-1表示单线程
		{
			if (_totalRefCount++ == 0)
			{
				_totalbeginTime = clock();
			}
		}
		else				 //多线程
		{
			lock_guard<mutex> lock(_mtx);
			//分别统计各个线程的花费时间和总的花费时间、调用次数
			if (_refCountMap[id]++ == 0)
			{
				_beginTimeMap[id] = clock();
			}
		}
	}

	void End(int id)
	{
		if (id == -1)
		{
			if (--_totalRefCount == 0)
			{
				_totalcostTime += clock() - _totalbeginTime;
			}
			++_totalcallCount;
		}
		else
		{
			lock_guard<mutex> lock(_mtx);
			if (--_refCountMap[id] == 0)
			{
				_costTimeMap[id] += clock() - _beginTimeMap[id];
			}
			++_callCountMap[id];
		}
	}

	//<id,统计信息>多线程
	map<int, LongType> _beginTimeMap;
	map<int, LongType> _costTimeMap;
	map<int, LongType> _callCountMap;
	map<int, LongType> _refCountMap;  //引用计数，解决多线程递归问题
	//单线程
	LongType _totalbeginTime;
	LongType _totalcostTime;
	LongType _totalcallCount;
	LongType _totalRefCount;		// 引用计数，解决递归问题
	//互斥锁
	mutex _mtx;
};

struct PPNodeHash
{
	static size_t BKDRHash(const char* str)				  //哈希算法
	{
		unsigned int seed = 131; // 31 131 1313 13131 131313
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash * seed + (unsigned int)(*str++);
		}
		return (hash & 0x7FFFFFFF);
	}

	size_t operator()(const PPNode& node)const
	{
		static string hash;
		hash = node._desc;
		hash += node._function;
		return BKDRHash(hash.c_str());
	}
};

class PerformanceProfiler :public Singleton<PerformanceProfiler>
{
	typedef unordered_map<PPNode, PPSection*, PPNodeHash> PP_MAP;

public:
	PPSection* CreateSection(const char* filename, const char* function, const size_t line, const char* desc)
	{
		PPNode node(filename, function, line, desc);
		PPSection* section = NULL;

		lock_guard<mutex> lock(_mtx);
		PP_MAP::iterator it = _ppMap.find(node);
		if (it != _ppMap.end())
		{
			section = it->second;
		}
		else
		{
			section = new PPSection;
			_ppMap.insert(pair<PPNode, PPSection*>(node, section));
		}
		return section;
	}

	void OutPut()
	{
		ConsoleSaveAdapter csa;
		_OutPut(csa);

		FileSaveAdapter fsa("PerfoemanceProfilerReport.txt");
		_OutPut(fsa);
	}

protected:
	friend class Singleton<PerformanceProfiler>;

	void _OutPut(SaveAdapter& sa)
	{
		vector<PP_MAP::iterator> vInfos;
		PP_MAP::iterator ppIt = _ppMap.begin();
		while (ppIt != _ppMap.end())
		{
			PPSection* section = ppIt->second;
			map<int, LongType>::iterator timeIt;
			timeIt = section->_costTimeMap.begin();
			while (timeIt != section->_costTimeMap.end())
			{
				section->_totalcostTime += timeIt->second;
				section->_totalcallCount += section->_callCountMap[timeIt->first];

				++timeIt;
			}
			vInfos.push_back(ppIt);
			++ppIt;
		}
		struct SortByCostTime
		{
			bool operator()(PP_MAP::iterator left, PP_MAP::iterator right)const
			{
				return left->second->_totalcostTime > right->second->_totalcostTime;
			}
		};
		//花费时间由高到低排序
		sort(vInfos.begin(), vInfos.end(), SortByCostTime());
		int num = 1;
		//PP_MAP::iterator ppIt = _ppMap.begin();
		for (size_t i = 0; i < vInfos.size(); ++i)
		{
			ppIt = vInfos[i];
			const PPNode& node = ppIt->first;
			PPSection* section = ppIt->second;
			//node信息输出
			sa.Save("No.%d, Desc:%s\n", num++, node._desc.c_str());
			sa.Save("Filename:%s,Line:%d,Function:%s\n", node._filename.c_str(), node._line, node._function.c_str());

			//section信息
			map<int, LongType>::iterator timeIt;
			timeIt = section->_costTimeMap.begin();
			while (timeIt != section->_costTimeMap.end())
			{
				int id = timeIt->first;
				sa.Save("ThreadId:%d, CostTime:%.2f s, CallCount:%lld\n"
					, id
					, (double)timeIt->second / 1000
					, section->_callCountMap[id]);

				section->_totalcostTime += timeIt->second;
				section->_totalcallCount += section->_callCountMap[id];

				++timeIt;
			}

			sa.Save("TotalCostTime:%.2f s, TotalCallCount:%lld, AverCostTime:%lld ms\n\n"
				, (double)section->_totalcostTime / 1000
				, section->_totalcallCount
				, section->_totalcostTime / section->_totalcallCount);

			++ppIt;
		}
	}

	PerformanceProfiler() {};
	PerformanceProfiler(const PerformanceProfiler&);
	PerformanceProfiler& operator=(const PerformanceProfiler&);

protected:
	PP_MAP _ppMap;			 //存放资源信息
	mutex _mtx;
};

struct Report
{
	~Report()
	{
		PerformanceProfiler::GetInstance()->OutPut();
	}
};

static Report report;

static int GetThreadId()
{
#ifdef _WIN32
	return GetCurrentThreadId();
#else
	return thread_self();
#endif // _WIN32
}

//单线程
#define PERFORMANCE_PROFILER_EE_ST_BEGIN(sign,desc)\
	PPSection* ps##sign = NULL; \
if (ConfigManager::GetInstance()->GetOptions() & PERFORMANCE_PROFILER)\
{\
	ps##sign = PerformanceProfiler::GetInstance()->CreateSection(__FILE__, __FUNCTION__, __LINE__, desc); \
	ps##sign->Begin(-1); \
}


#define PERFORMANCE_PROFILER_EE_ST_END(sign)\
if (ps##sign)\
	ps##sign->End(-1);

//多线程
#define PERFORMANCE_PROFILER_EE_MT_BEGIN(sign, desc) \
	PPSection* ps##sign = NULL;						 \
if (ConfigManager::GetInstance()->GetOptions() & PERFORMANCE_PROFILER)\
{												 \
	ps##sign = PerformanceProfiler::GetInstance()->CreateSection(__FILE__, __FUNCTION__, __LINE__, desc); \
	ps##sign->Begin(GetThreadId());						 \
}

#define PERFORMANCE_PROFILER_EE_MT_END(sign)	\
if (ps##sign)								\
	ps##sign->End(GetThreadId());

#define SET_CONFIG_OPTIONS(option)\
	ConfigManager::GetInstance()->SetOptions(option);