
#include "prime/platform.h"
#include "prime/logger.h"

#include <memory.h>

#ifdef PPLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>

static u64 s_UsedMemory = 0;

namespace prime {

    b8 
    Platform::init()
    {
        PINFO("Prime Windows Platform Init");
        return true;
    }

    void 
    Platform::shutdown()
    {
        PINFO("Prime Windows Platform Shutdown");
    }

    void* 
    Platform::_alloc(u64 size)
    {
        PASSERT_MSG(size, "size is invalid");
        s_UsedMemory += size;
        return (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
    }

    void 
    Platform::_free(void*memory, u64 size)
    {
        PASSERT_MSG(size, "size is invalid");
        s_UsedMemory -= size;
        HeapFree(GetProcessHeap(), 0, memory);
        memory = nullptr;
    }

    void 
    Platform::copy(void* dest_memory, void* src_memory, u64 size)
    {
        PASSERT_MSG(dest_memory, "dest_memory");
        PASSERT_MSG(src_memory, "src_memory");
        memcpy(dest_memory, src_memory, size);
    }

    void 
    Platform::set(void* memory, i32 value, u64 size)
    {
        PASSERT_MSG(memory, "memory");
        memset(memory, value, size);
    }

    void 
    Platform::zero(void* memory, u64 size)
    {
        PASSERT_MSG(memory, "memory");
        memset(memory, 0, size);
    }

    void 
    Logger::setLevel(LogLevel level, b8 reset)
    {
        HANDLE console = NULL;
        static u8 levels[4] = { 8, 2, 6, 4 };
        b8 error = level > LogLevel::Warn;

        if (error) {
            console = GetStdHandle(STD_ERROR_HANDLE);
        }
        else {
            console = GetStdHandle(STD_OUTPUT_HANDLE);
        }

        if (reset) {
            SetConsoleTextAttribute(console, 15);
        }
        else {
            SetConsoleTextAttribute(console, levels[(u32)level]);
        }
    }

} // namespace prime

#endif // PPLATFORM_WINDOWS