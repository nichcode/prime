
#include "prime_gltexture.h"
#include "prime/prime_memory.h"
#include "prime/prime_string.h"
#include "prime_utils.h"
#include "glad/glad.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

struct glTexture2D
{
	u32 id = 0;
	u32 dataFormat = 0;
    const char* path = nullptr;
};

static u32 s_Data = 0xffffffff;

static GLenum 
dataFormatToGL(primeTextureFormat format)
{
	switch (format)
	{
	case primeTextureFormatR8:
		return GL_R8;
		break;

	case primeTextureFormatRGB8:
		return GL_RGB;
		break;

	case primeTextureFormatRGBA8:
		return GL_RGBA;
		break;

	case primeTextureFormatRGBA32F:
		return GL_RGBA32F;
		break;
	}

	return 0;
}

static GLenum 
internalFormatToGL(primeTextureFormat format)
{
	switch (format)
	{
	case primeTextureFormatR8:
		return GL_R8;
		break;

	case primeTextureFormatRGB8:
		return GL_RGB8;
		break;

	case primeTextureFormatRGBA8:
		return GL_RGBA8;
		break;

	case primeTextureFormatRGBA32F:
		return GL_RGBA32F;
		break;
	}

	return 0;
}

void*
primeGLTexture2DCreate(const primeTexture2DDesc* desc)
{
    glTexture2D* tex = (glTexture2D*)primeMemoryAlloc(sizeof(glTexture2D));

	glGenTextures(1, &tex->id);
	glBindTexture(GL_TEXTURE_2D, tex->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	tex->dataFormat = dataFormatToGL(desc->format);
	u32 internal_format = internalFormatToGL(desc->format);

	if (desc->renderTarget) {
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			internal_format,
			desc->width,
			desc->height,
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
			desc->width,
			desc->height,
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
primeGLTexture2DLoad(const char* filepath, u32* width, u32* height)
{
    glTexture2D* tex = (glTexture2D*)primeMemoryAlloc(sizeof(glTexture2D));

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

		PASSERT_MSG(internal_format & data_format, "Format not supported!");

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
	char* str = primeStringFormat("Could not load texture2d - %s", filepath);
	PASSERT_MSG(false, str);
	primeStringFree(str);
	return nullptr;

}

void
primeGLTexture2DDestroy(void* handle)
{
    glTexture2D* gl_tex = (glTexture2D*)handle;
	glDeleteTextures(1, &gl_tex->id);
	gl_tex->id = 0;
	primeMemoryFree(handle, sizeof(glTexture2D));
}

void
primeGLTexture2DBind(void* handle, u32 slot = 0)
{
    glTexture2D* gl_tex = (glTexture2D*)handle;
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, gl_tex->id);
}

void
primeGLTexture2DUnbind(void* handle)
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void
primeGLTexture2DSetData(void* handle, const void* data, u32 width, u32 height)
{
    glTexture2D* gl_tex = (glTexture2D*)handle;
	glTexSubImage2D(gl_tex->id, 0, 0, 0, width, height, gl_tex->dataFormat, GL_UNSIGNED_BYTE, data);
}

u32
primeGLTexture2DGetHandle(void* handle)
{
    glTexture2D* gl_tex = (glTexture2D*)handle;
	return gl_tex->id;
}