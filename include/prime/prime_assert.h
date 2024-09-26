#pragma once

#include "prime_logger.h"

#include <format>

namespace prime {

    /**
     * @brief Check an expression to see if its true or false.
     * if the expression is true it does nothing else its triggers a
     * breakpoint printing out the line number and the file name to the console.
     * 
     * @param expr the expression to check.
     */
    static void AssertExpr(bool expr)
    {
        if (expr) {}
        else {
            str msg = std::format("Assertion failed in '{}' at line '{}'", PFILE, PLINE);
            prime::Logger::Log(prime::LogTypesError, msg);
            PBREAK;
        }
    }

    /**
     * @brief Check an expression to see if its true or false.
     * if the expression is true it does nothing else its triggers a
     * breakpoint printing out the line number, file name and the message to the console.
     * 
     * @param expr the expression to check.
     * @param message the message to printout.
     */
    static void AssertExprMessage(bool expr, const char* message)
    {
        if (expr) {}
        else {
            str msg = std::format("Assertion failed in '{}' at line '{}' \n'{}'", PFILE, PLINE, message);
            prime::Logger::Log(prime::LogTypesError, msg);
            PBREAK;
        }
    }
}

#ifdef PCONFIG_DEBUG
    /**
     * @brief Check an expression to see if its true or false.
     * if the expression is true it does nothing else its triggers a
     * breakpoint printing out the line number and file name to the console.
     * This only works on debug build or PCONFIG_DEBUG is defines.
     * 
     * @param expr the expression to check.
     */
#define PASSERT(expr) prime::AssertExpr(expr)

    /**
     * @brief Check an expression to see if its true or false.
     * if the expression is true it does nothing else its triggers a
     * breakpoint printing out the line number, file name and the message to the console.
     * This only works on debug build or PCONFIG_DEBUG is defines.
     * 
     * @param expr the expression to check.
     * @param message the message to printout.
     */
#define PASSERT_MSG(expr, message) prime::AssertExprMessage(expr, message)

#else
    /**
     * @brief Check an expression to see if its true or false.
     * if the expression is true it does nothing else its triggers a
     * breakpoint printing out the line number and file name to the console.
     * This only works on debug build or PCONFIG_DEBUG is defines.
     * 
     * @param expr the expression to check.
     */
#define PASSERT(expr) 

    /**
     * @brief Check an expression to see if its true or false.
     * if the expression is true it does nothing else its triggers a
     * breakpoint printing out the line number, file name and the message to the console.
     * This only works on debug build or PCONFIG_DEBUG is defines.
     * 
     * @param expr the expression to check.
     * @param message the message to printout.
     */
#define PASSERT_MSG(expr, message) 

#endif // PCONFIG_DEBUG 
