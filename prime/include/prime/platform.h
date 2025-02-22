
#pragma once

#include "defines.h"

namespace prime {
    
    class Platform
    {
    private:
        static void* _alloc(u64 size);
        static void _free(void* memory, u64 size);
        static void _copy(void* memory, u64 size);
        static void _set(void* memory, u64 size);

    public:
        static b8 init();
        static void shutdown();

        static void copy(void* dest_memory, void* src_memory, u64 size);
        static void set(void* memory, i32 value, u64 size);
        static void zero(void* memory, u64 size);

        template<typename T>
        static T* alloc()
        {
            T* ptr = (T*)_alloc(sizeof(T));
            *ptr = T();
            return ptr;
        }

        template<typename T>
        static T* alloc(u64 size)
        {
            T* ptr = (T*)_alloc(size);
            *ptr = T();
            return ptr;
        }

        template<typename T>
        static void free(T* object)
        {
            _free((void*)object, sizeof(T));
        }

        template<typename T>
        static void free(T* object, u64 size)
        {
            _free((void*)object, size);
        }
    };

} // namespace prime
