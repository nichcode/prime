
#include "prime/prime_renderer2d.h"
#include "prime/prime_window.h"
#include "prime/prime_log.h"
#include "prime/prime_buffers.h"
#include "prime/prime_shader.h"
#include "prime/prime_context.h"
#include "prime/prime_texture2d.h"
#include "prime_shader_sources.h"

#include <array>

struct SpriteVertex
{
	prime_Vec2 position;
	prime_Color color;
	prime_Vec2 texCoords;
	f32 tex_index = 0.0f;
};

struct LineVertex
{
	prime_Vec2 position;
	prime_Color color;
};

struct SpriteData
{
	prime_Vertexbuffer* vertexbuffer = nullptr;
	prime_Indexbuffer* indexbuffer = nullptr;
	prime_Shader* shader = nullptr;
	u32 indexCount = 0;
	prime_Vec4 vertices[4];
	prime_Vec2 texCoords[4];
	prime_Vec2 texCoordsFlipY[4];
	prime_Vec2 texCoordsFlipX[4];
	prime_Vec2 texCoordsFlipXY[4];

	SpriteVertex* vertexbufferBase = nullptr;
	SpriteVertex* vertexbufferPtr = nullptr;
	std::array<prime_Texture2D*, PRIME_MAX_TEXTURE_SLOTS> texSlots{};
	u32 texIndex = 1;
};

struct LineData
{
	prime_Vertexbuffer* vertexbuffer = nullptr;
	prime_Shader* shader = nullptr;
	u32 vertexCount = 0;

	LineVertex* vertexbufferBase = nullptr;
	LineVertex* vertexbufferPtr = nullptr;
};

struct prime_Renderer2D
{
	prime_Device* device = nullptr;
	prime_Context* context = nullptr;
	prime_Uniformbuffer* uniformbuffer = nullptr;
	prime_Viewport viewport;
	SpriteData spriteData;
	LineData lineData;
	prime_Color drawColor;
};

static void 
setProjectionMatrix(prime_Renderer2D* ren)
{
	const prime_Viewport& viewport = prime_Renderer2DGetViewport(ren);
	prime_Mat4 matrix = prime_Mat4Orthographic(
		viewport.x,
		(f32)viewport.width,
		(f32)viewport.height,
		viewport.y,
		-1.0f,
		1.0f);

	prime_UniformbufferBind(ren->uniformbuffer);
	prime_UniformbufferSetData(ren->uniformbuffer, &matrix, sizeof(prime_Mat4));
}

static void
initSprites(prime_Renderer2D* ren)
{
	prime_BufferLayout* layout = nullptr;
	layout = prime_BufferLayoutCreate();
	prime_BufferElementAdd(layout, prime_BufferElementCreate(prime_DataTypeFloat2));
	prime_BufferElementAdd(layout, prime_BufferElementCreate(prime_DataTypeFloat4));
	prime_BufferElementAdd(layout, prime_BufferElementCreate(prime_DataTypeFloat2));
	prime_BufferElementAdd(layout, prime_BufferElementCreate(prime_DataTypeFloat));

	u32 max_indices = PRIME_MAX_RENDERER2D_SPRITES * 6;
	u32 max_vertices = PRIME_MAX_RENDERER2D_SPRITES * 4;

	u32* indices = (u32*)prime_MemAlloc(sizeof(u32) * max_indices);
	u32 offset = 0;
	for (u32 i = 0; i < max_indices; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	ren->spriteData.vertexbuffer = prime_VertexbufferCreate(
		ren->device,
		nullptr,
		max_vertices * sizeof(SpriteVertex),
		prime_VertexbufferTypeDynamic
	);

	prime_BufferLayoutSet(ren->spriteData.vertexbuffer, layout);
	ren->spriteData.vertexbufferBase = (SpriteVertex*)prime_MemAlloc(sizeof(SpriteVertex) * max_vertices);

	ren->spriteData.indexbuffer = prime_IndexbufferCreate(
		ren->device, indices, max_indices);

	ren->spriteData.shader = prime_ShaderCreate(ren->device,
		s_SpriteVertexSource, s_SpritePixelSource, false);

	ren->spriteData.vertices[0] = prime_Vec4Create(0.0f, 0.0f, 0.0f, 1.0f);
	ren->spriteData.vertices[1] = prime_Vec4Create(1.0f, 0.0f, 0.0f, 1.0f);
	ren->spriteData.vertices[2] = prime_Vec4Create(1.0f, 1.0f, 0.0f, 1.0f);
	ren->spriteData.vertices[3] = prime_Vec4Create(0.0f, 1.0f, 0.0f, 1.0f);

	ren->spriteData.texCoords[0] = prime_Vec2Create(0.0f, 0.0f);
	ren->spriteData.texCoords[1] = prime_Vec2Create(1.0f, 0.0f);
	ren->spriteData.texCoords[2] = prime_Vec2Create(1.0f, 1.0f);
	ren->spriteData.texCoords[3] = prime_Vec2Create(0.0f, 1.0f);

	ren->spriteData.texCoordsFlipX[0] = prime_Vec2Create(1.0f, 0.0f);
	ren->spriteData.texCoordsFlipX[1] = prime_Vec2Create(0.0f, 0.0f);
	ren->spriteData.texCoordsFlipX[2] = prime_Vec2Create(0.0f, 1.0f);
	ren->spriteData.texCoordsFlipX[3] = prime_Vec2Create(1.0f, 1.0f);

	ren->spriteData.texCoordsFlipY[0] = prime_Vec2Create(0.0f, 1.0f);
	ren->spriteData.texCoordsFlipY[1] = prime_Vec2Create(1.0f, 1.0f);
	ren->spriteData.texCoordsFlipY[2] = prime_Vec2Create(1.0f, 0.0f);
	ren->spriteData.texCoordsFlipY[3] = prime_Vec2Create(0.0f, 0.0f);

	ren->spriteData.texCoordsFlipXY[0] = prime_Vec2Create(1.0f, 1.0f);
	ren->spriteData.texCoordsFlipXY[1] = prime_Vec2Create(0.0f, 1.0f);
	ren->spriteData.texCoordsFlipXY[2] = prime_Vec2Create(0.0f, 0.0f);
	ren->spriteData.texCoordsFlipXY[3] = prime_Vec2Create(1.0f, 0.0f);

	prime_ShaderBind(ren->spriteData.shader);

	i32 samplers[PRIME_MAX_TEXTURE_SLOTS]{};
	for (u32 i = 0; i < PRIME_MAX_TEXTURE_SLOTS; i++) { samplers[i] = i; }
	prime_ShaderSetIntArray(ren->spriteData.shader, "u_Textures", samplers, PRIME_MAX_TEXTURE_SLOTS);

	prime_ShaderUnbind(ren->spriteData.shader);

	ren->spriteData.texSlots[0] = prime_Texture2DCreate(
		ren->device,
		1,
		1,
		prime_Texture2DFormatRGBA8,
		false
	);

	prime_BufferLayoutDestroy(layout);
	prime_MemFree(indices, sizeof(u32) * max_indices);
}

static void
initLines(prime_Renderer2D* ren)
{
	prime_BufferLayout* layout = nullptr;
	layout = prime_BufferLayoutCreate();
	prime_BufferElementAdd(layout, prime_BufferElementCreate(prime_DataTypeFloat2));
	prime_BufferElementAdd(layout, prime_BufferElementCreate(prime_DataTypeFloat4));

	u32 max_vertices = PRIME_MAX_RENDERER2D_SPRITES * 2;

	ren->lineData.vertexbuffer = prime_VertexbufferCreate(
		ren->device,
		nullptr,
		max_vertices * sizeof(LineVertex),
		prime_VertexbufferTypeDynamic
	);

	prime_VertexbufferBind(ren->lineData.vertexbuffer);
	prime_BufferLayoutSet(ren->lineData.vertexbuffer, layout);
	ren->lineData.vertexbufferBase = (LineVertex*)prime_MemAlloc(sizeof(LineVertex) * max_vertices);

	ren->lineData.shader = prime_ShaderCreate(ren->device,
		s_LineVertexSource, s_LinePixelSource, false);

	prime_ContextSetLinesWidth(ren->context, 4.0f);
	prime_ContextSetAntiAliasing(ren->context, true);
	prime_BufferLayoutDestroy(layout);
}

static f32 
getTexture2DIndex(prime_Renderer2D* ren, prime_Texture2D* texture2d)
{
	f32 tex_index = 0.0f;
	for (u32 i = 1; i < ren->spriteData.texIndex; i++) {
		if (prime_Texture2DGetHandle(ren->spriteData.texSlots[i]) == prime_Texture2DGetHandle(texture2d)) {
			tex_index = (f32)i;
			break;
		}
	}

	if (tex_index == 0.0f) {
		tex_index = (f32)ren->spriteData.texIndex;
		ren->spriteData.texSlots[ren->spriteData.texIndex] = texture2d;
		ren->spriteData.texIndex++;
	}
	return tex_index;
}

prime_Renderer2D*
prime_Renderer2DCreate(prime_Device* device, prime_Window* window)
{
	prime_Renderer2D* ren = (prime_Renderer2D*)prime_MemAlloc(sizeof(prime_Renderer2D));
	ren->context = prime_ContextCreate(device, window);
	ren->viewport.width = prime_WindowGetWidth(window);
	ren->viewport.height = prime_WindowGetHeight(window);
	ren->device = device;
	initSprites(ren);
	initLines(ren);
	prime_ContextMakeActive(ren->context);

	ren->uniformbuffer = prime_UniformbufferCreate(device, sizeof(prime_Mat4), 0);
	setProjectionMatrix(ren);

	ren->drawColor = prime_ColorFromF32(0.0f, 0.0f, 0.0f, 1.0f);

	return ren;
}

void
prime_Renderer2DDestroy(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	prime_ContextDestroy(renderer2d->context);
	prime_UniformbufferDestroy(renderer2d->uniformbuffer);

	// sprite
	prime_VertexbufferDestroy(renderer2d->spriteData.vertexbuffer);
	prime_IndexbufferDestroy(renderer2d->spriteData.indexbuffer);
	prime_ShaderDestroy(renderer2d->spriteData.shader);
	prime_MemFree(renderer2d->spriteData.vertexbufferBase,
		sizeof(SpriteVertex) * PRIME_MAX_RENDERER2D_SPRITES * 4);

	// line
	prime_VertexbufferDestroy(renderer2d->lineData.vertexbuffer);
	prime_ShaderDestroy(renderer2d->lineData.shader);
	prime_MemFree(renderer2d->lineData.vertexbufferBase,
		sizeof(LineVertex) * PRIME_MAX_RENDERER2D_SPRITES * 2);
	
	renderer2d->device = nullptr;
	renderer2d->context = nullptr;
	renderer2d->uniformbuffer = nullptr;
	renderer2d->spriteData.indexbuffer = nullptr;
	renderer2d->spriteData.vertexbuffer = nullptr;
	renderer2d->spriteData.shader = nullptr;
	prime_MemFree(renderer2d, sizeof(prime_Renderer2D));
}

void
prime_Renderer2DSetClearColor(prime_Renderer2D* renderer2d, const prime_Color& color)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	prime_ContextSetClearColor(renderer2d->context, color);
}

void 
prime_Renderer2DSetDrawColor(prime_Renderer2D* renderer2d, const prime_Color& color)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	renderer2d->drawColor = color;
}

void 
prime_Renderer2DSetLinesWidth(prime_Renderer2D* renderer2d, f32 width)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	prime_ContextSetLinesWidth(renderer2d->context, width);
}

void 
prime_Renderer2DSetAntiAliasing(prime_Renderer2D* renderer2d, b8 anti_aliasing)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	prime_ContextSetAntiAliasing(renderer2d->context, anti_aliasing);
}

void
prime_Renderer2DSetVsync(prime_Renderer2D* renderer2d, b8 vsync)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	prime_ContextSetVsync(renderer2d->context, vsync);
}

void
prime_Renderer2DSetViewport(prime_Renderer2D* renderer2d, const prime_Viewport& viewport)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	renderer2d->viewport = viewport;
	prime_ContextSetViewport(renderer2d->context, &viewport);
}

void
prime_Renderer2DClear(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	prime_ContextClear(renderer2d->context);
}

void
prime_Renderer2DBegin(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");

	// sprite
	renderer2d->spriteData.texIndex = 1;
	renderer2d->spriteData.indexCount = 0;
	renderer2d->spriteData.vertexbufferPtr = renderer2d->spriteData.vertexbufferBase;

	// line
	renderer2d->lineData.vertexCount = 0;
	renderer2d->lineData.vertexbufferPtr = renderer2d->lineData.vertexbufferBase;
}

void
prime_Renderer2DEnd(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");

	if (renderer2d->spriteData.indexCount)
	{
		u32 data_size = (u32)((u8*)renderer2d->spriteData.vertexbufferPtr - (u8*)renderer2d->spriteData.vertexbufferBase);
		prime_VertexbufferBind(renderer2d->spriteData.vertexbuffer);
		prime_VertexbufferSetData(
			renderer2d->spriteData.vertexbuffer,
			renderer2d->spriteData.vertexbufferBase,
			data_size);

		prime_ShaderBind(renderer2d->spriteData.shader);

		for (u32 i = 0; i < renderer2d->spriteData.texIndex; i++) {
			prime_Texture2DBind(renderer2d->spriteData.texSlots[i], i);
		}

		prime_ContextDrawIndexed(
			renderer2d->context, prime_DrawModeTriangles, 
			renderer2d->spriteData.indexCount);
	}

	if (renderer2d->lineData.vertexCount)
	{
		u32 data_size = (u32)((u8*)renderer2d->lineData.vertexbufferPtr - (u8*)renderer2d->lineData.vertexbufferBase);
		prime_VertexbufferBind(renderer2d->lineData.vertexbuffer);
		prime_VertexbufferSetData(
			renderer2d->lineData.vertexbuffer,
			renderer2d->lineData.vertexbufferBase,
			data_size);

		prime_ShaderBind(renderer2d->lineData.shader);
		prime_ContextDrawIndexed(
			renderer2d->context, prime_DrawModeLines,
			renderer2d->lineData.vertexCount);
	}
}

void
prime_Renderer2DDrawRect(prime_Renderer2D* renderer2d, const prime_Rect2D& rect)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");

	prime_Mat4 translation = prime_Mat4Translation({ rect.x, rect.y, 0.0f });
	prime_Mat4 scale = prime_Mat4Scale({ rect.width, rect.height, 1.0f });
	prime_Mat4 transform = translation * scale;

	for (size_t i = 0; i < 4; i++)
	{
		prime_Vec4 position = transform * renderer2d->spriteData.vertices[i];
		renderer2d->spriteData.vertexbufferPtr->position.x = position.x;
		renderer2d->spriteData.vertexbufferPtr->position.y = position.y;

		renderer2d->spriteData.vertexbufferPtr->color = renderer2d->drawColor;

		renderer2d->spriteData.vertexbufferPtr->texCoords = renderer2d->spriteData.texCoords[i];

		renderer2d->spriteData.vertexbufferPtr->tex_index = 0.0f;

		renderer2d->spriteData.vertexbufferPtr++;
	}
	renderer2d->spriteData.indexCount += 6;
}

void 
prime_Renderer2DDrawRectEx(
	prime_Renderer2D* renderer2d, 
	const prime_Rect2D& rect, 
	f32 rotation, 
	prime_Anchor anchor)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");

	f32 origin_x = 0.0f;
	f32 origin_y = 0.0f;

	if (rotation) {
		switch (anchor)
		{
		case prime_AnchorTopLeft: {
			origin_x = 0.0f;
			origin_y = 0.0f;
			break;
		}
		case prime_AnchorCenter: {
			origin_x = rect.width / 2.0f;
			origin_y = rect.height / 2.0f;
			break;
		}
	}

	}

	prime_Mat4 translation = prime_Mat4Translation({ rect.x + origin_x, rect.y + origin_y, 0.0f });
	prime_Mat4 translation2 = prime_Mat4Translation({ -origin_x, -origin_y, 0.0f });
	prime_Mat4 rot = prime_Mat4RotationZ(prime_MathsDegreeToRadians(rotation));
	prime_Mat4 scale = prime_Mat4Scale({ rect.width, rect.height, 1.0f });
	prime_Mat4 transform = translation * rot * translation2 * scale;

	for (size_t i = 0; i < 4; i++)
	{
		prime_Vec4 position = transform * renderer2d->spriteData.vertices[i];
		renderer2d->spriteData.vertexbufferPtr->position.x = position.x;
		renderer2d->spriteData.vertexbufferPtr->position.y = position.y;

		renderer2d->spriteData.vertexbufferPtr->color = renderer2d->drawColor;

		renderer2d->spriteData.vertexbufferPtr->texCoords = renderer2d->spriteData.texCoords[i];

		renderer2d->spriteData.vertexbufferPtr->tex_index = 0.0f;

		renderer2d->spriteData.vertexbufferPtr++;
	}
	renderer2d->spriteData.indexCount += 6;
}

void
prime_Renderer2DDrawSprite(prime_Renderer2D* renderer2d, const prime_Rect2D& rect, prime_Texture2D* texture2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");

	prime_Mat4 translation = prime_Mat4Translation({ rect.x, rect.y, 0.0f });
	prime_Mat4 scale = prime_Mat4Scale({ rect.width, rect.height, 1.0f });
	prime_Mat4 transform = translation * scale;

	f32 tex_index = getTexture2DIndex(renderer2d, texture2d);

	for (size_t i = 0; i < 4; i++)
	{
		prime_Vec4 position = transform * renderer2d->spriteData.vertices[i];
		renderer2d->spriteData.vertexbufferPtr->position.x = position.x;
		renderer2d->spriteData.vertexbufferPtr->position.y = position.y;

		renderer2d->spriteData.vertexbufferPtr->color = prime_ColorFromF32(1.0f, 1.0f, 1.0f, 1.0f);

		renderer2d->spriteData.vertexbufferPtr->texCoords = renderer2d->spriteData.texCoords[i];

		renderer2d->spriteData.vertexbufferPtr->tex_index = tex_index;

		renderer2d->spriteData.vertexbufferPtr++;
	}
	renderer2d->spriteData.indexCount += 6;
}

void
prime_Renderer2DDrawSpriteEx(
	prime_Renderer2D* renderer2d,
	const prime_Rect2D& rect,
	prime_Texture2D* texture2d,
	f32 rotation,
	prime_Anchor anchor,
	b8 flip_x,
	b8 flip_y,
	const prime_Color& tint_color)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");

	f32 origin_x = 0.0f;
	f32 origin_y = 0.0f;
	if (rotation) {
		switch (anchor)
		{
		case prime_AnchorTopLeft: {
			origin_x = 0.0f;
			origin_y = 0.0f;
			break;
		}
		case prime_AnchorCenter: {
			origin_x = rect.width / 2.0f;
			origin_y = rect.height / 2.0f;
			break;
		}

		}
	}

	prime_Mat4 translation = prime_Mat4Translation({ rect.x + origin_x, rect.y + origin_y, 0.0f });
	prime_Mat4 translation2 = prime_Mat4Translation({ -origin_x, -origin_y, 0.0f });
	prime_Mat4 rot = prime_Mat4RotationZ(prime_MathsDegreeToRadians(rotation));
	prime_Mat4 scale = prime_Mat4Scale({ rect.width, rect.height, 1.0f });
	prime_Mat4 transform = translation * rot * translation2 * scale;

	f32 tex_index = getTexture2DIndex(renderer2d, texture2d);

	for (size_t i = 0; i < 4; i++)
	{
		prime_Vec4 position = transform * renderer2d->spriteData.vertices[i];
		renderer2d->spriteData.vertexbufferPtr->position.x = position.x;
		renderer2d->spriteData.vertexbufferPtr->position.y = position.y;

		renderer2d->spriteData.vertexbufferPtr->color = tint_color;

		if (flip_x && flip_y) {
			renderer2d->spriteData.vertexbufferPtr->texCoords = renderer2d->spriteData.texCoordsFlipXY[i];
		}
		else if (flip_x && flip_y == false) {
			renderer2d->spriteData.vertexbufferPtr->texCoords = renderer2d->spriteData.texCoordsFlipX[i];
		}
		else if (flip_y && flip_x == false) {
			renderer2d->spriteData.vertexbufferPtr->texCoords = renderer2d->spriteData.texCoordsFlipY[i];
		}
		else if (flip_y == false && flip_x == false) {
			renderer2d->spriteData.vertexbufferPtr->texCoords = renderer2d->spriteData.texCoords[i];
		}

		renderer2d->spriteData.vertexbufferPtr->tex_index = tex_index;

		renderer2d->spriteData.vertexbufferPtr++;
	}
	renderer2d->spriteData.indexCount += 6;
}

void 
prime_Renderer2DDrawLine(prime_Renderer2D* renderer2d, const prime_Vec2& point1, const prime_Vec2& point2)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");

	// point 1
	renderer2d->lineData.vertexbufferPtr->position.x = point1.x;
	renderer2d->lineData.vertexbufferPtr->position.y = point1.y;
	renderer2d->lineData.vertexbufferPtr->color = renderer2d->drawColor;
	renderer2d->lineData.vertexbufferPtr++;

	// point 2
	renderer2d->lineData.vertexbufferPtr->position.x = point2.x;
	renderer2d->lineData.vertexbufferPtr->position.y = point2.y;
	renderer2d->lineData.vertexbufferPtr->color = renderer2d->drawColor;
	renderer2d->lineData.vertexbufferPtr++;

	renderer2d->lineData.vertexCount += 2;
}

void
prime_Renderer2DPresent(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	prime_ContextSwapbuffers(renderer2d->context);
}

const prime_Viewport&
prime_Renderer2DGetViewport(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	return renderer2d->viewport;
}

const prime_Color&
prime_Renderer2DGetDrawColor(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	return renderer2d->drawColor;
}

f32
prime_Renderer2DGetLinesWidth(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	return prime_ContextGetLinesWidth(renderer2d->context);
}

b8
prime_Renderer2DGetAntiAliasing(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	return prime_ContextGetAntiAliasing(renderer2d->context);
}

b8
prime_Renderer2DGetVsync(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	return prime_ContextGetVSync(renderer2d->context);
}