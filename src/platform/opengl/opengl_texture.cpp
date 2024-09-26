
#include "opengl_texture.h"
#include "prime/prime_device.h"
#include "platform/glad/glad.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "platform/stb/stb_image.h"
#endif // STB_IMAGE_IMPLEMENTATION

namespace prime {

	static u32 s_Data = 0xffffffff;

	static GLenum GLDataFormatFromTextureFormat(TextureFormat format) 
	{
		switch (format)
		{
		case TextureFormatNone:
			PASSERT_MSG(false, "Invalid textureFormat");
			break;

		case TextureFormatR8:
			return GL_R8;
			break;

		case TextureFormatRGB8:
			return GL_RGB;
			break;

		case TextureFormatRGBA8:
			return GL_RGBA;
			break;

		case TextureFormatRGBA32F:
			return GL_RGBA32F;
			break;
		}

		return 0;
		PASSERT_MSG(false, "Invalid textureFormat");
	}

	static GLenum GLInternalFormatFromTextureFormat(TextureFormat format)
	{
		switch (format)
		{
		case TextureFormatNone:
			PASSERT_MSG(false, "Invalid textureFormat");
			break;

		case TextureFormatR8:
			return GL_R8;
			break;

		case TextureFormatRGB8:
			return GL_RGB8;
			break;

		case TextureFormatRGBA8:
			return GL_RGBA8;
			break;

		case TextureFormatRGBA32F:
			return GL_RGBA32F;
			break;
		}

		return 0;
		PASSERT_MSG(false, "Invalid textureFormat");
	}

	OpenGLTexture2D::OpenGLTexture2D(const TextureProperties& props)
	{
        glGenTextures(1, &m_ID);
        glBindTexture(GL_TEXTURE_2D, m_ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		i32 dataFormat = GLDataFormatFromTextureFormat(props.Format);
		i32 internalFormat = GLInternalFormatFromTextureFormat(props.Format);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			internalFormat,
			props.Width,
			props.Height,
			0,
			dataFormat,
			GL_UNSIGNED_BYTE,
			&s_Data);

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		m_Width = props.Width;
		m_Height = props.Height;
	}

	OpenGLTexture2D::OpenGLTexture2D(const str& filepath)
	{
		int w = 0, h = 0, channels = 0;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(filepath.c_str(), &w, &h, &channels, 0);
		if (data) {
			GLenum internalFormat = 0, dataFormat = 0;
			if (channels == 4) {
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (channels == 3) {
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}

			PASSERT_MSG(internalFormat & dataFormat, "Format not supported!");

			glGenTextures(1, &m_ID);
			glBindTexture(GL_TEXTURE_2D, m_ID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				internalFormat,
				w,
				h,
				0, 
				dataFormat,
				GL_UNSIGNED_BYTE,
				data);

			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);

			m_Width = w;
			m_Height = h;
			stbi_image_free(data);
		}
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_ID);
		m_ID = 0;
	}

	void OpenGLTexture2D::Bind(u32 slot)
	{
		// TODO: check available texture slots.
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void OpenGLTexture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}