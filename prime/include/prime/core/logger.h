
#pragma once

#include "prime/defines.h"

namespace prime::core {

    class Logger
    {
    public:
        static void log(LogLevel level, const char* msg, ...);

        static void log(LogLevel level, const str& msg, ...)
        {
            log(level, msg.c_str());
        }

        static void trace(const char* msg)
        {
            log(LogLevelTrace, msg);
        }

        static void trace(const str& msg)
        {
            log(LogLevelTrace, msg);
        }

        static void info(const char* msg)
        {
            log(LogLevelInfo, msg);
        }

        static void info(const str& msg)
        {
            log(LogLevelInfo, msg);
        }

        static void warn(const char* msg)
        {
            log(LogLevelWarn, msg);
        }

        static void warn(const str& msg)
        {
            log(LogLevelWarn, msg);
        }

        static void error(const char* msg)
        {
            log(LogLevelError, msg);
        }

        static void error(const str& msg)
        {
            log(LogLevelError, msg);
        }

        static void assertion(bool expr, const char* file, u32 line);
        static void assertion(bool expr, const char* file, u32 line, const char* message);

        static void assertion(bool expr, const char* file, u32 line, const str& message)
        {
            assertion(expr, file, line, message.c_str());
        }
    };
    
} // namespace prime::core


#ifdef PRIME_CONFIG_DEBUG
#define PRIME_TRACE(message)                prime::core::Logger::trace(message)
#define PRIME_INFO(message)                 prime::core::Logger::info(message)
#define PRIME_WARN(message)                 prime::core::Logger::warn(message)
#define PRIME_ERROR(message)                prime::core::Logger::error(message)
#define PRIME_ASSERT(expr)                  prime::core::Logger::assertion(expr, PRIME_FILE, PRIME_LINE)
#define PRIME_ASSERT_MSG(expr, message)     prime::core::Logger::assertion(expr, PRIME_FILE, PRIME_LINE, message)
#else
#define PRIME_TRACE(message)         
#define PRIME_DEBUG(message)         
#define PRIME_INFO(message)         
#define PRIME_WARN(message)          
#define PRIME_ERROR(message)               
#define PRIME_ASSERT(expr)
#define PRIME_ASSERT_MSG(expr, message)
#endif // PRIME_CONFIG_DEBUG