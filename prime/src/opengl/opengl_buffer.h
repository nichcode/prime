
#pragma once

#include "prime/buffer.h"

namespace prime {

    class GLBuffer : public Buffer
    {
    private:
        u32 m_ID;
        BufferType m_Type;
        BufferUsage m_Usage;
        void* m_Unused;

    public:
        GLBuffer(const BufferDesc& desc);
        virtual ~GLBuffer() override;

        virtual void
        setData(const void* data, u32 size) override;

        virtual BufferType
        getType() const override { return m_Type; }

        virtual BufferUsage
        getUsage()const override { return m_Usage; }

        virtual u32 getID()const override { return m_ID; }
        virtual void* getHandle() const override {return m_Unused; }
    };
    
} // namespace prime
