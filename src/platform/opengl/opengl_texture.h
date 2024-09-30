#pragma once

#include "prime/prime_texture.h"

namespace prime {

	class OpenGLTexture2D : public Texture2D
	{
		u32 m_id, m_width, m_height;
		str m_path;

	public:
		OpenGLTexture2D(const TextureProperties& props);
		OpenGLTexture2D(const str& filepath);

		virtual ~OpenGLTexture2D() override;

		virtual void Bind(u32 slot) override;
		virtual void Unbind() override;

		virtual u32 GetWidth() const override { return m_width; }
		virtual u32 GetHeight() const override { return m_height; }
		virtual str GetPath() const override { return m_path; }
	};

}