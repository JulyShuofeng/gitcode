#include"PerformanceProfiler.h"

void Fun(size_t n)
{
	while (n--)
	{
		PERFORMANCE_PROFILER_EE_MT_BEGIN(network, "����m");
		Sleep(100);
		PERFORMANCE_PROFILER_EE_MT_END(network);

		PERFORMANCE_PROFILER_EE_MT_BEGIN(mid, "�м��߼�m");
		Sleep(200);
		PERFORMANCE_PROFILER_EE_MT_END(mid);

		PERFORMANCE_PROFILER_EE_MT_BEGIN(sql, "���ݿ�m");
		Sleep(300);
		PERFORMANCE_PROFILER_EE_MT_END(sql);
	}
}

void TestSingleThead()
{
	PERFORMANCE_PROFILER_EE_ST_BEGIN(network, "����s");
	// ����
	Sleep(200);
	PERFORMANCE_PROFILER_EE_ST_END(network);

	PERFORMANCE_PROFILER_EE_ST_BEGIN(mid, "�м��߼�s");
	// �м��߼�
	Sleep(300);

	PERFORMANCE_PROFILER_EE_ST_END(mid);

	PERFORMANCE_PROFILER_EE_ST_BEGIN(sql, "���ݿ�s");
	// ���ݿ�
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