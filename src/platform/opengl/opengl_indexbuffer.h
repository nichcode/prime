#pragma once

#include "prime/prime_indexbuffer.h"

namespace prime {

	class OpenGLIndexbuffer : public Indexbuffer
	{
		u32 m_Count, m_ID;

	public:
		OpenGLIndexbuffer(u32* indices, u32 count);
		virtual ~OpenGLIndexbuffer() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		PINLINE virtual u32 GetCount() const override { return m_Count; }
	};
}
