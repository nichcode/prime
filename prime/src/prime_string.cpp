
#include "prime/prime_string.h"
#include "prime_utils.h"
#include "prime/prime_memory.h"

#include "prime/prime_math.h"

#include <string>
#include <stdarg.h>

struct prime_String
{
	u64 length = 0;
	char* buffer = nullptr;
};

struct prime_WString
{
	u64 length = 0;
	wchar_t* buffer = nullptr;
};


// string
prime_String*
prime_CstrToString(const char* string)
{
	if (string) {
		u64 length = strlen(string);
		prime_String* str = (prime_String*)prime_MemAlloc(sizeof(prime_String));
		str->length = length;
		str->buffer = (char*)prime_MemAlloc(length + 1);
		prime_MemCopy(str->buffer, (void*)string, length);
		str->buffer[length] = 0;

		return str;
	}
	return nullptr;
}

prime_String* 
prime_CopyString(const prime_String* string)
{
	if (string) {
		u64 length = strlen(string->buffer);
		prime_String* str = (prime_String*)prime_MemAlloc(sizeof(prime_String));
		str->length = length;
		str->buffer = (char*)prime_MemAlloc(length + 1);
		prime_MemCopy(str->buffer, (void*)string->buffer, length);
		str->buffer[length] = 0;

		return str;
	}
	return nullptr;
}

prime_String* 
primeWStringToString(const prime_WString* wide_string)
{
	if (wide_string) {
		int len = prime_WideCharToMultiByte(wide_string->buffer, 0, nullptr);
		if (len == 0) {
			return nullptr;
		}

		prime_String* string = (prime_String*)prime_MemAlloc(sizeof(prime_String));
		string->length = len;
		string->buffer = (char*)prime_MemAlloc(len + 1);
		prime_WideCharToMultiByte(wide_string->buffer, len, string->buffer);
	}
	return nullptr;
}

void
prime_DestroyString(prime_String* string)
{
	if (string) {
		prime_MemFree(string->buffer, string->length + 1);
		prime_MemFree(string, sizeof(prime_String));
	}
}

const char*
prime_GetCstr(const prime_String* string)
{
	if (string) {
		return string->buffer;
	}
	return nullptr;
}

u64
prime_GetStringLength(const prime_String* string)
{
	if (string) {
		return string->length;
	}
	return 0;
}

prime_String*
prime_FormatString(const char* fmt, ...)
{
	if (!fmt) {
		return nullptr;
	}

	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	prime_String* result = prime_FormatStringWithArgs(fmt, arg_ptr);
	va_end(arg_ptr);
	return result;
}

prime_String*
prime_FormatStringWithArgs(const char* fmt, char* va_listp)
{
	if (!fmt) {
		return 0;
	}

	va_list list_copy;
	list_copy = va_listp;

	i32 length = vsnprintf(0, 0, fmt, list_copy);
	va_end(list_copy);

	prime_String* str = (prime_String*)prime_MemAlloc(sizeof(prime_String));
	if (!str) {
		return 0;
	}

	str->buffer = (char*)prime_MemAlloc(length + 1);
	str->length = length;

	vsnprintf(str->buffer, length + 1, fmt, va_listp);
	str->buffer[length] = 0;
	return str;
}


// wide string
prime_WString*
prime_CopyWString(const prime_WString* wide_string)
{
	if (wide_string) {
		prime_WString* str = (prime_WString*)prime_MemAlloc(sizeof(prime_WString));
		str->length = wide_string->length;
		str->buffer = (wchar_t*)prime_MemAlloc(wide_string->length * sizeof(wchar_t));
		prime_MemCopy(str->buffer, (void*)wide_string, wide_string->length);
		str->buffer[wide_string->length] = 0;

		return str;
	}
	return nullptr;
}

prime_WString*
prime_WstrToWString(const wchar_t* wide_string)
{
	if (wide_string) {
		u64 length = wcslen(wide_string);
		prime_WString* str = (prime_WString*)prime_MemAlloc(sizeof(prime_WString));
		str->length = length;
		str->buffer = (wchar_t*)prime_MemAlloc(length * sizeof(wchar_t));
		prime_MemCopy(str->buffer, (void*)wide_string, length);
		str->buffer[length] = 0;

		return str;
	}
	return nullptr;
}

prime_WString*
prime_StringToWString(const prime_String* string)
{
	if (string) {
		int len = prime_MultiByteToWideChar(string->buffer, 0, nullptr);
		if (len == 0) {
			return nullptr;
		}

		prime_WString* str = (prime_WString*)prime_MemAlloc(sizeof(prime_WString));
		str->length = len;

		str->buffer = (wchar_t*)prime_MemAlloc(sizeof(wchar_t) * len);
		prime_MultiByteToWideChar(string->buffer, len, str->buffer);

		return str;
	}
	return nullptr;
}

prime_WString* 
prime_CstrToWString(const char* string)
{
	if (string) {
		int len = prime_MultiByteToWideChar(string, 0, nullptr);
		if (len == 0) {
			return nullptr;
		}

		prime_WString* str = (prime_WString*)prime_MemAlloc(sizeof(prime_WString));
		str->length = len;
		str->buffer = (wchar_t*)prime_MemAlloc(len * sizeof(wchar_t));
		prime_MultiByteToWideChar(string, len, str->buffer);

		return str;
	}
	return nullptr;
}

void
prime_DestroyWString(prime_WString* wide_string)
{
	if (wide_string) {
		prime_MemFree(wide_string->buffer, wide_string->length * sizeof(wchar_t));
		prime_MemFree(wide_string, sizeof(prime_WString));
	}
}

const wchar_t*
prime_GetWstr(const prime_WString* wide_string)
{
	if (wide_string) {
		return wide_string->buffer;
	}
	return nullptr;
}

u64
prime_GetWStringLength(const prime_WString* wide_string)
{
	if (wide_string) {
		return wide_string->length;
	}
	return 0;
}

// maths
prime_String*
prime_Vec2ToString(const prime_Vec2& vec)
{
	return prime_FormatString("Vec2(%.2f, %.2f)", vec.x, vec.y);
}

prime_String*
prime_Vec3ToString(const prime_Vec3& vec)
{
	return prime_FormatString("Vec3(%.2f, %.2f, %.2f)", vec.x, vec.y, vec.z);
}

prime_String*
prime_Vec4ToString(const prime_Vec4& vec)
{
	return prime_FormatString("Vec4(%.2f, %.2f, %.2f, %.2f)", vec.x, vec.y, vec.z, vec.w);
}

prime_String*
prime_Mat4ToString(const prime_Mat4& matrix)
{
	const f32* d = matrix.data;
	prime_String* str1 = prime_FormatString("[%f %f %f %f]", d[0], d[1], d[2], d[3]);
	prime_String* str2 = prime_FormatString("[%f %f %f %f]", d[4], d[5], d[6], d[7]);
	prime_String* str3 = prime_FormatString("[%f %f %f %f]", d[8], d[9], d[10], d[11]);
	prime_String* str4 = prime_FormatString("[%f %f %f %f]", d[12], d[13], d[14], d[15]);

	prime_String* str = prime_FormatString("Mat4(%s \n\t     %s \n\t     %s \n\t     %s)",
		prime_GetCstr(str1),
		prime_GetCstr(str2),
		prime_GetCstr(str3),
		prime_GetCstr(str4));

	prime_DestroyString(str1);
	prime_DestroyString(str2);
	prime_DestroyString(str3);
	prime_DestroyString(str4);
	
	return str;
}