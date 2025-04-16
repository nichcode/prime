
#pragma once

#include "PAL_defines.h"

/// @brief Log types
enum PAL_LogLevels_
{
    PAL_LogLevels_Trace,
    PAL_LogLevels_Info,
    PAL_LogLevels_Warn,
    PAL_LogLevels_Error
};

/**
 * @brief Log a message to the console.
 * @param level The log level of the message
 * @param msg The message to log. This uses c style formatting eg.%i, %f
 */
PAL_API void PAL_Log(u32 level, const char* msg, ...);

/**
 * @brief Log a trace message to the console.
 * @param msg The message to log. This uses c style formatting eg.%i, %f
 */
PAL_API void PAL_LogTrace(const char* msg, ...);

/**
 * @brief Log a info message to the console.
 * @param msg The message to log. This uses c style formatting eg.%i, %f
 */
PAL_API void PAL_LogInfo(const char* msg, ...);

/**
 * @brief Log a warn message to the console.
 * @param msg The message to log. This uses c style formatting eg.%i, %f
 */
PAL_API void PAL_LogWarn(const char* msg, ...);

/**
 * @brief Log a error message to the console.
 * @param msg The message to log. This uses c style formatting eg.%i, %f
 */
PAL_API void PAL_LogError(const char* msg, ...);

/**
 * @brief Assert an expresion to check if it failed. this triggers a breakpoint.
 * @param expr The expr.
 * @param file The file.
 * @param line The line number.
 * @param msg The message to log. This uses c style formatting eg.%i, %f
 */
PAL_API void PAL_Assert(b8 expr, const char* file, u32 line, const char* msg, ...);

#ifdef PAL_CONFIG_DEBUG
#define PAL_TRACE(...)                    PAL_LogTrace(__VA_ARGS__)
#define PAL_INFO(...)                     PAL_LogInfo(__VA_ARGS__)
#define PAL_WARN(...)                     PAL_LogWarn(__VA_ARGS__)
#define PAL_ERROR(...)                    PAL_LogError(__VA_ARGS__)
#define PAL_ASSERT(expr, ...)             PAL_Assert(expr, PAL_FILE, PAL_LINE, __VA_ARGS__)
#else
#define PAL_TRACE(...)                
#define PAL_INFO(...)         
#define PAL_WARN(...)          
#define PAL_ERROR(...)               
#define PAL_ASSERT(expr, ...)
#endif // PAL_CONFIG_DEBUG