
#include "prime/pr_string.h"
#include "pr_platform.h"
#include "prime/pr_memory.h"

#include "prime/pr_vec2.h"
#include "prime/pr_vec3.h"
#include "prime/pr_vec4.h"
#include "prime/pr_mat4.h"

#include <string>
#include <stdarg.h>

struct PrString
{
	u64 length = 0;
	char* buffer = nullptr;
};

struct PrWideString
{
	u64 length = 0;
	wchar_t* buffer = nullptr;
};


// string
PrString*
prStringCreate(const char* string)
{
	if (string) {
		u64 length = strlen(string);
		PrString* str = (PrString*)prMemAlloc(sizeof(PrString));
		str->length = length;
		str->buffer = (char*)prMemAlloc(length + 1);
		prMemCopy(str->buffer, (void*)string, length);
		str->buffer[length] = 0;

		return str;
	}
	return nullptr;
}

PrString* 
prStringCreateFromPrString(const PrString* string)
{
	if (string) {
		u64 length = strlen(string->buffer);
		PrString* str = (PrString*)prMemAlloc(sizeof(PrString));
		str->length = length;
		str->buffer = (char*)prMemAlloc(length + 1);
		prMemCopy(str->buffer, (void*)string->buffer, length);
		str->buffer[length] = 0;

		return str;
	}
	return nullptr;
}

PrString* 
prStringCreateFromPrWideString(const PrWideString* wide_string)
{
	if (wide_string) {
		int len = prPlatformWideCharToMultiByte(wide_string->buffer, 0, nullptr);
		if (len == 0) {
			return nullptr;
		}

		PrString* string = (PrString*)prMemAlloc(sizeof(PrString));
		string->length = len;
		string->buffer = (char*)prMemAlloc(len + 1);
		prPlatformWideCharToMultiByte(wide_string->buffer, len, string->buffer);
	}
	return nullptr;
}

void
prStringDestroy(PrString* string)
{
	if (string) {
		prMemFree(string->buffer, string->length + 1);
		prMemFree(string, sizeof(PrString));
	}
}

const char*
prStringGetBuffer(const PrString* string)
{
	if (string) {
		return string->buffer;
	}
	return nullptr;
}

u64
prStringGetLength(const PrString* string)
{
	if (string) {
		return string->length;
	}
	return 0;
}

PrString*
prStringFormat(const char* fmt, ...)
{
	if (!fmt) {
		return nullptr;
	}

	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	PrString* result = prStringFormatArgs(fmt, arg_ptr);
	va_end(arg_ptr);
	return result;
}

PrString*
prStringFormatArgs(const char* fmt, char* va_listp)
{
	if (!fmt) {
		return 0;
	}

	va_list list_copy;
	list_copy = va_listp;

	i32 length = vsnprintf(0, 0, fmt, list_copy);
	va_end(list_copy);

	PrString* str = (PrString*)prMemAlloc(sizeof(PrString));
	if (!str) {
		return 0;
	}

	str->buffer = (char*)prMemAlloc(length + 1);
	str->length = length;

	vsnprintf(str->buffer, length + 1, fmt, va_listp);
	str->buffer[length] = 0;
	return str;
}

void
prStringLog(PrString* string)
{
	prLogInfo(prStringGetBuffer(string));
}


// wide string
PrWideString*
prWideStringCreate(const wchar_t* wide_string)
{
	if (wide_string) {
		u64 length = wcslen(wide_string);
		PrWideString* str = (PrWideString*)prMemAlloc(sizeof(PrWideString));
		str->length = length;
		str->buffer = (wchar_t*)prMemAlloc(length * sizeof(wchar_t));
		prMemCopy(str->buffer, (void*)wide_string, length);
		str->buffer[length] = 0;

		return str;
	}
	return nullptr;
}

PrWideString*
prWideStringCreateFromPrString(const PrString* string)
{
	if (string) {
		int len = prPlatformMultiByteToWideChar(string->buffer, 0, nullptr);
		if (len == 0) {
			return nullptr;
		}

		PrWideString* str = (PrWideString*)prMemAlloc(sizeof(PrWideString));
		str->length = len;

		str->buffer = (wchar_t*)prMemAlloc(sizeof(wchar_t) * len);
		prPlatformMultiByteToWideChar(string->buffer, len, str->buffer);

		return str;
	}
	return nullptr;
}

PrWideString* 
prWideStringCreateFromCString(const char* string)
{
	if (string) {
		int len = prPlatformMultiByteToWideChar(string, 0, nullptr);
		if (len == 0) {
			return nullptr;
		}

		PrWideString* str = (PrWideString*)prMemAlloc(sizeof(PrWideString));
		str->length = len;
		str->buffer = (wchar_t*)prMemAlloc(len * sizeof(wchar_t));
		prPlatformMultiByteToWideChar(string, len, str->buffer);

		return str;
	}
	return nullptr;
}

void
prWideStringDestroy(PrWideString* wide_string)
{
	if (wide_string) {
		prMemFree(wide_string->buffer, wide_string->length * sizeof(wchar_t));
		prMemFree(wide_string, sizeof(PrWideString));
	}
}

const wchar_t*
prWideStringGetBuffer(const PrWideString* wide_string)
{
	if (wide_string) {
		return wide_string->buffer;
	}
	return nullptr;
}

u64
prWideStringGetLength(const PrWideString* wide_string)
{
	if (wide_string) {
		return wide_string->length;
	}
	return 0;
}

void
prWideStringLog(PrWideString* wide_string)
{
	prStringLog(prStringCreateFromPrWideString(wide_string));
}


PrString*
prVec2ToString(const PrVec2& vec)
{
	return prStringFormat("Vec2(%.2f, %.2f)", vec.x, vec.y);
}

PrString*
prVec3ToString(const PrVec3& vec)
{
	return prStringFormat("Vec3(%.2f, %.2f, %.2f)", vec.x, vec.y, vec.z);
}

PrString*
prVec4ToString(const PrVec4& vec)
{
	return prStringFormat("Vec4(%.2f, %.2f, %.2f, %.2f)", vec.x, vec.y, vec.z, vec.w);
}

PrString*
prMat4ToString(const PrMat4& matrix)
{
	const f32* d = matrix.data;
	PrString* str1 = prStringFormat("[%f %f %f %f]", d[0], d[1], d[2], d[3]);
	PrString* str2 = prStringFormat("[%f %f %f %f]", d[4], d[5], d[6], d[7]);
	PrString* str3 = prStringFormat("[%f %f %f %f]", d[8], d[9], d[10], d[11]);
	PrString* str4 = prStringFormat("[%f %f %f %f]", d[12], d[13], d[14], d[15]);

	PrString* str = prStringFormat("Mat4(%s \n\t     %s \n\t     %s \n\t     %s)",
		prStringGetBuffer(str1),
		prStringGetBuffer(str2),
		prStringGetBuffer(str3),
		prStringGetBuffer(str4));

	prStringDestroy(str1);
	prStringDestroy(str2);
	prStringDestroy(str3);
	prStringDestroy(str4);

	/*PrString* str = prStringFormat(
		"Mat4([%.2f %.2f %.2f %.2f] \n\t [%.2f %.2f %.2f %.2f] \n\t \ [%.2f %.2f %.2f %.2f] \n\t [%.2f %.2f %.2f %.2f])",
		d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7], d[8], d[9], d[10], d[11], d[12],
		d[13], d[14], d[15]);*/
	
	return str;
}