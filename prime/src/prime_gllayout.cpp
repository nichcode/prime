
#include "prime_gllayout.h"
#include "prime/prime_memory.h"
#include "prime/prime_log.h"
#include "glad/glad.h"

struct glLayout
{
    u32 vertexarray = 0;
	u32 vertexbuffer = 0;
	u32 indexbuffer = 0;
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
primeGLLayoutCreate(primeVertexbufferDesc vbo, primeIndexbufferDesc ibo)
{
    glLayout* layout = nullptr;
	layout = (glLayout*)primeMemoryAlloc(sizeof(glLayout));
	PASSERT_MSG(layout, "glLayout creation failed");

    glGenVertexArrays(1, &layout->vertexarray);
	glBindVertexArray(layout->vertexarray);

    glGenBuffers(1, &layout->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, layout->vertexbuffer);
	if (vbo.type == primeBufferTypeDynamic) {
		glBufferData(GL_ARRAY_BUFFER, vbo.size, vbo.data, GL_DYNAMIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, vbo.size, vbo.data, GL_STATIC_DRAW);
	}

	glGenBuffers(1, &layout->indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, layout->indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibo.count * sizeof(u32), ibo.indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return layout;
}

void
primeGLLayoutDestroy(void* layout)
{
    glLayout* gl_layout = (glLayout*)layout;
    glDeleteVertexArrays(1, &gl_layout->vertexarray);
	glDeleteBuffers(1, &gl_layout->vertexbuffer);
	glDeleteBuffers(1, &gl_layout->indexbuffer);
    gl_layout->vertexarray = 0;
    gl_layout->vertexbuffer = 0;
    gl_layout->indexbuffer = 0;
    primeMemoryFree(layout, sizeof(glLayout));
}

void
primeGLLayoutBind(void* layout)
{
    glLayout* gl_layout = (glLayout*)layout;
    glBindVertexArray(gl_layout->vertexarray);
	glBindBuffer(GL_ARRAY_BUFFER, gl_layout->vertexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_layout->indexbuffer);
}

void
primeGLLayoutUnbind(void* layout)
{
    glLayout* gl_layout = (glLayout*)layout;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void
primeGLLayoutSetData(void* layout, const void* data, u32 size)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
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