
#include "prime_opengl_texture2D.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"
#include "prime/prime_string.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#endif // STB_IMAGE_IMPLEMENTATION

#include "glad/glad.h"

struct gl_texture2D
{
	u32 id = 0;
	u32 dataFormat = 0;
};

static u32 s_Data = 0xffffffff;

static GLenum 
dataFormatFromTexture2DFormat(prime_Texture2DFormat format)
{
	switch (format)
	{
	case prime_Texture2DFormatR8:
		return GL_R8;
		break;

	case prime_Texture2DFormatRGB8:
		return GL_RGB;
		break;

	case prime_Texture2DFormatRGBA8:
		return GL_RGBA;
		break;

	case prime_Texture2DFormatRGBA32F:
		return GL_RGBA32F;
		break;
	}

	return 0;
}

static GLenum 
internalFormatFromTexture2DFormat(prime_Texture2DFormat format)
{
	switch (format)
	{
	case prime_Texture2DFormatR8:
		return GL_R8;
		break;

	case prime_Texture2DFormatRGB8:
		return GL_RGB8;
		break;

	case prime_Texture2DFormatRGBA8:
		return GL_RGBA8;
		break;

	case prime_Texture2DFormatRGBA32F:
		return GL_RGBA32F;
		break;
	}

	return 0;
}

void*
gl_Texture2DCreate(u32 width, u32 height, prime_Texture2DFormat format, b8 empty)
{
	gl_texture2D* tex = (gl_texture2D*)prime_MemAlloc(sizeof(gl_texture2D));

	glGenTextures(1, &tex->id);
	glBindTexture(GL_TEXTURE_2D, tex->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	tex->dataFormat = dataFormatFromTexture2DFormat(format);
	u32 internal_format = internalFormatFromTexture2DFormat(format);

	if (empty) {
		glTexImage2D(GL_TEXTURE_2D,
			0,
			internal_format,
			width,
			height,
			0,
			tex->dataFormat,
			GL_UNSIGNED_BYTE,
			nullptr);
	}
	else {
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			internal_format,
			width,
			height,
			0,
			tex->dataFormat,
			GL_UNSIGNED_BYTE,
			&s_Data);
	}

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	return tex;

}

void* 
gl_Texture2DLoad(const char* filepath, u32* width, u32* height)
{
	gl_texture2D* tex = (gl_texture2D*)prime_MemAlloc(sizeof(gl_texture2D));

	int w = 0, h = 0, channels = 0;

	stbi_uc* data = stbi_load(filepath, &w, &h, &channels, 0);

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

		PRIME_ASSERT_MSG(internal_format & data_format, "Format not supported!");

		glGenTextures(1, &tex->id);
		glBindTexture(GL_TEXTURE_2D, tex->id);

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

		*width = w;
		*height = h;
		stbi_image_free(data);

		return tex;
	}
	prime_String* str = prime_StringFormat("Could not load texture2d - %s", filepath);
	PRIME_ASSERT_MSG(false, prime_StringGetCstr(str));
	prime_StringDestroy(str);
	return nullptr;
}

void
gl_Texture2DDestroy(void* texture2d)
{
	gl_texture2D* gl_tex = (gl_texture2D*)texture2d;
	glDeleteTextures(1, &gl_tex->id);
	gl_tex->id = 0;
	prime_MemFree(texture2d, sizeof(gl_texture2D));
}

void
gl_Texture2DBind(void* texture2d, u32 slot)
{
	gl_texture2D* gl_tex = (gl_texture2D*)texture2d;
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, gl_tex->id);
}

void
gl_Texture2DUnbind(void* texture2d)
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void
gl_Texture2DSetData(void* texture2d, const void* data, u32 width, u32 height)
{
	gl_texture2D* gl_tex = (gl_texture2D*)texture2d;
	glTexSubImage2D(gl_tex->id, 0, 0, 0, width, height, gl_tex->dataFormat, GL_UNSIGNED_BYTE, data);
}