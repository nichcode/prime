
#include "prime/logger.h"
#include "prime/utils.h"

#include <iostream>

namespace prime {

    static const char* levels[4] = { "[TRACE]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: " };

    void 
    Logger::log(LogLevel level, const char* message)
    {
        setLevel(level);
        str msg = Utils::format("%s%s\n", levels[(u32)level], message);
        std::cout << msg;
        setLevel(level, true);
    }

    void 
    Logger::assertion(bool expr, const char* file, u32 line)
    {
        if (expr) {}
        else {
            str str = Utils::format("Assertion failed in '%s' at line '%i'", file, line);
            log(LogLevel::Error, str.c_str());
            PBREAK;
        }
    }

    void 
    Logger::assertion(bool expr, const char* file, u32 line, const char* message)
    {
        if (expr) {}
        else {
            str str = Utils::format("Assertion failed in '%s' at line '%i' \n'%s'", file, line, message);
            log(LogLevel::Error, str.c_str());
            PBREAK;
	    }

    }

} // namespace prime
