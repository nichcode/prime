#pragma once

#include "prime_opengl_shader.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"
#include "prime/prime_string.h"
#include "prime/prime_math.h"
#include "prime/prime_filesystem.h"

#include "glad/glad.h"

#include <vector>

struct gl_Shader
{
	GLuint vertex_shader = 0;
	GLuint fragment_shader = 0;
	GLuint id = 0;
};

static GLuint createShader(i32 type, const char* source)
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
			prime_String* msg = prime_StringFormat("Vertex shader compilation error : %s", info_log.data());
			PRIME_LOG_STRING(msg);
		}
		else if (type == GL_FRAGMENT_SHADER)
		{
			prime_String* msg = prime_StringFormat("Fragment shader compilation error : %s", info_log.data());
			PRIME_LOG_STRING(msg);
		}
		PRIME_ASSERT(false);
	}
	return shader;
}

void*
gl_ShaderCreate(const char* vertex_shader, const char* pixel_shader, b8 load)
{
	gl_Shader* handle = nullptr;
	handle = (gl_Shader*)prime_MemAlloc(sizeof(gl_Shader));

	if(load) {
		const char* vertex_src = prime_StringGetCstr(prime_LoadFile(vertex_shader));
		handle->vertex_shader = createShader(GL_VERTEX_SHADER, vertex_src);
		const char* fragment_src = prime_StringGetCstr(prime_LoadFile(pixel_shader));
		handle->fragment_shader = createShader(GL_FRAGMENT_SHADER, fragment_src);
	}
	else {
		handle->vertex_shader = createShader(GL_VERTEX_SHADER, vertex_shader);
		handle->fragment_shader = createShader(GL_FRAGMENT_SHADER, pixel_shader);
	}

	int status = GL_FALSE;
	int max_length = 0;

	handle->id = glCreateProgram();
	glAttachShader(handle->id, handle->vertex_shader);
	glAttachShader(handle->id, handle->fragment_shader);
	glLinkProgram(handle->id);

	glValidateProgram(handle->id);
	glGetProgramiv(handle->id, GL_LINK_STATUS, &status);
	glGetProgramiv(handle->id, GL_INFO_LOG_LENGTH, &max_length);
	if (status != GL_TRUE)
	{
		std::vector<GLchar> info_log(max_length);
		glGetProgramInfoLog(handle->id, max_length, &max_length, info_log.data());

		prime_String* msg = prime_StringFormat("shader link error : %s", info_log.data());
		PRIME_LOG_STRING(msg);

		glDeleteProgram(handle->id);
		handle->id = 0;
		PRIME_ASSERT(false);
	}
	glDeleteShader(handle->vertex_shader);
	glDeleteShader(handle->fragment_shader);

	return handle;
}

void
gl_ShaderDestroy(void* shader)
{
	gl_Shader* handle = (gl_Shader*)shader;
	glDeleteProgram(handle->id);
	handle->id = 0;
	prime_MemFree(shader, sizeof(gl_Shader));
}

void
gl_ShaderBind(void* shader)
{
	gl_Shader* handle = (gl_Shader*)shader;
	glUseProgram(handle->id);
}

void
gl_ShaderUnbind(void* shader)
{
	glUseProgram(0);
}

void
gl_ShaderSetInt(void* shader, const char* name, i32 data)
{
	gl_Shader* handle = (gl_Shader*)shader;
	GLint location = glGetUniformLocation(handle->id, name);
	glUniform1i(location, data);
}

void
gl_ShaderSetIntArray(void* shader, const char* name, i32* data, u32 count)
{
	gl_Shader* handle = (gl_Shader*)shader;
	GLint location = glGetUniformLocation(handle->id, name);
	glUniform1iv(location, count, data);
}

void
gl_ShaderSetFloat(void* shader, const char* name, f32 data)
{
	gl_Shader* handle = (gl_Shader*)shader;
	GLint location = glGetUniformLocation(handle->id, name);
	glUniform1f(location, data);
}

void
gl_ShaderSetFloat2(void* shader, const char* name, prime_Vec2 data)
{
	gl_Shader* handle = (gl_Shader*)shader;
	GLint location = glGetUniformLocation(handle->id, name);
	glUniform2f(location, data.x, data.y);
}

void
gl_ShaderSetFloat3(void* shader, const char* name, prime_Vec3 data)
{
	gl_Shader* handle = (gl_Shader*)shader;
	GLint location = glGetUniformLocation(handle->id, name);
	glUniform3f(location, data.x, data.y, data.z);
}

void
gl_ShaderSetFloat4(void* shader, const char* name, prime_Vec4 data)
{
	gl_Shader* handle = (gl_Shader*)shader;
	GLint location = glGetUniformLocation(handle->id, name);
	glUniform4f(location, data.x, data.y, data.z, data.w);
}

void
gl_ShaderSetMat4(void* shader, const char* name, prime_Mat4 data)
{
	gl_Shader* handle = (gl_Shader*)shader;
	GLint location = glGetUniformLocation(handle->id, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, data.data);
}
