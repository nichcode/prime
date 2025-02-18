
#include "prime/prime_layout.h"
#include "prime/prime_memory.h"
#include "prime/prime_device.h"
#include "prime_utils.h"

#include "prime_gllayout.h"

#include "map"
#include <vector>

struct Element
{
    primeType type = primeTypeFloat3;
	u32 size = 0;
	u64 offset = 0;
};

struct primeLayout
{
	primeDevice* device = nullptr;
    u32 id = 0;
    void* handle = nullptr;
	u32 stride = 0, count = 0;
	primeBufferType vboType = primeBufferTypeDynamic;

    void(*destroyFunc)(void* handle) = nullptr;
	void(*bindFunc)(void* handle) = nullptr;
	void(*unbindFunc)(void* handle) = nullptr;
	void(*setFunc)(void* handle, const void* data, u32 size) = nullptr;
	void(*pushFunc)(void* handle, u32 index, u32 count, primeType type, u64 offset, u32 stride) = nullptr;
	void(*setIntFunc)(void* handle, const char* name, i32 data);
	void(*setIntArrayFunc)(void* handle, const char* name, i32* data, u32 count);
	void(*setFloatFunc)(void* handle, const char* name, f32 data);
	void(*setFloat2Func)(void* handle, const char* name, primeVec2 data);
	void(*setFloat3Func)(void* handle, const char* name, primeVec3 data);
	void(*setFloat4Func)(void* handle, const char* name, primeVec4 data);
	void(*setMat4Func)(void* handle, const char* name, primeMat4 data);
};

struct LayoutData
{
    u32 index = 1;
    std::map<u32, std::vector<Element>> elements;
};

static LayoutData s_LayoutData;

inline u32
primeTypeGetSize(primeType type)
{
	switch (type)
	{
	case primeTypeInt:
	case primeTypeFloat: {
		return 4;
        break;
	}

	case primeTypeInt2:
	case primeTypeFloat2: {
		return 8;
        break;
	}

	case primeTypeInt3:
	case primeTypeFloat3: {
		return 12;
        break;
	}

	case primeTypeInt4:
	case primeTypeFloat4: {
		return 16;
        break;
	}

	case primeTypeMat3: {
        return 4 * 3 * 3;
        break;
    }    

	case primeTypeMat4:     {
        return 4 * 4 * 4; 
        break;
    }

	case primeTypeBool: {
            return 1;
            break;
	}

    }
	return 0;
}

inline u32
primeTypeGetCount(primeType type)
{
	switch (type)
	{
	case primeTypeFloat:
	case primeTypeInt:
	case primeTypeBool: {
		return 1;
	}

	case primeTypeFloat2:
	case primeTypeInt2: {
		return 2;
	}

	case primeTypeFloat3:
	case primeTypeInt3: {
		return 3;
	}

	case primeTypeFloat4:
	case primeTypeInt4: {
		return 4;
	}


	case primeTypeMat3: {
            return 9;
            break;
    }

	case primeTypeMat4:   {
        return 16;
        break;
    }  

	}
	return 0;
}

primeLayout*
primeLayoutCreate(primeDevice* device, const primeLayoutDesc* desc)
{
    primeLayout* layout = nullptr;
	layout = (primeLayout*)primeMemoryAlloc(sizeof(primeLayout));
	PASSERT_MSG(layout, "primeLayout creation failed");
	layout->device = device;
	layout->id = s_LayoutData.index;   
	s_LayoutData.index++;
	layout->vboType = desc->vbo.type;
	layout->count = desc->ibo.count;

    b8 shader_empty = true;
	if (desc->shader.vertex && desc->shader.pixel) {
		shader_empty = false;
	}

    switch (primeDeviceGetType(device)) 
    {
#ifdef PPLATFORM_WINDOWS
	case primeDeviceTypeDx11: {
        PASSERT_MSG(false, "Prime currently does not support Dx11");
		break;
	}
#endif // PPLATFORM_WINDOWS

	case primeDeviceTypeGL: {
        layout->handle = primeGLLayoutCreate(desc, shader_empty);

        layout->destroyFunc = primeGLLayoutDestroy;
        layout->bindFunc = primeGLLayoutBind;
        layout->unbindFunc = primeGLLayoutUnbind;
        layout->pushFunc = primeGLLayoutPush; 
		layout->setFunc = primeGLLayoutSetData;
		layout->setIntFunc = primeGLLayoutSetInt;
		layout->setIntArrayFunc = primeGLLayoutSetIntArray;
		layout->setFloatFunc = primeGLLayoutSetFloat;
		layout->setFloat2Func = primeGLLayoutSetFloat2;
		layout->setFloat3Func = primeGLLayoutSetFloat3;
		layout->setFloat4Func = primeGLLayoutSetFloat4;
		layout->setMat4Func = primeGLLayoutSetMat4;
    }

    }

	primeDeviceAppendLayout(device, layout);
	return layout;
}

void
primeLayoutDestroy(primeLayout* layout)
{
    PASSERT_MSG(layout, "layout is null");
    s_LayoutData.elements[layout->id].clear();
    layout->destroyFunc(layout->handle);
    layout->handle = nullptr;
	primeDevicePopLayout(layout->device, layout);
	layout->id = 0;
	layout->destroyFunc = nullptr;
    layout->bindFunc = nullptr;
    layout->unbindFunc = nullptr;
    layout->pushFunc = nullptr;
	layout->setFunc = nullptr;

	primeMemoryFree(layout, sizeof(primeLayout));
	s_LayoutData.index--;
}

void
primeLayoutAdd(primeLayout* layout, primeType type)
{
    PASSERT_MSG(layout, "layout is null");
    Element element;
	element.type = type;
	element.size = primeTypeGetSize(type);
	s_LayoutData.elements[layout->id].push_back(element);
}

void
primeLayoutBind(primeLayout* layout)
{
    PASSERT_MSG(layout, "layout is null");
    layout->bindFunc(layout->handle);
}

void
primeLayoutUnbind(primeLayout* layout)
{
    PASSERT_MSG(layout, "layout is null");
    layout->unbindFunc(layout->handle);
}

void
primeLayoutSetData(primeLayout* layout, const void* data, u32 size)
{
	PASSERT_MSG(layout, "layout is null");
	PASSERT_MSG(layout->vboType == primeBufferTypeDynamic, "Cannot set data to a static vbo");
    layout->setFunc(layout->handle, data, size);
}

u32
primeLayoutGetCount(primeLayout* layout)
{
	PASSERT_MSG(layout, "layout is null");
	return layout->count;
}

void
primeLayoutSubmit(primeLayout* layout)
{
    PASSERT_MSG(layout, "layout is null");

	layout->stride = 0;
	for (auto& element : s_LayoutData.elements[layout->id])
	{
		element.offset = layout->stride;
		layout->stride += element.size;
	}

	u32 index = 0;
	for (const auto& element : s_LayoutData.elements[layout->id]) {
        layout->pushFunc(layout->handle,
         index, 
         primeTypeGetCount(element.type),
         element.type,
         element.offset,
         layout->stride);

		index++;
	}

}

void
primeLayoutSetInt(primeLayout* layout, const char* name, i32 data)
{
	PASSERT_MSG(layout, "layout is null");
	layout->setIntFunc(layout->handle, name, data);
}

void
primeLayoutSetIntArray(primeLayout* layout, const char* name, i32* data, u32 count)
{
	PASSERT_MSG(layout, "layout is null");
	layout->setIntArrayFunc(layout->handle, name, data, count);
}

void
primeLayoutSetFloat(primeLayout* layout, const char* name, f32 data)
{
	PASSERT_MSG(layout, "layout is null");
	layout->setFloatFunc(layout->handle, name, data);
}

void
primeLayoutSetFloat2(primeLayout* layout, const char* name, primeVec2 data)
{
	PASSERT_MSG(layout, "layout is null");
	layout->setFloat2Func(layout->handle, name, data);
}

void
primeLayoutSetFloat3(primeLayout* layout, const char* name, primeVec3 data)
{
	PASSERT_MSG(layout, "layout is null");
	layout->setFloat3Func(layout->handle, name, data);
}

void
primeLayoutSetFloat4(primeLayout* layout, const char* name, primeVec4 data)
{
	PASSERT_MSG(layout, "layout is null");
	layout->setFloat4Func(layout->handle, name, data);
}

void
primeLayoutSetMat4(primeLayout* layout, const char* name, primeMat4 data)
{
	PASSERT_MSG(layout, "layout is null");
	layout->setMat4Func(layout->handle, name, data);
}