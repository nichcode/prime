
#include "prime/prime_logger.h"
#include "prime/prime_time.h"

#ifdef PPLATFORM_WINDOWS
#include <Windows.h>

namespace prime {

	static f64 s_ClockFrequency;
	static LARGE_INTEGER s_StartTime;

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
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		s_ClockFrequency = 1.0 / (f64)frequency.QuadPart;
		QueryPerformanceCounter(&s_StartTime);
	}

	f64 Time::Get()
	{
		LARGE_INTEGER now_time;
		QueryPerformanceCounter(&now_time);
		return (f64)now_time.QuadPart * (f64)s_ClockFrequency;
	}

	void Time::SetSleep(f64 miliSeconds)
	{
		Sleep((DWORD)miliSeconds);
	}
}

#endif // PPLATFORM_WINDOWS