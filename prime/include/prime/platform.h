
#pragma once

#include "defines.h"
#include "log.h"
#include <stdarg.h>

/**
 * @brief Initialize the library.
 * @param font The font to query its baseline
 * @returns If successful, true otherwise false.
 */
PR_API b8 prInit();

/**
 * @brief Shutdown the library.
 */
PR_API void prShutdown();

/**
 * @brief format a c style string. 
 * The string is dynamically allocated so the user should delete it with prFreeString.
 * @param fmt The format string. This uses c style formatting eg.%i, %f
 * @returns If successful, a pointer to the string true otherwise nullptr.
 */
PR_API char* prFormat(const char* fmt, ...);

/**
 * @brief format a c style string with args. 
 * The string is dynamically allocated so the user should delete it with prFreeString.
 * @param fmt The format string. This uses c style formatting eg.%i, %f
 * @param args_list The args_list.
 * @returns If successful, a pointer to the string true otherwise nullptr.
 */
PR_API char* prFormatArgs(const char* fmt, va_list args_list);

/**
 * @brief format a c style wide string into a c style string 
 * The string is dynamically allocated so the user should delete it with prFreeString.
 * @param wstring The wide string
 * @returns If successful, a pointer to the string true otherwise nullptr.
 */
PR_API char* prToString(const wchar_t* wstring);

/**
 * @brief format a c style string into a c style wide string 
 * The string is dynamically allocated so the user should delete it with prFreeString.
 * @param string The string
 * @returns If successful, a pointer to the wide string true otherwise nullptr.
 */
PR_API wchar_t* prToWstring(const char* string);

/**
 * @brief Free a dynamically allocated c style string.
 * @param string The string
 */
PR_API void prFreeString(char* string);

/**
 * @brief Free a dynamically allocated c style wide string.
 * @param wstring The wide string
 */
PR_API void prFreeWstring(wchar_t* wstring);

/**
 * @brief Load a dynamic library from disk.
 * @param dll The filepath
 */
PR_API void* prLoadLibrary(const char* dll);

/**
 * @brief Load a function proc from a dynamic library..
 * @param dll The dynamic library
 * @param func_name The name of the function proc.
 * @returns If successful, a pointer to the proc otherwise nullptr.
 */
PR_API void* prLoadProc(void* dll, const char* func_name);

/**
 * @brief Free a dynamic library.
 * @param dll The dynamic library
 */
PR_API void prFreeLibrary(void* dll);

/**
 * @brief Set user data pointer.
 * @param data The data pointer
 */
PR_API void prSetUserData(void* data);

/**
 * @brief Get user data pointer.
 * @returns The data pointer
 */
PR_API void* prGetUserData();
