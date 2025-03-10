
#include "prime/core/logger.h"
#include "prime/core/fmt.h"
#include "prime_utils.h"
#include <stdarg.h>

namespace prime::core {

    static const char* levels[4] = { "[TRACE]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: " };

    void Logger::log(LogLevel level, const char* msg, ...)
    {
        va_list arg_ptr;
        va_start(arg_ptr, msg);
        str formatted = format(msg, arg_ptr);
        va_end(arg_ptr);
        str out_msg = format("%s%s\n", levels[level], formatted.c_str());
        utils::consoleWrite(level, out_msg.c_str());
    }

    void Logger::assertion(bool expr, const char* file, u32 line)
    {
        if (expr) {}
        else {
            str msg = format("Assertion failed in '%s' at line '%i'", file, line);
            error(msg);
            PRIME_BREAK;
        }
    }

    void Logger::assertion(bool expr, const char* file, u32 line, const char* message)
    {
        if (expr) {}
        else {
            str msg = format("Assertion failed in '%s' at line '%i' \n'%s'", file, line, message);
            error(msg);
            PRIME_BREAK;
        }
    }

} // namespace prime::core