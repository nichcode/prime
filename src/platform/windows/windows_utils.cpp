
#include "prime/prime_logger.h"

#ifdef PPLATFORM_WINDOWS
#include <Windows.h>

namespace prime {

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
}

#endif // PPLATFORM_WINDOWS