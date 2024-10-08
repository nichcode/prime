#pragma once

#include "prime_logger.h"

#include <format>

namespace prime {

    static void assertMessage(bool expr)
    {
        if (expr) {}
        else {
            str msg = std::format("Assertion failed in '{}' at line '{}'", PFILE, PLINE);
            PERROR(msg);
            PBREAK;
        }
    }

    static void assertMessage(bool expr, const char* message)
    {
        if (expr) {}
        else {
            str msg = std::format("Assertion failed in '{}' at line '{}' \n'{}'", PFILE, PLINE, message);
            PERROR(msg);
            PBREAK;
        }
    }
}

#ifdef PCONFIG_DEBUG

#define PASSERT(expr) prime::assertMessage(expr)
#define PASSERT_MSG(expr, message) prime::assertMessage(expr, message)

#else
#define PASSERT(expr)                  
#define PASSERT_MSG(expr, message)     
#endif // PCONFIG_DEBUG 
