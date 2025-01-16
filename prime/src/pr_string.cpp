
#include "prime/pr_string.h"
#include "prime/pr_log.h"
#include "prime/pr_memory.h"
#include "prime/pr_linear_allocator.h"

#include <string>
#include <stdarg.h>

struct PrString
{
	u64 length = 0;
	char* buffer = nullptr;
	PrAllocator* allocator = nullptr;
};

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
prStringCreateA(PrAllocator* allocator, const char* string)
{
	if (string) {
		u64 length = strlen(string);
		PrString* str = (PrString*)prAllocatorAlloc(allocator, sizeof(PrString));
		str->length = length;
		str->buffer = (char*)prAllocatorAlloc(allocator, length + 1);
		prMemCopy(str->buffer, (void*)string, length);
		str->buffer[length] = 0;
		str->allocator = allocator;

		return str;
	}
	return nullptr;
}

void
prStringDestroy(PrString* string)
{
	if (string && string->allocator == nullptr) {
		prMemFree(string->buffer, string->length + 1);
		prMemFree(string, sizeof(PrString));
	}
}

PrString*
prStringCopy(const PrString* string)
{
	if (string) {
		PrString* str = (PrString*)prMemAlloc(sizeof(PrString));
		str->length = string->length;
		str->buffer = (char*)prMemAlloc(string->length + 1);
		prMemCopy(str->buffer, (void*)string->buffer, string->length);
		str->buffer[string->length] = 0;
		
		return str;
	}
	return nullptr;
}

PrString*
prStringCopyA(PrAllocator* allocator, const PrString* string)
{
	if (string) {
		PrString* str = (PrString*)prAllocatorAlloc(allocator, sizeof(PrString));
		str->length = string->length;
		str->buffer = (char*)prAllocatorAlloc(allocator, string->length + 1);
		prMemCopy(str->buffer, (void*)string->buffer, string->length);
		str->buffer[string->length] = 0;
		str->allocator = allocator;

		return str;
	}
	return nullptr;
}

const char*
prStringGetBuffer(PrString* string)
{
	return string->buffer;
}

u64
prStringGetLength(PrString* string)
{
	return string->length;
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