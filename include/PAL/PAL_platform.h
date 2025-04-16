
#pragma once

#include "PAL_defines.h"
#include "PAL_log.h"
#include <stdarg.h>

/**
 * @brief Initialize the library.
 * @param font The font to query its baseline
 * @returns If successful, true otherwise false.
 */
PAL_API b8 PAL_Init();

/**
 * @brief Shutdown the library.
 */
PAL_API void PAL_Shutdown();

/**
 * @brief format a c style string. 
 * The string is dynamically allocated so the user should delete it with PAL_FreeString.
 * @param fmt The format string. This uses c style formatting eg.%i, %f
 * @returns If successful, a pointer to the string true otherwise nullptr.
 */
PAL_API char* PAL_Format(const char* fmt, ...);

/**
 * @brief format a c style string with args. 
 * The string is dynamically allocated so the user should delete it with PAL_FreeString.
 * @param fmt The format string. This uses c style formatting eg.%i, %f
 * @param args_list The args_list.
 * @returns If successful, a pointer to the string true otherwise nullptr.
 */
PAL_API char* PAL_FormatArgs(const char* fmt, va_list args_list);

/**
 * @brief format a c style wide string into a c style string 
 * The string is dynamically allocated so the user should delete it with PAL_FreeString.
 * @param wstring The wide string
 * @returns If successful, a pointer to the string true otherwise nullptr.
 */
PAL_API char* PAL_ToString(const wchar_t* wstring);

/**
 * @brief format a c style string into a c style wide string 
 * The string is dynamically allocated so the user should delete it with PAL_FreeString.
 * @param string The string
 * @returns If successful, a pointer to the wide string true otherwise nullptr.
 */
PAL_API wchar_t* PAL_ToWstring(const char* string);

/**
 * @brief Free a dynamically allocated c style string.
 * @param string The string
 */
PAL_API void PAL_FreeString(char* string);

/**
 * @brief Free a dynamically allocated c style wide string.
 * @param wstring The wide string
 */
PAL_API void PAL_FreeWstring(wchar_t* wstring);

/**
 * @brief Load a dynamic library from disk.
 * @param dll The filepath
 */
PAL_API void* PAL_LoadLibrary(const char* dll);

/**
 * @brief Load a function PAL_oc from a dynamic library..
 * @param dll The dynamic library
 * @param func_name The name of the function PAL_oc.
 * @returns If successful, a pointer to the PAL_oc otherwise nullptr.
 */
PAL_API void* PAL_LoadPAL_oc(void* dll, const char* func_name);

/**
 * @brief Free a dynamic library.
 * @param dll The dynamic library
 */
PAL_API void PAL_FreeLibrary(void* dll);

/**
 * @brief Set user data pointer.
 * @param data The data pointer
 */
PAL_API void PAL_SetUserData(void* data);

/**
 * @brief Get user data pointer.
 * @returns The data pointer
 */
PAL_API void* PAL_GetUserData();
