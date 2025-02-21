
#include "prime/prime_renderer2d.h"
#include "prime/prime_layout.h"
#include "prime/prime_constantbuffer.h"
#include "prime_shaders.h"
#include "prime/prime_window.h"
#include "prime/prime_context.h"
#include "prime/prime_log.h"

#include <array>

#define PMAX_SPRITES 10000

struct SpriteVertex
{
    primeVec2 position = primeVec2Create(0.0f, 0.0f);
    primeColor color = primeColorFromF32(1.0f, 1.0f, 1.0f, 1.0f);
    primeVec2 texCoords = primeVec2Create(0.0f, 0.0f);
	f32 texIndex = 0.0f;
};

struct SpriteData
{
    primeLayout* layout = nullptr;
	u32 indexCount = 0;
	primeVec4 vertices[4];

	primeVec2 texCoords[4];
	primeVec2 texCoordsFlipY[4];
	primeVec2 texCoordsFlipX[4];
	primeVec2 texCoordsFlipXY[4];
	std::array<primeTexture2D*, PMAX_TEXTURE_SLOTS> texSlots{};
	f32 texIndex = 1.0f;
	
	SpriteVertex* base = nullptr;
	SpriteVertex* ptr = nullptr;
};

struct primeRenderer2D
{
	primeDevice* device = nullptr;
	primeContext* context = nullptr;
	primeConstantbuffer* uniformBlock = nullptr;
	primeRect view;
	SpriteData spriteData;
};

static void 
setProjectionMatrix(primeRenderer2D* ren)
{
	const primeRect* view = primeRenderer2DGetView(ren);
	primeMat4 matrix = primeMat4Orthographic(
		view->x,
		(f32)view->width,
		(f32)view->height,
		view->y,
		-1.0f,
		1.0f);

	primeConstantbufferBind(ren->uniformBlock);
	primeConstantbufferSetData(ren->uniformBlock, &matrix, sizeof(primeMat4));
}

static void
initSprites(primeRenderer2D* ren)
{
	ren->spriteData.vertices[0] = primeVec4Create(0.0f, 0.0f, 0.0f, 1.0f);
	ren->spriteData.vertices[1] = primeVec4Create(1.0f, 0.0f, 0.0f, 1.0f);
	ren->spriteData.vertices[2] = primeVec4Create(1.0f, 1.0f, 0.0f, 1.0f);
	ren->spriteData.vertices[3] = primeVec4Create(0.0f, 1.0f, 0.0f, 1.0f);

	ren->spriteData.texCoords[0] = primeVec2Create(0.0f, 0.0f);
	ren->spriteData.texCoords[1] = primeVec2Create(1.0f, 0.0f);
	ren->spriteData.texCoords[2] = primeVec2Create(1.0f, 1.0f);
	ren->spriteData.texCoords[3] = primeVec2Create(0.0f, 1.0f);

	ren->spriteData.texCoordsFlipX[0] = primeVec2Create(1.0f, 0.0f);
	ren->spriteData.texCoordsFlipX[1] = primeVec2Create(0.0f, 0.0f);
	ren->spriteData.texCoordsFlipX[2] = primeVec2Create(0.0f, 1.0f);
	ren->spriteData.texCoordsFlipX[3] = primeVec2Create(1.0f, 1.0f);

	ren->spriteData.texCoordsFlipY[0] = primeVec2Create(0.0f, 1.0f);
	ren->spriteData.texCoordsFlipY[1] = primeVec2Create(1.0f, 1.0f);
	ren->spriteData.texCoordsFlipY[2] = primeVec2Create(1.0f, 0.0f);
	ren->spriteData.texCoordsFlipY[3] = primeVec2Create(0.0f, 0.0f);

	ren->spriteData.texCoordsFlipXY[0] = primeVec2Create(1.0f, 1.0f);
	ren->spriteData.texCoordsFlipXY[1] = primeVec2Create(0.0f, 1.0f);
	ren->spriteData.texCoordsFlipXY[2] = primeVec2Create(0.0f, 0.0f);
	ren->spriteData.texCoordsFlipXY[3] = primeVec2Create(1.0f, 0.0f);

	u32* indices = (u32*)primeMemoryAlloc(sizeof(u32) * PMAX_SPRITES * 6);
	u32 offset = 0;
	for (u32 i = 0; i < PMAX_SPRITES * 6; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

    primeVertexbufferDesc vbo;
    vbo.size = sizeof(SpriteVertex) * PMAX_SPRITES * 4;
    vbo.data = nullptr;
    vbo.type = primeBufferTypeDynamic;

    primeIndexbufferDesc ibo;
    ibo.count = PMAX_SPRITES * 6;
    ibo.indices = indices;

	primeShaderDesc shader_desc;
	shader_desc.load = false;
	shader_desc.pixel = s_SpritePixelSource;
	shader_desc.vertex = s_SpriteVertexSource;
	shader_desc.type = primeShaderTypeGLSL;

    primeLayoutDesc layout_desc;
    layout_desc.ibo = ibo;
    layout_desc.vbo = vbo;
	layout_desc.shader = shader_desc;

    ren->spriteData.layout = primeLayoutCreate(ren->device, &layout_desc);
    primeLayoutBind(ren->spriteData.layout);
    primeLayoutAdd(ren->spriteData.layout, primeTypeFloat2, PDIVISOR_DEFAULT);
    primeLayoutAdd(ren->spriteData.layout, primeTypeFloat4, PDIVISOR_DEFAULT);
    primeLayoutAdd(ren->spriteData.layout, primeTypeFloat2, PDIVISOR_DEFAULT);
    primeLayoutAdd(ren->spriteData.layout, primeTypeFloat, PDIVISOR_DEFAULT);
    primeLayoutSubmit(ren->spriteData.layout);

	i32 samplers[PMAX_TEXTURE_SLOTS]{};
	for (u32 i = 0; i < PMAX_TEXTURE_SLOTS; i++) { samplers[i] = i; }
	primeLayoutSetIntArray(ren->spriteData.layout, "u_Textures", samplers, PMAX_TEXTURE_SLOTS);

    primeLayoutUnbind(ren->spriteData.layout);

	ren->spriteData.base = (SpriteVertex*)primeMemoryAlloc(
		sizeof(SpriteVertex) * PMAX_SPRITES * 4
	);

	primeTexture2DDesc tex_desc;
	ren->spriteData.texSlots[0] = primeTexture2DCreate(ren->device, &tex_desc);

	primeMemoryFree(indices, sizeof(u32) * PMAX_SPRITES * 6);
}

static f32 
getTexture2DIndex(primeRenderer2D* ren, primeTexture2D* texture)
{
	f32 tex_index = 0.0f;
	for (u32 i = 1; i < ren->spriteData.texIndex; i++) {
		if (ren->spriteData.texSlots[i] == texture) {
			tex_index = (f32)i;
			break;
		}
	}

	if (tex_index == 0.0f) {
		tex_index = (f32)ren->spriteData.texIndex;
		ren->spriteData.texSlots[ren->spriteData.texIndex] = texture;
		ren->spriteData.texIndex++;
	}
	return tex_index;
}

primeRenderer2D*
primeRenderer2DCreate(primeDevice* device, primeWindow* window)
{
	primeRenderer2D* ren = (primeRenderer2D*)primeMemoryAlloc(sizeof(primeRenderer2D));
	ren->context = primeContextCreate(device, window);
	ren->view.width = primeWindowGetWidth(window);
	ren->view.height = primeWindowGetHeight(window);
	ren->device = device;
	initSprites(ren);
	primeContextMakeActive(ren->context);

	ren->uniformBlock = primeConstantbufferCreate(device, sizeof(primeMat4), 0);
	setProjectionMatrix(ren);
	return ren;
}

void
primeRenderer2DDestroy(primeRenderer2D* renderer)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	primeMemoryFree(
		renderer->spriteData.base,
	    sizeof(SpriteVertex) * PMAX_SPRITES * 4);

	renderer->device = nullptr;
	renderer->context = nullptr;
	renderer->uniformBlock = nullptr;
    renderer->spriteData.layout = nullptr;
	primeMemoryFree(renderer, sizeof(primeRenderer2D));
}

void
primeRenderer2DSetClearColor(primeRenderer2D* renderer, primeColor* color)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	primeContextSetClearColor(renderer->context, color);
}

void 
primeRenderer2DSetLinesWidth(primeRenderer2D* renderer, f32 width)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	primeContextSetLinesWidth(renderer->context, width);
}

void 
primeRenderer2DSetAntiAliasing(primeRenderer2D* renderer, b8 anti_aliasing)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	primeContextSetAntiAliasing(renderer->context, anti_aliasing);
}

void
primeRenderer2DSetVsync(primeRenderer2D* renderer, b8 vsync)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	primeContextSetVsync(renderer->context, vsync);
}

void
primeRenderer2DSetView(primeRenderer2D* renderer, primeRect* viewport)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	renderer->view = *viewport;
	primeContextSetViewport(renderer->context, viewport);
	setProjectionMatrix(renderer);
}

void 
primeRenderer2DSetScale(primeRenderer2D* renderer, primeVec2 scale)
{
	PASSERT_MSG(scale.x, "Scale x invalid");
	PASSERT_MSG(scale.y, "Scale x invalid");

	const primeRect& view = renderer->view;
	f32 width = (f32)view.width / scale.x;
	f32 height = (f32)view.height / scale.y;

	primeMat4 matrix = primeMat4Orthographic(
		view.x,
		width,
		height,
		view.y,
		-1.0f,
		1.0f);

	primeConstantbufferBind(renderer->uniformBlock);
	primeConstantbufferSetData(renderer->uniformBlock, &matrix, sizeof(primeMat4));
}

void
primeRenderer2DClear(primeRenderer2D* renderer)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	primeContextClear(renderer->context);
}

void
primeRenderer2DBegin(primeRenderer2D* renderer)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	renderer->spriteData.ptr = renderer->spriteData.base;
	renderer->spriteData.indexCount = 0;

	renderer->spriteData.texIndex = 1.0f;
}

void
primeRenderer2DEnd(primeRenderer2D* renderer)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	if (renderer->spriteData.indexCount) {
        primeLayoutBind(renderer->spriteData.layout);
		u32 size = (u32)((u8*)renderer->spriteData.ptr - (u8*)renderer->spriteData.base);

		primeLayoutSetData(
			renderer->spriteData.layout, 
			renderer->spriteData.base,
			size);

		for (u32 i = 0; i < renderer->spriteData.texIndex; i++) {
			primeTexture2DBind(renderer->spriteData.texSlots[i], i);
		}

        primeContextDrawElements(
			renderer->context, 
			primeDrawModeTriangles,
			renderer->spriteData.indexCount);
	}
}

void
primeRenderer2DDrawRect(primeRenderer2D* renderer, const primeRect* rect, primeColor* color)
{
	PASSERT_MSG(renderer, "Renderer2D is null");

	primeMat4 translation = primeMat4Translation({ rect->x, rect->y, 0.0f });
	primeMat4 scale = primeMat4Scale({ rect->width, rect->height, 1.0f });
	primeMat4 transform = translation * scale;

	for (u64 i = 0; i < 4; i++) {
		primeVec4 position = transform * renderer->spriteData.vertices[i];
		renderer->spriteData.ptr->position.x = position.x;
		renderer->spriteData.ptr->position.y = position.y;

		renderer->spriteData.ptr->color = *color;

		renderer->spriteData.ptr->texCoords = renderer->spriteData.texCoords[i];
		renderer->spriteData.ptr->texIndex = 0.0f;

		renderer->spriteData.ptr++;
	}
	renderer->spriteData.indexCount += 6;
}

void
primeRenderer2DDrawRectEx(primeRenderer2D* renderer, const primeRect* rect, 
                          primeColor* color, f32 rotation, primeAnchor anchor)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	if (rotation) {
		f32 origin_x = 0.0f;
	    f32 origin_y = 0.0f;

		switch (anchor) {
		    case primeAnchorTopLeft: {
				origin_x = 0.0f;
			    origin_y = 0.0f;
		    }
		    break;

		    case primeAnchorCenter: {
				origin_x = rect->width / 2.0f;
			    origin_y = rect->height / 2.0f;
			}
			break;
		}

		primeMat4 offset = primeMat4Translation({ rect->x + origin_x, rect->y + origin_y, 0.0f });
		primeMat4 translation = primeMat4Translation({ -origin_x, -origin_y, 0.0f });
		primeMat4 rot = primeMat4RotationZ(primeMathDegreeToRadians(rotation));
		primeMat4 scale = primeMat4Scale({ rect->width, rect->height, 1.0f });
		primeMat4 transform = offset * rot * translation * scale;

		for (u64 i = 0; i < 4; i++) {
			primeVec4 position = transform * renderer->spriteData.vertices[i];
			renderer->spriteData.ptr->position.x = position.x;
			renderer->spriteData.ptr->position.y = position.y;

			renderer->spriteData.ptr->color = *color;

			renderer->spriteData.ptr->texCoords = renderer->spriteData.texCoords[i];
		    renderer->spriteData.ptr->texIndex = 0.0f;

			renderer->spriteData.ptr++;
		}
		renderer->spriteData.indexCount += 6;

	}
	else {
		primeRenderer2DDrawRect(renderer, rect, color);
	}
}

void
primeRenderer2DDrawSprite(primeRenderer2D* renderer, const primeRect* rect, primeTexture2D* texture)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	if (texture) {
		primeMat4 translation = primeMat4Translation({ rect->x, rect->y, 0.0f });
		primeMat4 scale = primeMat4Scale({ rect->width, rect->height, 1.0f });
		primeMat4 transform = translation * scale;

		f32 tex_index = getTexture2DIndex(renderer, texture);

		for (u64 i = 0; i < 4; i++) {
			primeVec4 position = transform * renderer->spriteData.vertices[i];
			renderer->spriteData.ptr->position.x = position.x;
			renderer->spriteData.ptr->position.y = position.y;

			renderer->spriteData.ptr->color = s_White;

			renderer->spriteData.ptr->texCoords = renderer->spriteData.texCoords[i];
			renderer->spriteData.ptr->texIndex = tex_index;

			renderer->spriteData.ptr++;
		}
		renderer->spriteData.indexCount += 6;

	}
	else {
		primeRenderer2DDrawRect(renderer, rect, PCOLOR_WHITE);
	}

}

PAPI void
primeRenderer2DDrawSpriteEx(primeRenderer2D* renderer, const primeRect* rect, 
                            primeTexture2D* texture, primeFlip flip,
							f32 rotation, primeAnchor anchor, primeColor* tint_color)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	if (rotation && texture) {
		f32 origin_x = 0.0f;
	    f32 origin_y = 0.0f;

		switch (anchor) {
		    case primeAnchorTopLeft: {
				origin_x = 0.0f;
			    origin_y = 0.0f;
		    }
		    break;

		    case primeAnchorCenter: {
				origin_x = rect->width / 2.0f;
			    origin_y = rect->height / 2.0f;
			}
			break;
		}

		primeMat4 offset = primeMat4Translation({ rect->x + origin_x, rect->y + origin_y, 0.0f });
		primeMat4 translation = primeMat4Translation({ -origin_x, -origin_y, 0.0f });
		primeMat4 rot = primeMat4RotationZ(primeMathDegreeToRadians(rotation));
		primeMat4 scale = primeMat4Scale({ rect->width, rect->height, 1.0f });
		primeMat4 transform = offset * rot * translation * scale;

		f32 tex_index = getTexture2DIndex(renderer, texture);

		for (u64 i = 0; i < 4; i++) {
			primeVec4 position = transform * renderer->spriteData.vertices[i];
			renderer->spriteData.ptr->position.x = position.x;
			renderer->spriteData.ptr->position.y = position.y;

			renderer->spriteData.ptr->color = *tint_color;

			if (flip == primeFlipNone) {
				renderer->spriteData.ptr->texCoords = renderer->spriteData.texCoords[i];
			}

			else if (flip == primeFlipX) {
				renderer->spriteData.ptr->texCoords = renderer->spriteData.texCoordsFlipX[i];
			}

			else if (flip == primeFlipY) {
				renderer->spriteData.ptr->texCoords = renderer->spriteData.texCoordsFlipY[i];
			}

			else {
				renderer->spriteData.ptr->texCoords = renderer->spriteData.texCoordsFlipXY[i];
			}

		    renderer->spriteData.ptr->texIndex = tex_index;

			renderer->spriteData.ptr++;
		}
		renderer->spriteData.indexCount += 6;

	}

	else if (texture) {
		primeMat4 translation = primeMat4Translation({ rect->x, rect->y, 0.0f });
		primeMat4 scale = primeMat4Scale({ rect->width, rect->height, 1.0f });
		primeMat4 transform = translation * scale;

		f32 tex_index = getTexture2DIndex(renderer, texture);

		for (u64 i = 0; i < 4; i++) {
			primeVec4 position = transform * renderer->spriteData.vertices[i];
			renderer->spriteData.ptr->position.x = position.x;
			renderer->spriteData.ptr->position.y = position.y;

			renderer->spriteData.ptr->color = *tint_color;

			if (flip == primeFlipNone) {
				renderer->spriteData.ptr->texCoords = renderer->spriteData.texCoords[i];
			}

			else if (flip == primeFlipX) {
				renderer->spriteData.ptr->texCoords = renderer->spriteData.texCoordsFlipX[i];
			}

			else if (flip == primeFlipY) {
				renderer->spriteData.ptr->texCoords = renderer->spriteData.texCoordsFlipY[i];
			}

			else {
				renderer->spriteData.ptr->texCoords = renderer->spriteData.texCoordsFlipXY[i];
			}

			renderer->spriteData.ptr->texIndex = tex_index;

			renderer->spriteData.ptr++;
		}
		renderer->spriteData.indexCount += 6;
	}
	
	else {
		primeRenderer2DDrawRectEx(renderer, rect, tint_color, rotation, anchor);
	}
}

void
primeRenderer2DPresent(primeRenderer2D* renderer)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	primeContextSwapbuffers(renderer->context);
}

const primeRect*
primeRenderer2DGetView(primeRenderer2D* renderer)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	return &renderer->view;
}

f32
primeRenderer2DGetLinesWidth(primeRenderer2D* renderer)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	return primeContextGetLinesWidth(renderer->context);
}

b8
primeRenderer2DGetAntiAliasing(primeRenderer2D* renderer)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	return primeContextGetAntiAliasing(renderer->context);
}

b8
primeRenderer2DGetVsync(primeRenderer2D* renderer)
{
	PASSERT_MSG(renderer, "Renderer2D is null");
	return primeContextGetVSync(renderer->context);
}