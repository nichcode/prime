#pragma once

#include "logger.h"

#include <format>

namespace prime {

    /**
     * @brief Check to see if an expression is true or false.
     * if the expression is true it does nothing else its triggers a
     * breakpoint printing out the line number and the file name to the console.
     * 
     * @param expr The expression to check.
     */
    static void assert_expr(bool expr)
    {
        if (expr) {}
        else {
            str msg = std::format("Assertion failed in '{}' at line '{}'", PFILE, PLINE);
            prime::Logger::log(prime::LogTypesError, msg);
            PBREAK;
        }
    }

    /**
     * @brief Check to see if an expression is true or false.
     * if the expression is true it does nothing else its triggers a
     * breakpoint printing out the line number, file name and the message to the console.
     * 
     * @param expr the expression to check.
     * @param message the message to printout.
     */
    static void assert_expr_msg(bool expr, const char* message)
    {
        if (expr) {}
        else {
            str msg = std::format("Assertion failed in '{}' at line '{}' \n'{}'", PFILE, PLINE, message);
            prime::Logger::log(prime::LogTypesError, msg);
            PBREAK;
        }
    }
}

#ifdef PCONFIG_DEBUG

#define PASSERT(expr) prime::assert_expr(expr)
#define PASSERT_MSG(expr, message) prime::assert_expr_msg(expr, message)

#else
#define PASSERT(expr) 
#define PASSERT_MSG(expr, message) 

#endif // PCONFIG_DEBUG 
