
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
	u32 stride = 0;

    void(*destroyFunc)(void* handle) = nullptr;
	void(*bindFunc)(void* handle) = nullptr;
	void(*unbindFunc)(void* handle) = nullptr;
	void(*pushFunc)(void* handle, u32 index, u32 count, primeType type, u64 offset, u32 stride) = nullptr;
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
primeLayoutCreate(primeDevice* device)
{
    primeLayout* layout = nullptr;
	layout = (primeLayout*)primeMemoryAlloc(sizeof(primeLayout));
	PASSERT_MSG(layout, "primeLayout creation failed");
	layout->device = device;
	layout->id = s_LayoutData.index;   
	s_LayoutData.index++;

    switch (primeDeviceGetType(device)) 
    {
#ifdef PPLATFORM_WINDOWS
	case primeDeviceTypeDx11: {
        PASSERT_MSG(false, "Prime currently does not support Dx11");
		break;
	}
#endif // PPLATFORM_WINDOWS

	case primeDeviceTypeGL: {
        layout->handle = primeGLLayoutCreate();

        layout->destroyFunc = primeGLLayoutDestroy;
        layout->bindFunc = primeGLLayoutBind;
        layout->unbindFunc = primeGLLayoutUnbind;
        layout->pushFunc = primeGLLayoutPush; 
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
primeLayoutSubmit(primeLayout* layout, primeVertexbuffer* buffer)
{
    PASSERT_MSG(layout, "layout is null");
    PASSERT_MSG(buffer, "vertexbuffer is null");

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