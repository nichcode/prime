#pragma once

#include "prime/prime_uniformbuffer.h"

namespace prime {

	class OpenGLUniformbuffer : public Uniformbuffer
	{
		u32 m_id;

	public:
		OpenGLUniformbuffer(u32 size, u32 binding);
		virtual ~OpenGLUniformbuffer() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetData(u32 size, void* data) override;
	};
}
