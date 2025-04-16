
#pragma once

#include "defines.h"

/// @brief Log types
enum prLogLevels_
{
    prLogLevels_Trace,
    prLogLevels_Info,
    prLogLevels_Warn,
    prLogLevels_Error
};

/**
 * @brief Log a message to the console.
 * @param level The log level of the message
 * @param msg The message to log. This uses c style formatting eg.%i, %f
 */
PR_API void prLog(u32 level, const char* msg, ...);

/**
 * @brief Log a trace message to the console.
 * @param msg The message to log. This uses c style formatting eg.%i, %f
 */
PR_API void prLogTrace(const char* msg, ...);

/**
 * @brief Log a info message to the console.
 * @param msg The message to log. This uses c style formatting eg.%i, %f
 */
PR_API void prLogInfo(const char* msg, ...);

/**
 * @brief Log a warn message to the console.
 * @param msg The message to log. This uses c style formatting eg.%i, %f
 */
PR_API void prLogWarn(const char* msg, ...);

/**
 * @brief Log a error message to the console.
 * @param msg The message to log. This uses c style formatting eg.%i, %f
 */
PR_API void prLogError(const char* msg, ...);

/**
 * @brief Assert an expresion to check if it failed. this triggers a breakpoint.
 * @param expr The expr.
 * @param file The file.
 * @param line The line number.
 * @param msg The message to log. This uses c style formatting eg.%i, %f
 */
PR_API void prAssert(b8 expr, const char* file, u32 line, const char* msg, ...);

#ifdef PR_CONFIG_DEBUG
#define PR_TRACE(...)                    prLogTrace(__VA_ARGS__)
#define PR_INFO(...)                     prLogInfo(__VA_ARGS__)
#define PR_WARN(...)                     prLogWarn(__VA_ARGS__)
#define PR_ERROR(...)                    prLogError(__VA_ARGS__)
#define PR_ASSERT(expr, ...)             prAssert(expr, PR_FILE, PR_LINE, __VA_ARGS__)
#else
#define PR_TRACE(...)                
#define PR_INFO(...)         
#define PR_WARN(...)          
#define PR_ERROR(...)               
#define PR_ASSERT(expr, ...)
#endif // PR_CONFIG_DEBUG