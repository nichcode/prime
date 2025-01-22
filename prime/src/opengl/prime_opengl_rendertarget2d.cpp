
#include "prime_opengl_rendertarget2d.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"
#include "prime/prime_texture2d.h"
#include "prime/prime_string.h"
#include "prime_utils.h"

#include "glad/glad.h"

struct gl_RenderTarget2D
{
	u32 id = 0;
	u32 depth = 0;
	prime_Texture2D* texture = nullptr;
};

void 
init(prime_Device* device, gl_RenderTarget2D* ren, u32 width, u32 height, b8 reset)
{
	if (reset) {
		glDeleteRenderbuffers(1, &ren->depth);
		glDeleteFramebuffers(1, &ren->id);
		ren->id = 0;
		ren->depth = 0;
		prime_Texture2DDestroy(ren->texture);
		ren->texture = nullptr;
	}

	glGenFramebuffers(1, &ren->id);
	glBindFramebuffer(GL_FRAMEBUFFER, ren->id);

	// color texture
	ren->texture = prime_Texture2DCreate(
		device,
		width,
		height,
		prime_Texture2DFormatRGBA8,
		true);

	glFramebufferTexture2D(
		GL_FRAMEBUFFER, 
		GL_COLOR_ATTACHMENT0, 
		GL_TEXTURE_2D, 
		prime_Texture2DGetGLHandle(prime_Texture2DGetHandle(ren->texture)),
		0);

	// Create depth/stencil renderbuffer
	glGenRenderbuffers(1, &ren->depth);
	glBindRenderbuffer(GL_RENDERBUFFER, ren->depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ren->depth);

	// Check for completeness
	i32 completeStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (completeStatus != GL_FRAMEBUFFER_COMPLETE) {
		auto msg = prime_StringFormat("Failure to create render target. Complete status: %i", completeStatus);
		PRIME_LOG_STRING(msg);
		prime_StringDestroy(msg);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void*
gl_RenderTarget2DCreate(prime_Device* device, u32 width, u32 height)
{
	gl_RenderTarget2D* ren = nullptr;
	ren = (gl_RenderTarget2D*)prime_MemAlloc(sizeof(gl_RenderTarget2D));
	init(device, ren, width, height, false);

	return ren;
}

void
gl_RenderTarget2DDestroy(void* rendertarget2d)
{
	gl_RenderTarget2D* ren = (gl_RenderTarget2D*)rendertarget2d;
	glDeleteRenderbuffers(1, &ren->depth);
	glDeleteFramebuffers(1, &ren->id);
	prime_Texture2DDestroy(ren->texture);
	ren->id = 0;
	ren->texture = nullptr;
	ren->depth = 0;
	prime_MemFree(rendertarget2d, sizeof(gl_RenderTarget2D));
}

void
gl_RenderTarget2DBind(void* rendertarget2d, u32 width, u32 height)
{
	gl_RenderTarget2D* ren = (gl_RenderTarget2D*)rendertarget2d;
	glBindFramebuffer(GL_FRAMEBUFFER, ren->id);
	glViewport(0, 0, width, height);
}

void
gl_RenderTarget2DUnbind(void* rendertarget2d)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void 
gl_RenderTarget2DResize(prime_Device* device, void* rendertarget2d, u32 width, u32 height)
{
	if (width == 0 || height == 0 || width > PRIME_MAX_RENDER_TARGET_SIZE || height > PRIME_MAX_RENDER_TARGET_SIZE)
	{
		auto msg = prime_StringFormat("Attempted to rezize render target to (%i, %i)", width, height);
		PRIME_LOG_STRING(msg);
		prime_StringDestroy(msg);
		return;
	}

	gl_RenderTarget2D* ren = (gl_RenderTarget2D*)rendertarget2d;
	init(device, ren, width, height, true);
}

prime_Texture2D*
gl_RenderTarget2DGetTexture2D(void* rendertarget2d)
{
	gl_RenderTarget2D* ren = (gl_RenderTarget2D*)rendertarget2d;
	return ren->texture;
}