#pragma once

#include "prime/texture2d.h"

namespace prime {

	class OpenGLTexture2D : public Texture2D
	{
	private:
		u32 m_id, m_width, m_height;
		str m_path;

	public:
		OpenGLTexture2D(const TextureProperties& props);
		OpenGLTexture2D(const str& filepath);

		virtual ~OpenGLTexture2D() override;

		virtual void bind(u32 slot) override;
		virtual void unbind() override;

		virtual u32 get_width() const override { return m_width; }
		virtual u32 get_height() const override { return m_height; }
		virtual str get_path() const override { return m_path; }

		virtual const void* get_handle() const override
		{
			return &m_id;
		}
	};

}