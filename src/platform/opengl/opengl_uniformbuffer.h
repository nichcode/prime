#pragma once

#include "prime/uniformbuffer.h"

namespace prime {

	class OpenGLUniformbuffer : public Uniformbuffer
	{
	private:
		u32 m_id;

	public:
		OpenGLUniformbuffer(u32 size, u32 binding);
		virtual ~OpenGLUniformbuffer() override;

		virtual void bind() override;
		virtual void unbind() override;

		virtual void set_data(u32 size, void* data) override;
	};
}
