
#include "opengl_texture2d.h"
#include "prime/assert.h"
#include "platform/glad/glad.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "platform/stb/stb_image.h"
#endif // STB_IMAGE_IMPLEMENTATION

namespace prime {

	static u32 s_data = 0xffffffff;

	static GLenum gl_data_format_from_texture_format(TextureFormat format) 
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

	static GLenum gl_internal_format_from_texture_format(TextureFormat format)
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
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		i32 data_format = gl_data_format_from_texture_format(props.format);
		i32 internal_format = gl_internal_format_from_texture_format(props.format);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			internal_format,
			props.width,
			props.height,
			0,
			data_format,
			GL_UNSIGNED_BYTE,
			&s_data);

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		m_width = props.width;
		m_height = props.height;
	}

	OpenGLTexture2D::OpenGLTexture2D(const str& filepath)
	{
		int w = 0, h = 0, channels = 0;
		m_width = 0; m_height = 0; m_id = 0;

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(filepath.c_str(), &w, &h, &channels, 0);
		if (data) {
			GLenum internal_format = 0, data_format = 0;
			if (channels == 4) {
				internal_format = GL_RGBA8;
				data_format = GL_RGBA;
			}
			else if (channels == 3) {
				internal_format = GL_RGB8;
				data_format = GL_RGB;
			}

			PASSERT_MSG(internal_format & data_format, "Format not supported!");

			glGenTextures(1, &m_id);
			glBindTexture(GL_TEXTURE_2D, m_id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				internal_format,
				w,
				h,
				0, 
				data_format,
				GL_UNSIGNED_BYTE,
				data);

			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);

			m_width = w;
			m_height = h;
			stbi_image_free(data);
		}
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_id);
		m_id = 0;
	}

	void OpenGLTexture2D::bind(u32 slot)
	{
		if (slot < MAX_TEXTURE_SLOTS) {
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, m_id);
		}
	}

	void OpenGLTexture2D::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}