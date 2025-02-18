
#include "prime/prime_string.h"
#include "prime/prime_memory.h"
#include "prime_utils.h"
#include "prime/prime_math.h"

#include <string.h>
#include <stdio.h>

char*
primeStringDuplicate(const char* string)
{
	PASSERT_MSG(string, "string is null");
	u64 length = strlen(string);
	char* buffer = nullptr;
	if (s_Allocator) {}
	else {
		buffer = (char*)primeMemoryAlloc(length + 1);
	}
	PASSERT_MSG(buffer, "string buffer failed to allocate");
	primeMemoryCopy(buffer, (void*)string, length);
	buffer[length] = 0;
	return buffer;
}

void
primeStringCopy(char* dest_string, const char* src_string)
{
	PASSERT_MSG(dest_string, "dest_string is null");
	PASSERT_MSG(dest_string, "src_string is null");
	strcpy(dest_string, src_string);
}

void
primeStringNcopy(char* dest_string, const char* src_string, u64 length)
{
	PASSERT_MSG(dest_string, "dest_string is null");
	PASSERT_MSG(src_string, "src_string is null");
	strncpy(dest_string, src_string, length);
}

void
primeStringFree(char* string)
{
	PASSERT_MSG(string, "string is null");
	u64 length = strlen(string);
	if (s_Allocator) {}
	else {
		primeMemoryFree(string, length + 1);
	}
}

u64
primeStringGetLength(const char* string)
{
	PASSERT_MSG(string, "string is null");
	return strlen(string);
}

char*
primeStringAdd(const char* string1, const char* string2)
{
	PASSERT_MSG(string1, "string1 is null");
	PASSERT_MSG(string2, "string2 is null");
	u64 len = strlen(string1) + strlen(string2);
	char* result = nullptr;
	if (s_Allocator) {}
	else {
		result = (char*)primeMemoryAlloc(len + 1);
	}
	
	PASSERT_MSG(result, "buffer allocation failed");
	strcat(result, string1);
	strcat(result, string2);
	return result;
}

char*
primeStringFormatArgs(const char* fmt, va_list args_list)
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
		result = (char*)primeMemoryAlloc(length + 1);
	}

	PASSERT_MSG(result, "buffer allocation failed");
	vsnprintf(result, length + 1, fmt, args_list);
	result[length] = 0;
	return result;
}

char*
primeStringFormat(const char* fmt, ...)
{
	PASSERT_MSG(fmt, "fmt is null");
	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	char* result = primeStringFormatArgs(fmt, arg_ptr);
	PASSERT_MSG(result, "buffer allocation failed");
	va_end(arg_ptr);
	return result;
}

b8
primeStringEqual(const char* string1, const char* string2, b8 case_sensitive)
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
primeStringEmpty(const char* string)
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
primeStringClear(char* string)
{
	PASSERT_MSG(string, "string is null");
	string[0] = 0;
}

i32
primeStringGetIndex(const char* string1, const char* string2)
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
primeStringInsert(char* dest_string, const char* src_string, u32 pos, const char* string)
{
	PASSERT_MSG(dest_string, "dest_string is null");
	PASSERT_MSG(src_string, "src_string is null");
	u64 src_len = strlen(src_string);
	u64 len = strlen(string);
	u64 remaining = src_len - pos;

	if (pos > 0) {
		primeMemoryCopy((void*)dest_string, (void*)src_string, pos);
	}
	if (pos < src_len) {
		primeMemoryCopy((void*)(dest_string + pos + len), (void*)(src_string + pos), (u32)remaining);
	}
	primeMemoryCopy((void*)(dest_string + pos), (void*)string, len);
}

char* 
primeStringInsertAlloc(const char* src_string, u32 pos, const char* string)
{
	PASSERT_MSG(src_string, "src_string is null");
	u64 src_len = strlen(src_string);
	u64 len = strlen(string);
	u64 remaining = src_len - pos;

	char* dest_string = nullptr;
	if (s_Allocator) {}
	else {
		dest_string = (char*)primeMemoryAlloc(src_len + len + 1);
	}

	PASSERT_MSG(src_string, "buffer allocation failed");
	if (pos > 0) {
		primeMemoryCopy((void*)dest_string, (void*)src_string, pos);
	}
	if (pos < src_len) {
		primeMemoryCopy((void*)(dest_string + pos + len), (void*)(src_string + pos), (u32)remaining);
	}
	primeMemoryCopy((void*)(dest_string + pos), (void*)string, len);
	return dest_string;
}

void
primeStringAssign(char* string, u32 pos, char c)
{
	PASSERT_MSG(string, "string is null");
	PASSERT_MSG(pos < strlen(string), "pos out of bounds");
	string[pos] = c;
}

void
primeStringRemove(char* dest_string, const char* src_string, u32 pos, u32 length)
{
	PASSERT_MSG(dest_string, "dest_string is null");
	PASSERT_MSG(src_string, "src_string is null");
	u64 original_length = strlen(src_string);
	u64 remaining = original_length - pos - length;
	if (pos > 0) {
		primeMemoryCopy((void*)dest_string, (void*)src_string, pos);
	}

	if (pos < original_length) {
		primeMemoryCopy((void*)(dest_string + pos), (void*)(src_string + pos + length), (u32)remaining);
	}
	dest_string[original_length - length] = 0;
}

char*
primeF32ToString(f32 num)
{
	char* result = primeStringFormat("%.2f", num);
	return result;
}

char*
primeF64ToString(f64 num)
{
	char* result = primeStringFormat("%.2f", num);
	return result;
}

char*
primeU8ToString(u8 num)
{
	char* result = primeStringFormat("%hhu", num);
	return result;
}

char*
primeU16ToString(u16 num)
{
	char* result = primeStringFormat("%hu", num);
	return result;
}

char*
primeU32ToString(u32 num)
{
	char* result = primeStringFormat("%u", num);
	return result;
}

char*
primeU64ToString(u64 num)
{
	char* result = primeStringFormat("%llu", num);
	return result;
}

char*
primeI8ToString(i8 num)
{
	char* result = primeStringFormat("%hhi", num);
	return result;
}

char*
primeI16ToString(i16 num)
{
	char* result = primeStringFormat("%hi", num);
	return result;
}

char*
primeI32ToString(i32 num)
{
	char* result = primeStringFormat("%i", num);
	return result;
}

char*
primeI64ToString(i64 num)
{
	char* result = primeStringFormat("%lli", num);
	return result;
}

char*
primeB8ToString(b8 num)
{
	return primeStringDuplicate(num == false ? "false" : "true");
}

wchar_t*
primeStringToWstring(const char* string)
{
	PASSERT_MSG(string, "string is null");
	int len = primeMultibyteToWchar(string, 0, nullptr);
	if (len == 0) {
		return nullptr;
	}
	wchar_t* buffer = nullptr;
	if (s_Allocator) {}
	else {
		buffer = (wchar_t*)primeMemoryAlloc(sizeof(wchar_t) * len);
	}
	
	PASSERT_MSG(buffer, "buffer allocation failed");
	primeMultibyteToWchar(string, len, buffer);
	return buffer;
}

char*
primeWstringToString(const wchar_t* wstring)
{
	PASSERT_MSG(wstring, "wstring is null");
	int len = primeWcharToMultibyte(wstring, 0, nullptr);
	if (len == 0) {
		return nullptr;
	}

	char* buffer = nullptr;
	if (s_Allocator) {}
	else {
		buffer = (char*)primeMemoryAlloc(len + 1);
	}
	PASSERT_MSG(buffer, "buffer allocation failed");
	primeWcharToMultibyte(wstring, len, buffer);
	return buffer;
}

void
primeWstringFree(wchar_t* wstring)
{
	PASSERT_MSG(wstring, "wstring is null");
	u64 len = wcslen(wstring);
	if (s_Allocator) {}
	else {
		primeMemoryFree(wstring, sizeof(wchar_t) * len);
	}
}

char*
primeStringFormatSys(const char* fmt, ...)
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
	char* result = (char*)primeMemoryAlloc(length + 1);

	if (!result) {
		return nullptr;
	}
	vsnprintf(result, length + 1, fmt, arg_ptr);
	result[length] = 0;

	va_end(arg_ptr);
	return result;
}

void
primeStringFreeSys(char* string)
{
	u64 length = strlen(string);
	primeMemoryFree(string, length + 1);
}

// maths
char*
primeVec2ToString(const primeVec2& vec)
{
	return primeStringFormat("Vec2(%.2f, %.2f)", vec.x, vec.y);
}

char*
primeVec3ToString(const primeVec3& vec)
{
	return primeStringFormat("Vec3(%.2f, %.2f, %.2f)", vec.x, vec.y, vec.z);
}

char*
primeVec4ToString(const primeVec4& vec)
{
	return primeStringFormat("Vec4(%.2f, %.2f, %.2f, %.2f)", vec.x, vec.y, vec.z, vec.w);
}

char*
primeMat4ToString(const primeMat4& matrix)
{
	const f32* d = matrix.data;
	char* str1 = primeStringFormat("[%f %f %f %f]", d[0], d[1], d[2], d[3]);
	char* str2 = primeStringFormat("[%f %f %f %f]", d[4], d[5], d[6], d[7]);
	char* str3 = primeStringFormat("[%f %f %f %f]", d[8], d[9], d[10], d[11]);
	char* str4 = primeStringFormat("[%f %f %f %f]", d[12], d[13], d[14], d[15]);

	char* str = primeStringFormat("Mat4(%s \n\t     %s \n\t     %s \n\t     %s)",
		str1,
		str2,
		str3,
		str4);

	primeStringFree(str1);
	primeStringFree(str2);
	primeStringFree(str3);
	primeStringFree(str4);
	
	return str;
}