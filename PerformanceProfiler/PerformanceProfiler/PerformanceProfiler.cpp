#include"PerformanceProfiler.h"

void Fun(size_t n)
{
	while (n--)
	{
		PERFORMANCE_PROFILER_EE_MT_BEGIN(network, "网络m");
		Sleep(100);
		PERFORMANCE_PROFILER_EE_MT_END(network);

		PERFORMANCE_PROFILER_EE_MT_BEGIN(mid, "中间逻辑m");
		Sleep(200);
		PERFORMANCE_PROFILER_EE_MT_END(mid);

		PERFORMANCE_PROFILER_EE_MT_BEGIN(sql, "数据库m");
		Sleep(300);
		PERFORMANCE_PROFILER_EE_MT_END(sql);
	}
}

void TestSingleThead()
{
	PERFORMANCE_PROFILER_EE_ST_BEGIN(network, "网络s");
	// 网络
	Sleep(200);
	PERFORMANCE_PROFILER_EE_ST_END(network);

	PERFORMANCE_PROFILER_EE_ST_BEGIN(mid, "中间逻辑s");
	// 中间逻辑
	Sleep(300);

	PERFORMANCE_PROFILER_EE_ST_END(mid);

	PERFORMANCE_PROFILER_EE_ST_BEGIN(sql, "数据库s");
	// 数据库
	Sleep(400);

	PERFORMANCE_PROFILER_EE_ST_END(sql);
}

void TestMultiThread()
{
	thread t1(Fun, 5);
	thread t2(Fun, 4);
	thread t3(Fun, 3);

	t1.join();
	t2.join();
	t3.join();
}

int main()
{
	SET_CONFIG_OPTIONS(PERFORMANCE_PROFILER
		| SAVE_TO_FILE
		| SAVE_TO_CONSOLE
		| SORT_BY_COSTTIME);
	TestSingleThead();
	TestMultiThread();
	return 0;
}