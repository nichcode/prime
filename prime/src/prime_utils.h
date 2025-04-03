
#pragma once

#include "prime/prime.h"

struct prime_window;

namespace prime {

    class Allocator
    {
    private:
        u64 m_Size = 0;
        u64 m_Allocated = 0;
        void* m_Memory = nullptr;

    public:
        void init();
        void shutdown();

        void* allocate(u64 size);
        void clear();
    };
    
    struct InitData
    {
        Allocator allocator;
        u32 type;
        prime_window* window;
    };

    static InitData s_Data;

    i32 multibyteToWchar(const char* str, u32 str_len, wchar_t* wstr);
    i32 wcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str);

    void consoleWrite(u32 level, const char* msg);
    void initInput();
}