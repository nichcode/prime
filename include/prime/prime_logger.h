#pragma once

#include "prime_defines.h"

#include <iostream>

namespace prime {

	enum LogTypes : u8
	{
		LogTypesNone,
		LogTypesTrace,
		LogTypesDebug,
		LogTypesInfo,
		LogTypesWarn,
		LogTypesError,
		LogTypesCritical,

		LogTypesMax
	};

	class Logger
	{
	private:
		static void SetLevel(u8 logType);

	public:
		template<typename Type>
		static void Log(u8 logType, const Type& msg)
		{
			SetLevel(logType);
			std::cout << msg << std::endl;
			SetLevel(LogTypesNone);
		}
	};
}

#ifdef PCONFIG_DEBUG
#define PTRACE(...)         prime::Logger::Log(prime::LogTypesTrace,    __VA_ARGS__)
#define PDEBUG(...)         prime::Logger::Log(prime::LogTypesDebug,    __VA_ARGS__)
#define PINFO(...)          prime::Logger::Log(prime::LogTypesInfo,     __VA_ARGS__)
#define PWARN(...)          prime::Logger::Log(prime::LogTypesWarn,     __VA_ARGS__)
#define PERROR(...)         prime::Logger::Log(prime::LogTypesError,    __VA_ARGS__)
#define PFATAL(...)         prime::Logger::Log(prime::LogTypesCritical, __VA_ARGS__)
#else
#define PTRACE(...)         
#define PDEBUG(...)         
#define PINFO(...)          
#define PWARN(...)          
#define PERROR(...)         
#define PFATAL(...)         
#endif // PCONFIG_DEBUG
