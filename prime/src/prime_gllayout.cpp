
#include "prime_gllayout.h"
#include "prime/prime_memory.h"
#include "prime/prime_log.h"
#include "glad/glad.h"

struct glLayout
{
    u32 vertexarray = 0;
};

static inline GLenum
typeToGLType(primeType type)
{
	switch (type)
	{
	case primeTypeInt:
	case primeTypeInt2:
	case primeTypeInt3:
	case primeTypeInt4:
		return GL_INT;

	case primeTypeFloat:
	case primeTypeFloat2:
	case primeTypeFloat3:
	case primeTypeFloat4:
	case primeTypeMat3:
	case primeTypeMat4:
		return GL_FLOAT;

	case primeTypeBool:
		return GL_BOOL;
	}
	return 0;
}

void*
primeGLLayoutCreate()
{
    glLayout* layout = nullptr;
	layout = (glLayout*)primeMemoryAlloc(sizeof(glLayout));
	PASSERT_MSG(layout, "glLayout creation failed");

    glGenVertexArrays(1, &layout->vertexarray);
	return layout;
}

void
primeGLLayoutDestroy(void* layout)
{
    glLayout* gl_layout = (glLayout*)layout;
    glDeleteVertexArrays(1, &gl_layout->vertexarray);
    gl_layout->vertexarray = 0;
    primeMemoryFree(layout, sizeof(glLayout));
}

void
primeGLLayoutBind(void* layout)
{
    glLayout* gl_layout = (glLayout*)layout;
    glBindVertexArray(gl_layout->vertexarray);
}

void
primeGLLayoutUnbind(void* layout)
{
    glLayout* gl_layout = (glLayout*)layout;
    glBindVertexArray(0);
}

void
primeGLLayoutPush(void* layout, u32 index, u32 count, primeType type, u64 offset, u32 stride)
{
    switch (type) {
	case primeTypeFloat:
	case primeTypeFloat2:
	case primeTypeFloat3:
	case primeTypeFloat4:
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			count,
			typeToGLType(type),
			GL_FALSE,
			stride,
			(const void*)offset);
		break;
	}
	
    case primeTypeInt:
	case primeTypeInt2:
	case primeTypeInt3:
	case primeTypeInt4:
	case primeTypeBool:
	{
		glEnableVertexAttribArray(index);
		glVertexAttribIPointer(index,
			count,
			typeToGLType(type),
			stride,
			(const void*)offset);
		break;
	}
	
    case primeTypeMat3:
	case primeTypeMat4:
	{
		u8 count = count;
		for (u8 i = 0; i < count; i++)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				count,
				typeToGLType(type),
				GL_FALSE,
				stride,
				(const void*)(offset + sizeof(f32) * count * i));
			glVertexAttribDivisor(index, 1);
		}
		break;
	}

	}
}