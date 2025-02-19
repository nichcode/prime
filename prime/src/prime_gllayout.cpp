
#include "prime_gllayout.h"
#include "prime/prime_memory.h"
#include "prime/prime_log.h"
#include "prime/prime_string.h"
#include "prime/prime_filesystem.h"
#include "glad/glad.h"

#include <vector>

struct glLayout
{
    GLuint vertexarray = 0;
	GLuint vertexbuffer = 0;
	GLuint indexbuffer = 0;
	GLuint vertexShader = 0, pixelShader = 0;
	GLuint shader = 0;
	b8 shaderEmpty = false;
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

static GLuint createShader(GLint type, const char* source)
{
	int status = GL_FALSE;
	int max_length = 0;

	GLuint shader = glCreateShader(type);
	const char* gl_source = source;
	glShaderSource(shader, 1, &gl_source, 0);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

	if (status != GL_TRUE)
	{
		std::vector<GLchar> info_log(max_length);
		glGetShaderInfoLog(shader, max_length, &max_length, info_log.data());

		if (type == GL_VERTEX_SHADER)
		{
			char* msg = primeStringFormat("Vertex shader compilation error : %s", info_log.data());
			PERROR(msg);
		}
		else if (type == GL_FRAGMENT_SHADER)
		{
			char* msg = primeStringFormat("Fragment shader compilation error : %s", info_log.data());
			PERROR(msg);
		}
		PASSERT(false);
	}
	return shader;
}

static GLuint createProgram(GLuint v_shader, GLuint f_shader)
{
	int status = GL_FALSE;
	int max_length = 0;

	GLuint program = 0;

	program = glCreateProgram();
	glAttachShader(program, v_shader);
	glAttachShader(program, f_shader);
	glLinkProgram(program);

	glValidateProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
	if (status != GL_TRUE)
	{
		std::vector<GLchar> info_log(max_length);
		glGetProgramInfoLog(program, max_length, &max_length, info_log.data());

		char* msg = primeStringFormat("shader link error : %s", info_log.data());
		PERROR(msg);

		glDeleteProgram(program);
		program = 0;
		PASSERT(false);
	}
	glDeleteShader(v_shader);
	glDeleteShader(f_shader);

	return program;
}

void*
primeGLLayoutCreate(const primeLayoutDesc* desc, b8 shader_empty)
{
    glLayout* layout = nullptr;
	layout = (glLayout*)primeMemoryAlloc(sizeof(glLayout));
	PASSERT_MSG(layout, "glLayout creation failed");

    glGenVertexArrays(1, &layout->vertexarray);
	glBindVertexArray(layout->vertexarray);

    glGenBuffers(1, &layout->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, layout->vertexbuffer);
	if (desc->vbo.type == primeBufferTypeDynamic) {
		glBufferData(GL_ARRAY_BUFFER, desc->vbo.size, desc->vbo.data, GL_DYNAMIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, desc->vbo.size, desc->vbo.data, GL_STATIC_DRAW);
	}

	glGenBuffers(1, &layout->indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, layout->indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, desc->ibo.count * sizeof(u32), desc->ibo.indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if (!shader_empty) {
		if (desc->shader.load) {
			char* v_src = primeFilesystemLoad(desc->shader.vertex);
			PASSERT_MSG(v_src, "vertex source is null");

			char* p_src = primeFilesystemLoad(desc->shader.pixel);
			PASSERT_MSG(p_src, "pixel source is null");

			layout->vertexShader = createShader(GL_VERTEX_SHADER, v_src);
			layout->pixelShader = createShader(GL_FRAGMENT_SHADER, p_src);

			primeStringFree(v_src);
			primeStringFree(p_src);
		}
		else {
			layout->vertexShader = createShader(GL_VERTEX_SHADER, desc->shader.vertex);
			layout->pixelShader = createShader(GL_FRAGMENT_SHADER, desc->shader.pixel);
		}

		layout->shader = createProgram(layout->vertexShader, layout->pixelShader);
	}
	
	layout->shaderEmpty = shader_empty;
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

	if (!gl_layout->shaderEmpty) {
		glDeleteProgram(gl_layout->shader);
		gl_layout->shader = 0;
		gl_layout->vertexShader = 0;
		gl_layout->indexbuffer = 0;
	}

    primeMemoryFree(layout, sizeof(glLayout));
}

void
primeGLLayoutBind(void* layout)
{
    glLayout* gl_layout = (glLayout*)layout;
    glBindVertexArray(gl_layout->vertexarray);
	glBindBuffer(GL_ARRAY_BUFFER, gl_layout->vertexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_layout->indexbuffer);
	if (!gl_layout->shaderEmpty) {
		glUseProgram(gl_layout->shader);
	}
}

void
primeGLLayoutUnbind(void* layout)
{
	glLayout* gl_layout = (glLayout*)layout;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if (!gl_layout->shaderEmpty) {
		glUseProgram(0);
	}
}

void
primeGLLayoutSetData(void* layout, const void* data, u32 size)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void
primeGLLayoutPush(void* layout, u32 index, u32 count, primeType type, u64 offset, u32 stride, u32 divisor)
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
		
		glVertexAttribDivisor(index, divisor);
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
		
		glVertexAttribDivisor(index, divisor);
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
			glVertexAttribDivisor(index, divisor);
		}
		break;
	}

	}
}

void
primeGLLayoutSetInt(void* layout, const char* name, i32 data)
{
	glLayout* gl_layout = (glLayout*)layout;
	if (!gl_layout->shaderEmpty) {
		GLint location = glGetUniformLocation(gl_layout->shader, name);
		glUniform1i(location, data);
	}
}

void
primeGLLayoutSetIntArray(void* layout, const char* name, i32* data, u32 count)
{
	glLayout* gl_layout = (glLayout*)layout;
	if (!gl_layout->shaderEmpty) {
		GLint location = glGetUniformLocation(gl_layout->shader, name);
	    glUniform1iv(location, count, data);
	}
}

void
primeGLLayoutSetFloat(void* layout, const char* name, f32 data)
{
	glLayout* gl_layout = (glLayout*)layout;
	if (!gl_layout->shaderEmpty) {
		GLint location = glGetUniformLocation(gl_layout->shader, name);
		glUniform1f(location, data);
	}
}

void
primeGLLayoutSetFloat2(void* layout, const char* name, primeVec2 data)
{
	glLayout* gl_layout = (glLayout*)layout;
	if (!gl_layout->shaderEmpty) {
		GLint location = glGetUniformLocation(gl_layout->shader, name);
		glUniform2f(location, data.x, data.y);
	}
}

void
primeGLLayoutSetFloat3(void* layout, const char* name, primeVec3 data)
{
	glLayout* gl_layout = (glLayout*)layout;
	if (!gl_layout->shaderEmpty) {
		GLint location = glGetUniformLocation(gl_layout->shader, name);
		glUniform3f(location, data.x, data.y, data.y);
	}
}

void
primeGLLayoutSetFloat4(void* layout, const char* name, primeVec4 data)
{
	glLayout* gl_layout = (glLayout*)layout;
	if (!gl_layout->shaderEmpty) {
		GLint location = glGetUniformLocation(gl_layout->shader, name);
		glUniform4f(location, data.x, data.y, data.z, data.w);
	}
}

void
primeGLLayoutSetMat4(void* layout, const char* name, primeMat4 data)
{
	glLayout* gl_layout = (glLayout*)layout;
	if (!gl_layout->shaderEmpty) {
		GLint location = glGetUniformLocation(gl_layout->shader, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, data.data);
	}
}