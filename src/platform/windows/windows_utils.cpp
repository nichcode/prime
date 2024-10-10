
#include "prime/prime_logger.h"
#include "prime/prime_time.h"

#ifdef PPLATFORM_WINDOWS
#include <Windows.h>

namespace prime {

	static u64 s_clockFrequency;
	static u64 s_startTime;

	void Logger::SetLevel(u8 logType)
	{
		HANDLE consoleHandle;
		const u8 logLevels[LogTypesMax] = { 15, 8, 1, 2, 6, 4, 64 };
		u8 level = logLevels[logType];

		b8 error = level > LogTypesWarn;
		if (error) {
			consoleHandle = GetStdHandle(STD_ERROR_HANDLE);
		}
		else {
			consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		SetConsoleTextAttribute(consoleHandle, level);
	}

	void Time::Init()
	{
		QueryPerformanceFrequency((LARGE_INTEGER*)& s_clockFrequency);
		QueryPerformanceCounter((LARGE_INTEGER*)&s_startTime);
	}

	f64 Time::Get()
	{
		u64 time;
		QueryPerformanceCounter((LARGE_INTEGER*)&time);
		return (f64)(time - s_startTime) / s_clockFrequency;
	}

	void Time::SetSleep(f64 miliSeconds)
	{
		Sleep((DWORD)miliSeconds);
	}
}

#endif // PPLATFORM_WINDOWS