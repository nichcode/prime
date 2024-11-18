
#include "prime/logger.h"
#include "prime/time.h"

#ifdef PPLATFORM_WINDOWS
#include <Windows.h>

namespace prime {

	static u64 s_clock_frequency;
	static u64 s_start_time;

	void Logger::set_level(u8 log_type)
	{
		HANDLE console_handle;
		const u8 log_levels[LogTypesMax] = { 15, 8, 1, 2, 6, 4, 64 };
		u8 level = log_levels[log_type];

		b8 error = level > LogTypesWarn;
		if (error) {
			console_handle = GetStdHandle(STD_ERROR_HANDLE);
		}
		else {
			console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		SetConsoleTextAttribute(console_handle, level);
	}

	void Time::init()
	{
		QueryPerformanceFrequency((LARGE_INTEGER*)& s_clock_frequency);
		QueryPerformanceCounter((LARGE_INTEGER*)&s_start_time);
	}

	f64 Time::get()
	{
		u64 time;
		QueryPerformanceCounter((LARGE_INTEGER*)&time);
		return (f64)(time - s_start_time) / s_clock_frequency;
	}

	void Time::sleep(f64 milli_seconds)
	{
		Sleep((DWORD)milli_seconds);
	}
}

#endif // PPLATFORM_WINDOWS