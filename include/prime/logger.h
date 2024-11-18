#pragma once

#include "defines.h"

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
		static void set_level(u8 log_type);

	public:
	    
		// @brief Log a message and display it on the console.
		// @tparam Type The type of the message ie. string, float, int etc. This is set internally.
		// @param log_type The log type of the message.
		// @param msg The message or the object to log.
		template<typename Type>
		static void log(u8 log_type, const Type& msg)
		{
			set_level(log_type);
			std::cout << msg << std::endl;
			set_level(LogTypesNone);
		}
	};
}

#ifdef PCONFIG_DEBUG

#define PTRACE(...)         prime::Logger::log(prime::LogTypesTrace,    __VA_ARGS__)
#define PDEBUG(...)         prime::Logger::log(prime::LogTypesDebug,    __VA_ARGS__)
#define PINFO(...)          prime::Logger::log(prime::LogTypesInfo,     __VA_ARGS__)
#define PWARN(...)          prime::Logger::log(prime::LogTypesWarn,     __VA_ARGS__)
#define PERROR(...)         prime::Logger::log(prime::LogTypesError,    __VA_ARGS__)
#define PFATAL(...)         prime::Logger::log(prime::LogTypesCritical, __VA_ARGS__)

#else

#define PTRACE(...)         
#define PDEBUG(...)         
#define PINFO(...)          
#define PWARN(...)          
#define PERROR(...)         
#define PFATAL(...)         

#endif // PCONFIG_DEBUG
