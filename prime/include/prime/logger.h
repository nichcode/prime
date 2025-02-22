
#pragma once

#include "defines.h"

namespace prime {

    enum class LogLevel
    {
        Trace,
        Info,
        Warn,
        Error
    };

    class Logger
    {
    private:
        static void 
        setLevel(LogLevel level, b8 reset =false);

    public:
        static void 
        log(LogLevel level, const char* message);

        PINLINE static void 
        trace(const char* message)
        {
            log(LogLevel::Trace, message);
        }

        PINLINE static void 
        info(const char* message)
        {
            log(LogLevel::Info, message);
        }

        PINLINE static void 
        warn(const char* message)
        {
            log(LogLevel::Warn, message);
        }

        PINLINE static void 
        error(const char* message)
        {
            log(LogLevel::Error, message);
        }

        static void 
        assert(bool expr, const char* file, u32 line);

        static void 
        assert(bool expr, const char* file, u32 line, const char* message);
    };

} // namespace prime

#ifdef PCONFIG_DEBUG
#define PTRACE(message, ...)           prime::Logger::trace(message)
#define PINFO(message, ...)            prime::Logger::info(message)
#define PWARN(message, ...)            prime::Logger::warn(message)
#define PERROR(message, ...)           prime::Logger::error(message)
#define PASSERT(expr)                  prime::Logger::assert(expr, PFILE, PLINE)
#define PASSERT_MSG(expr, message)     prime::Logger::assert(expr, PFILE, PLINE, message)
#else
#define PTRACE(message, ...)         
#define PDEBUG(message, ...)               
#define PINFO(message, ...)                
#define PWARN(message, ...)          
#define PERROR(message, ...)         
#define PASSERT(expr)
#define PASSERT_MSG(expr, message)
#endif // PCONFIG_DEBUG;