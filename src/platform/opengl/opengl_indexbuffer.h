#pragma once

#include "prime/prime_indexbuffer.h"

namespace prime {

	class OpenGLIndexbuffer : public Indexbuffer
	{
	private:
		Device* m_Device;
		u32 m_Count, m_ID;
		IndexbufferHandle m_Handle;

	public:
		OpenGLIndexbuffer(Device* device, u32* indices, u32 count);
		virtual ~OpenGLIndexbuffer() override;

		virtual void Bind() override;
		PINLINE virtual u32 GetCount() const override { return m_Count; }
	};
}
