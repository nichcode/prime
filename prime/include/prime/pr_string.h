#pragma once

#include "pr_defines.h"
#include "pr_log.h"

struct PrString;
struct PrWideString;

PR_API PrString*
prStringCreate(const char* string);

PR_API PrString*
prStringCreateFromPrString(const PrString* string);

PR_API PrString*
prStringCreateFromPrWideString(const PrWideString* wide_string);

PR_API void
prStringDestroy(PrString* string);

PR_API const char*
prStringGetBuffer(const PrString* string);

PR_API u64
prStringGetLength(const PrString* string);

PR_API PrString*
prStringFormat(const char* fmt, ...);

PR_API PrString*
prStringFormatArgs(const char* fmt, char* va_listp);

PR_API void
prStringLog(PrString* string);


PR_API PrWideString*
prWideStringCreate(const wchar_t* wide_string);

PR_API PrWideString*
prWideStringCreateFromPrString(const PrString* string);

PR_API PrWideString*
prWideStringCreateFromCString(const char* string);

PR_API void
prWideStringDestroy(PrWideString* wide_string);

PR_API const wchar_t*
prWideStringGetBuffer(const PrWideString* wide_string);

PR_API u64
prWideStringGetLength(const PrWideString* wide_string);

PR_API void
prWideStringLog(PrWideString* wide_string);

#ifdef PR_CONFIG_DEBUG
#define PR_STRING_LOG(string)           prStringLog(string)
#define PR_WSTRING_LOG(wide_string)     prWideStringLog(wide_string)
#else
#define PR_STRING_LOG(message, ...)         
#define PR_WSTRING_LOG(message, ...)         
#endif // PR_CONFIG_DEBUG

#ifdef PR_CPP

class PrStringClass
{
	PrString* m_Handle;

public:
	PrStringClass() : m_Handle(nullptr) {}

	~PrStringClass()
	{
		if (m_Handle) {
			destroy();
		}
	}

	inline void
	destroy()
	{
		prStringDestroy(m_Handle);
		m_Handle = nullptr;
	}

	PrStringClass& 
	operator=(const PrStringClass& other)
	{
		if (this != &other) {
			m_Handle = prStringCreateFromPrString(other.m_Handle);
		}
		return *this;
	}

	PrStringClass&
	operator=(const char* string)
	{
		m_Handle = prStringCreate(string);
		return *this;
	}

	PrStringClass&
	operator=(PrString* string)
	{
		m_Handle = prStringCreateFromPrString(string);
		return *this;
	}

	inline const char* 
	getBuffer() 
	{
		return prStringGetBuffer(m_Handle);
	}

	inline u64
	getLength()
	{
		return prStringGetLength(m_Handle);
	}
};

#endif // PR_CPP
