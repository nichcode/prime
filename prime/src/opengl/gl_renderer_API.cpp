
#include "gl_renderer_API.h"
#include "prime/internal.h"
#include "prime/core/logger.h"
#include "opengl_API.h"
#include <algorithm>

#include "windows/windows_gl_context.h"

namespace prime::renderer {

    struct VertexArray
    {
        u32 id = 0;
    };

    struct VertexBuffer
    {
        u32 id = 0;
        b8 dynamic = false;
    };

    struct IndexBuffer
    {
        u32 id = 0;
        u32 count = 0;
    };

    struct Element
    {
        DataType type = DataTypeFloat3;
        b8 normalize = false;
        u64 offset = 0;
        u32 size = 0;
        u32 divisor = 0;
    };

    struct Layout
    {
        std::vector<Element> elements;
        u32 stride = 0;
    };

    GLRendererAPI::GLRendererAPI(const core::Scope<core::Window>& window)
    {
#ifdef PRIME_PLATFORM_WINDOWS
        HWND handle = internal::getWin32WindowHandle(window);
        m_Context = core::createScope<WindowsGLContext>(handle);
#endif // PRIME_PLATFORM_WINDOWS
        
        m_Index = 0;
        m_Viewport.width = window->getWidth();
        m_Viewport.height = window->getHeight();
    }
    
    GLRendererAPI::~GLRendererAPI()
    {
        // vertex arrays
        for (VertexArray* vertex_array : m_VertexArrays) {
            glDeleteBuffers(1, &vertex_array->id);
            vertex_array->id = 0;
            delete vertex_array;
            vertex_array = nullptr;
        }

        // vertex buffers
        for (VertexBuffer* vertex_buffer : m_VertexBuffers) {
            glDeleteBuffers(1, &vertex_buffer->id);
            vertex_buffer->id = 0;
            delete vertex_buffer;
            vertex_buffer = nullptr;
        }

        // index buffers
        for (IndexBuffer* index_buffer : m_IndexBuffers) {
            glDeleteBuffers(1, &index_buffer->id);
            index_buffer->id = 0;
            index_buffer->count = 0;
            delete index_buffer;
            index_buffer = nullptr;
        }

        // layout
        for (Layout* layout : m_Layouts) {
            layout->elements.clear();
            layout->stride = 0;
            delete layout;
            layout = nullptr;
        }

        m_VertexArrays.clear();
        m_VertexBuffers.clear();
        m_IndexBuffers.clear();
        m_Layouts.clear();
    }
    
    VertexArray* GLRendererAPI::createVertexArray()
    {
        VertexArray* vertex_array = new VertexArray();
        glGenVertexArrays(1, &vertex_array->id);
        glBindVertexArray(vertex_array->id);

        m_VertexArrays.push_back(vertex_array);
        return vertex_array;
    }
    
    void GLRendererAPI::deleteVertexArray(VertexArray* vertex_array)
    {
        PRIME_ASSERT_MSG(vertex_array, "vertex_array is null");

        auto it = std::find(m_VertexArrays.begin(), m_VertexArrays.end(), vertex_array);
        if (it != m_VertexArrays.end())
        {
            m_VertexArrays.erase(it);
        }

        glDeleteVertexArrays(1, &vertex_array->id);
        vertex_array->id = 0;
        delete vertex_array;
        vertex_array = nullptr;
    }
    
    VertexBuffer* GLRendererAPI::createStaticVertexBuffer(f32* vertices, u32 size)
    {
        VertexBuffer* vertex_buffer = new VertexBuffer();
        glGenBuffers(1, &vertex_buffer->id);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

        vertex_buffer->dynamic = false;
        m_VertexBuffers.push_back(vertex_buffer);
        return vertex_buffer;
    }
    
    VertexBuffer* GLRendererAPI::createDynamicVertexBuffer(u32 size)
    {
        VertexBuffer* vertex_buffer = new VertexBuffer();
        glGenBuffers(1, &vertex_buffer->id);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

        vertex_buffer->dynamic = true;
        m_VertexBuffers.push_back(vertex_buffer);
        return vertex_buffer;
    }
    
    void GLRendererAPI::deleteVertexBuffer(VertexBuffer* vertex_buffer)
    {
        PRIME_ASSERT_MSG(vertex_buffer, "vertex_buffer is null");

        auto it = std::find(m_VertexBuffers.begin(), m_VertexBuffers.end(), vertex_buffer);
        if (it != m_VertexBuffers.end())
        {
            m_VertexBuffers.erase(it);
        }

        glDeleteBuffers(1, &vertex_buffer->id);
        vertex_buffer->id = 0;
        delete vertex_buffer;
        vertex_buffer = nullptr;
    }
    
    IndexBuffer* GLRendererAPI::createIndexBuffer(u32* indices, u32 count)
    {
        IndexBuffer* index_buffer = new IndexBuffer();
        index_buffer->count = count;

        glGenBuffers(1, &index_buffer->id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);

        m_IndexBuffers.push_back(index_buffer);
        return index_buffer;
    }
    
    void GLRendererAPI::deleteIndexBuffer(IndexBuffer* index_buffer)
    {
        PRIME_ASSERT_MSG(index_buffer, "index_buffer is null");

        auto it = std::find(m_IndexBuffers.begin(), m_IndexBuffers.end(), index_buffer);
        if (it != m_IndexBuffers.end())
        {
            m_IndexBuffers.erase(it);
        }

        glDeleteBuffers(1, &index_buffer->id);
        index_buffer->id = 0;
        index_buffer->count = 0;
        delete index_buffer;
        index_buffer = nullptr;
    }
    
    Layout* GLRendererAPI::createLayout()
    {
        Layout* layout = new Layout();
        layout->elements.clear();
        m_Layouts.push_back(layout);
        return layout;
    }
    
    void GLRendererAPI::deleteLayout(Layout* layout)
    {
        PRIME_ASSERT_MSG(layout, "layout is null");

        auto it = std::find(m_Layouts.begin(), m_Layouts.end(), layout);
        if (it != m_Layouts.end())
        {
            m_Layouts.erase(it);
        }

        layout->elements.clear();
        layout->stride = 0;
        delete layout;
        layout = nullptr;
    }
    
    void GLRendererAPI::AddElement(Layout* layout, DataType type, u32 divisor, b8 normalize)
    {
        PRIME_ASSERT_MSG(layout, "layout is null");

        Element element;
        element.divisor = divisor;
        element.normalize = normalize;
        element.type = type;
        element.size = getDataTypeSize(type);
        layout->elements.push_back(element);
    }
    
    void GLRendererAPI::makeActive()
    {
        m_Context->makeActive();
    }
    
    void GLRendererAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void GLRendererAPI::present()
    {
        m_Context->present();
    }
    
    void GLRendererAPI::submit(DrawType type, DrawMode mode, u32 count)
    {
        GLenum gl_type = drawModeToGL(mode);
        if (type == DrawTypeArrays) {
            glDrawArrays(gl_type, 0, count);
        }
        else if (type == DrawTypeElements) {
            glDrawElements(gl_type, count, GL_UNSIGNED_INT, nullptr);
        }      
    }
    
    void GLRendererAPI::setClearColor(const Color& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    
    void GLRendererAPI::setVertexBufferData(const VertexBuffer* vertex_buffer, const void* data, u32 size)
    {
        PRIME_ASSERT_MSG(vertex_buffer, "vertex_buffer is null");

        if (vertex_buffer->dynamic) {
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        }
        else {
            PRIME_WARN("vertex_buffer is static");
        }
    }
    
    void GLRendererAPI::setVsync(b8 vsync)
    {
        m_Context->setVsync(vsync);
    }
    
    void GLRendererAPI::setViewport(const Viewport& viewport)
    {
        m_Viewport = viewport;
        glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
    }
    
    void GLRendererAPI::setVertexArray(const VertexArray* vertex_array)
    {
        PRIME_ASSERT_MSG(vertex_array, "vertex_array is null");
        glBindVertexArray(vertex_array->id);
    }
    
    void GLRendererAPI::setVertexBuffer(const VertexBuffer* vertex_buffer)
    {
        PRIME_ASSERT_MSG(vertex_buffer, "vertex_buffer is null");
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
    }
    
    void GLRendererAPI::setIndexBuffer(const IndexBuffer* index_buffer)
    {
        PRIME_ASSERT_MSG(index_buffer, "index_buffer is null");
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->id);
    }
    
    void GLRendererAPI::setLayout(Layout* layout)
    {
        PRIME_ASSERT_MSG(layout, "layout is null");

        layout->stride = 0;
        for (Element& element : layout->elements) {
            element.offset = layout->stride;
            layout->stride += element.size;
        }

        for (const Element& element : layout->elements) {
            u32 count = getDataTypeCount(element.type);
            u32 type = typeToGLType(element.type);
            u32 stride = layout->stride;

            switch (element.type) {
                case DataTypeFloat:
                case DataTypeFloat2:
                case DataTypeFloat3:
                case DataTypeFloat4: {
                    glVertexAttribPointer(
                        m_Index,
                        count,
                        type,
                        element.normalize,
                        stride,
                        (const void*)element.offset);

                    glEnableVertexAttribArray(m_Index);
                    glVertexAttribDivisor(m_Index, element.divisor);
                    break;
                }

                case DataTypeInt:
                case DataTypeInt2:
                case DataTypeInt3:
                case DataTypeInt4:
                case DataTypeBool: {
                    glVertexAttribIPointer(
                        m_Index,
                        count,
                        type,
                        stride,
                        (const void*)element.offset);

                    glEnableVertexAttribArray(m_Index);
                    glVertexAttribDivisor(m_Index, element.divisor);
                    break;
                }

            } // switch

            m_Index++;
        }
    }
    
    u32 GLRendererAPI::getIndexBufferCount(const IndexBuffer* index_buffer) const 
    {
        PRIME_ASSERT_MSG(index_buffer, "index_buffer is null");
        return index_buffer->count;
    }
    
} // namespace prime::renderer
