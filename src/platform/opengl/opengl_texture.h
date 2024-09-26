#pragma once

#include "prime/prime_texture.h"

namespace prime {

	class OpenGLTexture2D : public Texture2D
	{
		u32 m_ID, m_Width, m_Height;
		str m_Path;

	public:
		OpenGLTexture2D(const TextureProperties& props);
		OpenGLTexture2D(const str& filepath);

		virtual ~OpenGLTexture2D() override;

		virtual void Bind(u32 slot) override;
		virtual void Unbind() override;

		virtual u32 GetWidth() const override { return m_Width; }
		virtual u32 GetHeight() const override { return m_Height; }
		virtual str GetPath() const override { return m_Path; }
	};

}