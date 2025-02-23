
#include "opengl_context.h"
#include "prime/native.h"
#include "prime/logger.h"
#include "glad/glad.h"

#include <algorithm>

#ifdef PPLATFORM_WINDOWS
#include "windows/wgl_context.h"
#endif // PPLATFORM_WINDOWS

namespace prime {

    static i32 
    getBufferType(BufferType type)
    {
        switch (type)
        {
            case BufferType::Vertex: {
                return GL_ARRAY_BUFFER;
            }
            break;

            case BufferType::Index: {
                return GL_ELEMENT_ARRAY_BUFFER;
            }
            break;
        }
        return 0;
    }

    static i32 
    getBufferUsage(BufferUsage usage)
    {
        switch (usage)
        {
            case BufferUsage::DynamicDraw: {
                return GL_DYNAMIC_DRAW;
            }
            break;

            case BufferUsage::StaticDraw: {
                return GL_STATIC_DRAW;
            }
            break;
        }
        return 0;
    }

    static inline GLenum
    typeToGLType(Type type)
    {
        switch (type)
        {
        case Type::Int:
        case Type::Int2:
        case Type::Int3:
        case Type::Int4:
            return GL_INT;

        case Type::Float:
        case Type::Float2:
        case Type::Float3:
        case Type::Float4:
        case Type::Mat3:
        case Type::Mat4:
            return GL_FLOAT;

        case Type::Bool:
            return GL_BOOL;
        }
        return 0;
    }

    inline static 
    GLenum drawModeToOpenGL(DrawMode mode)
    {
        switch (mode)
        {
        case DrawMode::Triangles:
            return GL_TRIANGLES;
            break;

        case DrawMode::Lines:
            return GL_LINES;
            break;
        }
        return 0;
    }

    GLBuffer::GLBuffer(const BufferDesc& desc)
    {
        i32 type = getBufferType(desc.type);
        i32 usage = getBufferUsage(desc.usage);
        m_Usage = desc.usage;
        m_Type = desc.type;
        glGenBuffers(1, &m_ID);
        glBindBuffer(type, m_ID);

        glBufferData(type, desc.size, desc.data, usage);
        glBindBuffer(type, 0);
    }

    GLBuffer::~GLBuffer()
    {
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
    }

    void
    GLBuffer::setData(const void* data, u32 size)
    {
        i32 type = getBufferType(m_Type);
        glBufferSubData(type, 0, size, data);
    }

    
    GLLayout::GLLayout()
    {
        glGenVertexArrays(1, &m_ID);
    }

    GLLayout::~GLLayout()
    {
        glDeleteVertexArrays(1, &m_ID);
        m_Elements.clear();
    }

    void 
    GLLayout::add(Type type, u32 divisor)
    {
        Element element;
        element.type = type;
        element.divisor = divisor;
        element.size = typeGetSize(type);
        m_Elements.push_back(element);
    }


    GLContext::GLContext(const Window& window)
    {
#ifdef PPLATFORM_WINDOWS
        m_Window = getWin32WindowHandle(window);
        m_Context = wglContextCreate(m_Window);
        m_Hdc = GetDC(m_Window);
#endif // PPLATFORM_WINDOWS
        m_Buffers.clear();
    }

    GLContext::~GLContext()
    {
#ifdef PPLATFORM_WINDOWS
        wglContextDestroy(m_Context);
#endif // PPLATFORM_WINDOWS
    }

    void 
    GLContext::swapbuffers()
    {
#ifdef PPLATFORM_WINDOWS
        SwapBuffers(m_Hdc);
#endif // PPLATFORM_WINDOWS
    }

    void 
    GLContext::makeActive()
    {
#ifdef PPLATFORM_WINDOWS
        wglContextMakeCurrent(m_Window, m_Context);
#endif // PPLATFORM_WINDOWS
    }

    void 
    GLContext::setClearColor(const Color& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void 
    GLContext::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Buffer*
    GLContext::createBuffer(const BufferDesc& desc)
    {
        Buffer* buffer = new GLBuffer(desc);
        m_Buffers.push_back(buffer);
        return buffer;
    }

    void
    GLContext::destroyBuffer(Buffer* buffer)
    {
        PASSERT_MSG(buffer, "buffer is null");
        auto it = std::find(m_Buffers.begin(), m_Buffers.end(), buffer);
        if (it != m_Buffers.end())
        {
            m_Buffers.erase(it);
        }

        delete buffer;
    }

    Layout*
    GLContext::createLayout()
    {
        Layout* layout = new GLLayout();
        m_Layouts.push_back(layout);
        return layout;
    }

    void
    GLContext::destroyLayout(Layout* layout)
    {
        PASSERT_MSG(layout, "layout is null");
        auto it = std::find(m_Layouts.begin(), m_Layouts.end(), layout);
        if (it != m_Layouts.end())
        {
            m_Layouts.erase(it);
        }

        delete layout;
    }

    void
    GLContext::setLayout(Layout* layout, b8 submit)
    {
        glBindVertexArray(layout->getID());

        u32 stride = 0;
        for (auto& element : layout->get())
        {
            element.offset = stride;
            stride += element.size;
        }
        layout->setStride(stride);

        if (submit) {
                u32 index = 0;
                for (const auto& element : layout->get()) {
                    switch (element.type) {
                        case Type::Float:
                        case Type::Float2:
                        case Type::Float3:
                        case Type::Float4: {
                            glEnableVertexAttribArray(index);
                            glVertexAttribPointer(index,
                                typeGetCount(element.type),
                                typeToGLType(element.type),
                                GL_FALSE,
                                layout->getStride(),
                                (const void*)element.offset);
                            
                            glVertexAttribDivisor(index, element.divisor);
                            break;
                        }
                        
                        case Type::Int:
                        case Type::Int2:
                        case Type::Int3:
                        case Type::Int4:
                        case Type::Bool: {
                            glEnableVertexAttribArray(index);
                            glVertexAttribIPointer(index,
                                typeGetCount(element.type),
                                typeToGLType(element.type),
                                layout->getStride(),
                                (const void*)element.offset);
                            
                            glVertexAttribDivisor(index, element.divisor);
                            break;
                        }
                        
                        case Type::Mat3:
                        case Type::Mat4: {
                            u8 count = count;
                            for (u8 i = 0; i < count; i++)
                            {
                                glEnableVertexAttribArray(index);
                                glVertexAttribPointer(index,
                                    count,
                                    typeToGLType(element.type),
                                    GL_FALSE,
                                    layout->getStride(),
                                    (const void*)(element.offset + sizeof(f32) * count * i));
                                glVertexAttribDivisor(index, element.divisor);
                            }
                            break;
                        }
                    
                    }
                    index++;
            }
        }

    }

    void
    GLContext::setBuffer(Buffer* buffer)
    {
        i32 type = getBufferType(buffer->getType());
        glBindBuffer(type, buffer->getID());
    }

    void
    GLContext::drawElements(DrawMode mode, u32 count)
    {
        GLenum type = drawModeToOpenGL(mode);
        glDrawElements(type, count, GL_UNSIGNED_INT, nullptr);
    }
    
} // namespace prime
