#pragma once

#include "prime/indexbuffer.h"

namespace prime {

	class OpenGLIndexbuffer : public Indexbuffer
	{
	private:
		u32 m_count, m_id;

	public:
		OpenGLIndexbuffer(u32* indices, u32 count);
		virtual ~OpenGLIndexbuffer() override;

		virtual void bind() override;
		virtual void unbind() override;

		PINLINE virtual u32 get_count() const override { return m_count; }
	};
}
