
#include "pch.h"

namespace prime {

    void Allocator::init()
    {
        m_Memory = malloc(PRIME_MB);
        memset(m_Memory, 0, PRIME_MB);
        m_Size = PRIME_MB;
    }

    void Allocator::shutdown()
    {
        free(m_Memory);
        m_Size = 0;
        m_Allocated = 0;
    }

    void* Allocator::allocate(u64 size) 
    {
        if (m_Allocated + size > m_Size) {
            u64 remaining = m_Size - m_Allocated;
            PRIME_ASSERT_MSG(false, "Tried to allocate %lluB, only %lluB remaining.", size, remaining);
            return nullptr;
        }

        void* block = ((u8*)m_Memory) + m_Allocated;
        m_Allocated += size;
        return block;
    }

    void Allocator::clear() 
    {
        memset(m_Memory, 0, m_Size);
    }

} // namespace prime

