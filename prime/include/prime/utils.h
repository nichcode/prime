
#pragma once

#include "defines.h"

#include <stdarg.h>
#include <memory>

namespace prime {

    class Utils
    {
    private:
        static char*
        formatArgs(const char* fmt, va_list args_list);

    public:
        static void
        init();

        static str 
        format(const char* fmt, ...);

        static const char* 
        getName(Action action);

        static const char* 
        getName(Button button);

        static const char* 
        getName(Key key);

        static str 
        toString(const wstr& wstring);

        static wstr 
        toWstring(const str& string);
    };

    template<typename T>
	using Scope = std::unique_ptr<T>;

    template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> createScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr Ref<T> createRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
    
} // namespace prime