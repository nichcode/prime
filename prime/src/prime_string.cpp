
#include "prime/prime_string.h"
#include "prime/prime_memory.h"
#include "prime_utils.h"

#include <string.h>
#include <stdio.h>

char*
prime_StringDuplicate(const char* string)
{
	PASSERT_MSG(string, "string is null");
	u64 length = strlen(string);
	char* buffer = nullptr;
	if (s_Allocator) {}
	else {
		buffer = (char*)prime_MemoryAlloc(length + 1);
	}
	PASSERT_MSG(buffer, "string buffer failed to allocate");
	prime_MemoryCopy(buffer, (void*)string, length);
	buffer[length] = 0;
	return buffer;
}

void
prime_StringCopy(char* dest_string, const char* src_string)
{
	PASSERT_MSG(dest_string, "dest_string is null");
	PASSERT_MSG(dest_string, "src_string is null");
	strcpy(dest_string, src_string);
}

void
prime_StringNcopy(char* dest_string, const char* src_string, u64 length)
{
	PASSERT_MSG(dest_string, "dest_string is null");
	PASSERT_MSG(src_string, "src_string is null");
	strncpy(dest_string, src_string, length);
}

void
prime_StringFree(char* string)
{
	PASSERT_MSG(string, "string is null");
	u64 length = strlen(string);
	if (s_Allocator) {}
	else {
		prime_MemoryFree(string, length + 1);
	}
}

u64
prime_StringGetLength(const char* string)
{
	PASSERT_MSG(string, "string is null");
	return strlen(string);
}

char*
prime_StringAdd(const char* string1, const char* string2)
{
	PASSERT_MSG(string1, "string1 is null");
	PASSERT_MSG(string2, "string2 is null");
	u64 len = strlen(string1) + strlen(string2);
	char* result = nullptr;
	if (s_Allocator) {}
	else {
		result = (char*)prime_MemoryAlloc(len + 1);
	}
	
	PASSERT_MSG(result, "buffer allocation failed");
	strcat(result, string1);
	strcat(result, string2);
	return result;
}

char*
prime_StringFormatArgs(const char* fmt, va_list args_list)
{
	PASSERT_MSG(fmt, "fmt is null");
	va_list list_copy;

#ifdef _MSC_VER
	list_copy = args_list;
#elif defined(P_PLATFORM_APPLE)
	list_copy = args_list;
#else
	__builtin_va_copy(list_copy, args_list);
#endif

	i32 length = vsnprintf(0, 0, fmt, list_copy);
	va_end(list_copy);

	char* result = nullptr;
	if (s_Allocator) {}
	else {
		result = (char*)prime_MemoryAlloc(length + 1);
	}

	PASSERT_MSG(result, "buffer allocation failed");
	vsnprintf(result, length + 1, fmt, args_list);
	result[length] = 0;
	return result;
}

char*
prime_StringFormat(const char* fmt, ...)
{
	PASSERT_MSG(fmt, "fmt is null");
	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	char* result = prime_StringFormatArgs(fmt, arg_ptr);
	PASSERT_MSG(result, "buffer allocation failed");
	va_end(arg_ptr);
	return result;
}

b8
prime_StringEqual(const char* string1, const char* string2, b8 case_sensitive)
{
	PASSERT_MSG(string1, "string1 is null");
	PASSERT_MSG(string2, "string2 is null");
	if (case_sensitive) {
		return strcmp(string1, string2) == 0;
	}
	else {
#if defined(__GNUC__)
		return strcasecmp(string1, string2) == 0;
#elif (defined _MSC_VER)
		return _strcmpi(string1, string2) == 0;
#endif
	}
}

b8
prime_StringEmpty(const char* string)
{
	PASSERT_MSG(string, "string is null");
	if (string[0] == 0) {
		return true;
	}
	else {
		return false;
	}
	return true;
}

void
prime_StringClear(char* string)
{
	PASSERT_MSG(string, "string is null");
	string[0] = 0;
}

i32
prime_StringGetIndex(const char* string1, const char* string2)
{
	PASSERT_MSG(string1, "string1 is null");
	PASSERT_MSG(string2, "string2 is null");
	u64 length = strlen(string1);
	u64 length2 = strlen(string2);
	const char* a = string1;
	const char* b = string2;
	if (length2 > length) {
		u64 temp = length;
		length = length2;
		length2 = temp;
		a = string2;
		b = string1;
	}
	if (length > 0 && length2 > 0) {
		for (u32 i = 0; i < length; ++i) {
			if (a[i] == b[0]) {
				u32 start = i;
				b8 keep_looking = false;
				for (u32 j = 0; j < length2; ++j) {
					if (a[i + j] != b[j]) {
						keep_looking = true;
						break;
					}
				}
				if (!keep_looking) {
					return start;
				}
			}
		}
	}

	return -1;
}

void
prime_StringInsert(char* dest_string, const char* src_string, u32 pos, const char* string)
{
	PASSERT_MSG(dest_string, "dest_string is null");
	PASSERT_MSG(src_string, "src_string is null");
	u64 src_len = strlen(src_string);
	u64 len = strlen(string);
	u64 remaining = src_len - pos;

	if (pos > 0) {
		prime_MemoryCopy((void*)dest_string, (void*)src_string, pos);
	}
	if (pos < src_len) {
		prime_MemoryCopy((void*)(dest_string + pos + len), (void*)(src_string + pos), (u32)remaining);
	}
	prime_MemoryCopy((void*)(dest_string + pos), (void*)string, len);
}

char* 
prime_StringInsertAlloc(const char* src_string, u32 pos, const char* string)
{
	PASSERT_MSG(src_string, "src_string is null");
	u64 src_len = strlen(src_string);
	u64 len = strlen(string);
	u64 remaining = src_len - pos;

	char* dest_string = nullptr;
	if (s_Allocator) {}
	else {
		dest_string = (char*)prime_MemoryAlloc(src_len + len + 1);
	}

	PASSERT_MSG(src_string, "buffer allocation failed");
	if (pos > 0) {
		prime_MemoryCopy((void*)dest_string, (void*)src_string, pos);
	}
	if (pos < src_len) {
		prime_MemoryCopy((void*)(dest_string + pos + len), (void*)(src_string + pos), (u32)remaining);
	}
	prime_MemoryCopy((void*)(dest_string + pos), (void*)string, len);
	return dest_string;
}

void
prime_StringAssign(char* string, u32 pos, char c)
{
	PASSERT_MSG(string, "string is null");
	PASSERT_MSG(pos < strlen(string), "pos out of bounds");
	string[pos] = c;
}

void
prime_StringRemove(char* dest_string, const char* src_string, u32 pos, u32 length)
{
	PASSERT_MSG(dest_string, "dest_string is null");
	PASSERT_MSG(src_string, "src_string is null");
	u64 original_length = strlen(src_string);
	u64 remaining = original_length - pos - length;
	if (pos > 0) {
		prime_MemoryCopy((void*)dest_string, (void*)src_string, pos);
	}

	if (pos < original_length) {
		prime_MemoryCopy((void*)(dest_string + pos), (void*)(src_string + pos + length), (u32)remaining);
	}
	dest_string[original_length - length] = 0;
}

char*
prime_F32ToString(f32 num)
{
	char* result = prime_StringFormat("%.2f", num);
	return result;
}

char*
prime_F64ToString(f64 num)
{
	char* result = prime_StringFormat("%.2f", num);
	return result;
}

char*
prime_U8ToString(u8 num)
{
	char* result = prime_StringFormat("%hhu", num);
	return result;
}

char*
prime_U16ToString(u16 num)
{
	char* result = prime_StringFormat("%hu", num);
	return result;
}

char*
prime_U32ToString(u32 num)
{
	char* result = prime_StringFormat("%u", num);
	return result;
}

char*
prime_U64ToString(u64 num)
{
	char* result = prime_StringFormat("%llu", num);
	return result;
}

char*
prime_I8ToString(i8 num)
{
	char* result = prime_StringFormat("%hhi", num);
	return result;
}

char*
prime_I16ToString(i16 num)
{
	char* result = prime_StringFormat("%hi", num);
	return result;
}

char*
prime_I32ToString(i32 num)
{
	char* result = prime_StringFormat("%i", num);
	return result;
}

char*
prime_I64ToString(i64 num)
{
	char* result = prime_StringFormat("%lli", num);
	return result;
}

char*
prime_B8ToString(b8 num)
{
	return prime_StringDuplicate(num == false ? "false" : "true");
}

wchar_t*
prime_StringToWstring(const char* string)
{
	PASSERT_MSG(string, "string is null");
	int len = prime_MultibyteToWchar(string, 0, nullptr);
	if (len == 0) {
		return nullptr;
	}
	wchar_t* buffer = nullptr;
	if (s_Allocator) {}
	else {
		buffer = (wchar_t*)prime_MemoryAlloc(sizeof(wchar_t) * len);
	}
	
	PASSERT_MSG(buffer, "buffer allocation failed");
	prime_MultibyteToWchar(string, len, buffer);
	return buffer;
}

char*
prime_WstringToString(const wchar_t* wstring)
{
	PASSERT_MSG(wstring, "wstring is null");
	int len = prime_WcharToMultibyte(wstring, 0, nullptr);
	if (len == 0) {
		return nullptr;
	}

	char* buffer = nullptr;
	if (s_Allocator) {}
	else {
		buffer = (char*)prime_MemoryAlloc(len + 1);
	}
	PASSERT_MSG(buffer, "buffer allocation failed");
	prime_WcharToMultibyte(wstring, len, buffer);
	return buffer;
}

void
prime_WstringFree(wchar_t* wstring)
{
	PASSERT_MSG(wstring, "wstring is null");
	u64 len = wcslen(wstring);
	if (s_Allocator) {}
	else {
		prime_MemoryFree(wstring, sizeof(wchar_t) * len);
	}
}

char*
prime_StringFormatSys(const char* fmt, ...)
{
	if (!fmt) {
		return nullptr;
	}

	va_list arg_ptr;
	va_start(arg_ptr, fmt);

	va_list list_copy;

#ifdef _MSC_VER
	list_copy = arg_ptr;
#elif defined(P_PLATFORM_APPLE)
	list_copy = arg_ptr;
#else
	__builtin_va_copy(list_copy, arg_ptr);
#endif

	i32 length = vsnprintf(0, 0, fmt, list_copy);
	va_end(list_copy);
	char* result = (char*)prime_MemoryAlloc(length + 1);

	if (!result) {
		return nullptr;
	}
	vsnprintf(result, length + 1, fmt, arg_ptr);
	result[length] = 0;

	va_end(arg_ptr);
	return result;
}

void
prime_StringFreeSys(char* string)
{
	u64 length = strlen(string);
	prime_MemoryFree(string, length + 1);
}