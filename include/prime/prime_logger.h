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
	    
		// @brief Log a message and display it on the console.
		// @tparam Type The type of the message ie. string, float, int etc. This is set internally.
		// @param logType The log type of the message.
		// @param msg The message or the object to log.
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

// @brief Log a trace type message only in debug builds or if PCONFIG_DEBUG is defined.
#define PTRACE(...)         prime::Logger::Log(prime::LogTypesTrace,    __VA_ARGS__)

// @brief Log a debug type message only in debug builds or if PCONFIG_DEBUG is defined.
#define PDEBUG(...)         prime::Logger::Log(prime::LogTypesDebug,    __VA_ARGS__)

// @brief Log a info type message only in debug builds or if PCONFIG_DEBUG is defined.
#define PINFO(...)          prime::Logger::Log(prime::LogTypesInfo,     __VA_ARGS__)

// @brief Log a warn type message only in debug builds or if PCONFIG_DEBUG is defined.
#define PWARN(...)          prime::Logger::Log(prime::LogTypesWarn,     __VA_ARGS__)

// @brief Log a error type message only in debug builds or if PCONFIG_DEBUG is defined.
#define PERROR(...)         prime::Logger::Log(prime::LogTypesError,    __VA_ARGS__)

// @brief Log a fatal type message only in debug builds or if PCONFIG_DEBUG is defined.
#define PFATAL(...)         prime::Logger::Log(prime::LogTypesCritical, __VA_ARGS__)

#else

// @brief Log a trace type message only in debug builds or if PCONFIG_DEBUG is defined.
#define PTRACE(...)         

// @brief Log a debug type message only in debug builds or if PCONFIG_DEBUG is defined.
#define PDEBUG(...)         

// @brief Log a info type message only in debug builds or if PCONFIG_DEBUG is defined.
#define PINFO(...)          

// @brief Log a warn type message only in debug builds or if PCONFIG_DEBUG is defined.
#define PWARN(...)          

// @brief Log a error type message only in debug builds or if PCONFIG_DEBUG is defined.
#define PERROR(...)         

// @brief Log a fatal type message only in debug builds or if PCONFIG_DEBUG is defined.
#define PFATAL(...)         

#endif // PCONFIG_DEBUG
