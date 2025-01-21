
#include "prime/prime_shader.h"
#include "prime/prime_math.h"
#include "prime/prime_log.h"
#include "prime_utils.h"
#include "prime/prime_device.h"

#include "opengl/prime_opengl_shader.h"

struct prime_Shader
{
	prime_Device* device = nullptr;
	void* handle = nullptr;

	void(*destroyFunc)(void* handle);
	void(*bindFunc)(void* handle);
	void(*unbindFunc)(void* handle);
	void(*setIntFunc)(void* handle, const char* name, i32 data);
	void(*setIntArrayFunc)(void* handle, const char* name, i32* data, u32 count);
	void(*setFloatFunc)(void* handle, const char* name, f32 data);
	void(*setFloat2Func)(void* handle, const char* name, prime_Vec2 data);
	void(*setFloat3Func)(void* handle, const char* name, prime_Vec3 data);
	void(*setFloat4Func)(void* handle, const char* name, prime_Vec4 data);
	void(*setMat4Func)(void* handle, const char* name, prime_Mat4 data);
};

prime_Shader*
prime_ShaderCreate(prime_Device* device, const char* vertex_shader, const char* pixel_shader, b8 load)
{
	prime_Shader* shader = nullptr;
	shader = (prime_Shader*)prime_MemAlloc(sizeof(prime_Shader));
	shader->device = device;

	switch (prime_DeviceGetType(device))
	{
	case prime_DeviceTypeDx11:{
			PRIME_ASSERT_MSG(false, "Dx11 Shader not implemented yet");
			break;
		}
	case prime_DeviceTypeGL: {
		shader->handle = gl_ShaderCreate(vertex_shader, pixel_shader, load);

		shader->bindFunc = gl_ShaderBind;
		shader->unbindFunc = gl_ShaderUnbind;
		shader->destroyFunc = gl_ShaderDestroy;
		shader->setFloatFunc = gl_ShaderSetFloat;
		shader->setFloat2Func = gl_ShaderSetFloat2;
		shader->setFloat3Func = gl_ShaderSetFloat3;
		shader->setFloat4Func = gl_ShaderSetFloat4;
		shader->setMat4Func = gl_ShaderSetMat4;
		shader->setIntFunc = gl_ShaderSetInt;
		shader->setIntArrayFunc = gl_ShaderSetIntArray;
		break;
	}
	}
	shader->device = device;
	prime_AppendShader(device, shader);
	return shader;
}

void
prime_ShaderDestroy(prime_Shader* shader)
{
	PRIME_ASSERT_MSG(shader, "Shader is null");
	shader->destroyFunc(shader->handle);

	shader->destroyFunc = nullptr;
	shader->bindFunc = nullptr;
	shader->unbindFunc = nullptr;
	shader->setFloatFunc = nullptr;
	shader->setFloat2Func = nullptr;
	shader->setFloat3Func = nullptr;
	shader->setFloat4Func = nullptr;
	shader->setMat4Func = nullptr;

	prime_PopShader(shader->device, shader);
	prime_MemFree(shader, sizeof(prime_Shader));
}

void
prime_ShaderBind(prime_Shader* shader)
{
	PRIME_ASSERT_MSG(shader, "Shader is null");
	shader->bindFunc(shader->handle);
}

void
prime_ShaderUnbind(prime_Shader* shader)
{
	PRIME_ASSERT_MSG(shader, "Shader is null");
	shader->unbindFunc(shader->handle);
}

void
prime_ShaderSetInt(prime_Shader* shader, const char* name, i32 data)
{
	PRIME_ASSERT_MSG(shader, "Shader is null");
	shader->setIntFunc(shader->handle, name, data);
}

void
prime_ShaderSetIntArray(prime_Shader* shader, const char* name, i32* data, u32 count)
{
	PRIME_ASSERT_MSG(shader, "Shader is null");
	shader->setIntArrayFunc(shader->handle, name, data, count);
}

void
prime_ShaderSetFloat(prime_Shader* shader, const char* name, f32 data)
{
	PRIME_ASSERT_MSG(shader, "Shader is null");
	shader->setFloatFunc(shader->handle, name, data);
}

void
prime_ShaderSetFloat2(prime_Shader* shader, const char* name, prime_Vec2 data)
{
	PRIME_ASSERT_MSG(shader, "Shader is null");
	shader->setFloat2Func(shader->handle, name, data);
}

void
prime_ShaderSetFloat3(prime_Shader* shader, const char* name, prime_Vec3 data)
{
	PRIME_ASSERT_MSG(shader, "Shader is null");
	shader->setFloat3Func(shader->handle, name, data);
}

void
prime_ShaderSetFloat4(prime_Shader* shader, const char* name, prime_Vec4 data)
{
	PRIME_ASSERT_MSG(shader, "Shader is null");
	shader->setFloat4Func(shader->handle, name, data);
}

void
prime_ShaderSetMat4(prime_Shader* shader, const char* name, prime_Mat4 data)
{
	PRIME_ASSERT_MSG(shader, "Shader is null");
	shader->setMat4Func(shader->handle, name, data);
}