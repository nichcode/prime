
#include "opengl_context.h"
#include "pch.h"
#include "opengl/opengl_funcs.h"
#include "prime/window.h"

#ifdef PRIME_PLATFORM_WINDOWS
#include "win32/wgl_context.h"
#endif // PRIME_PLATFORM_WINDOWS

PRIME_INLINE GLenum typeToGLType(primeDataType type)
{
    switch (type)
    {
        case PRIME_DATA_TYPE_INT:
        case PRIME_DATA_TYPE_INT2:
        case PRIME_DATA_TYPE_INT3:
        case PRIME_DATA_TYPE_INT4:
            return GL_INT;

        case PRIME_DATA_TYPE_FLOAT:
        case PRIME_DATA_TYPE_FLOAT2:
        case PRIME_DATA_TYPE_FLOAT3:
        case PRIME_DATA_TYPE_FLOAT4:
            return GL_FLOAT;

        case PRIME_DATA_TYPE_BOOL:
            return GL_BOOL;
    }
    return 0;
}

PRIME_INLINE GLenum drawModeToGL(primeDrawMode mode)
{
    switch (mode)
    {
        case PRIME_DRAW_MODE_TRIANGLES:
            return GL_TRIANGLES;
            break;

        case PRIME_DRAW_MODE_LINES:
            return GL_LINES;
            break;
    }
    return 0;
}

PRIME_INLINE u32 bufferTypeToGL(primeBufferType type)
{
    switch (type) {
        case PRIME_BUFFER_TYPE_VERTEX: {
            return GL_ARRAY_BUFFER;
            break;
        }
        case PRIME_BUFFER_TYPE_INDEX: {
            return GL_ELEMENT_ARRAY_BUFFER;  
            break;
        }
        case PRIME_BUFFER_TYPE_UNIFORM: {
            return GL_UNIFORM_BUFFER;
            break;
        }
        case PRIME_BUFFER_TYPE_STORAGE: {
            return GL_SHADER_STORAGE_BUFFER;
            break;
        }
    } // switch
    PRIME_ASSERT_MSG(false, "invalid buffer type");
    return 0;
}

PRIME_INLINE u32 bufferUsageToGL(primeBufferUsage usage)
{
    switch (usage) {
        case PRIME_BUFFER_USAGE_STATIC: {
            return GL_STATIC_DRAW;
            break;
        }
        case PRIME_BUFFER_USAGE_DYNAMIC: {
            return GL_DYNAMIC_DRAW;  
            break;
        }
    } // switch
    PRIME_ASSERT_MSG(false, "invalid buffer usage");
    return 0;
}

struct glBuffer
{
    u32 id = 0;
    u32 type;
    u32 usage;
};

struct glShader
{
    u32 id = 0;
};

struct glLayout
{
    u32 stride = 0;
    std::vector<primeElement> elements;
};

struct glContext
{
#ifdef PRIME_PLATFORM_WINDOWS
    HWND windowHandle;
    HGLRC handle;
    HDC deviceContext;
#endif // PRIME_PLATFORM_WINDOWS
    u32 vao = 0;
};

static GLuint generateShader(i32 type, const char* source)
{
    int status = GL_FALSE;
    int max_length = 0;

    GLuint shader = glCreateShader(type);
    const char* gl_source = source;
    glShaderSource(shader, 1, &gl_source, 0);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

    if (status != GL_TRUE) {
        std::vector<GLchar> info_log(max_length);
        glGetShaderInfoLog(shader, max_length, &max_length, info_log.data());
        if (type == GL_VERTEX_SHADER) {
            PRIME_ASSERT_MSG(false, "Vertex shader compilation error : %s", info_log.data());
        }
        else if (type == GL_FRAGMENT_SHADER) {
            PRIME_ASSERT_MSG(false, "Pixel shader compilation error : %s", info_log.data());
        }
    }
    return shader;
}

static GLuint generateProgram(u32 vertexShader, u32 pixelShader)
{
    int status = GL_FALSE;
    int max_length = 0;

    u32 program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, pixelShader);
    glLinkProgram(program);

    glValidateProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
    if (status != GL_TRUE) {
        std::vector<GLchar> info_log(max_length);
        glGetProgramInfoLog(program, max_length, &max_length, info_log.data());

        glDeleteProgram(program);
        program = 0;
        PRIME_ASSERT_MSG(false, "shader link error : %s", info_log.data());
    }
    return program;
}

std::string readfile(const char* filepath)
{
    std::string result;
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    if (file) {
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        if (size != -1) {
            result.resize(size);
            file.seekg(0, std::ios::beg);
            file.read(&result[0], size);
        }
        else {
            PRIME_ASSERT_MSG(false, "Could not read from file '%s'", filepath);
            return nullptr;
        }
    }
    else {
        PRIME_ASSERT_MSG(false, "Could not read from file '%s'", filepath);
        return nullptr;
    }
    return result;
}

void* glCreateContext(primeWindow* window)
{
    glContext* context = new glContext();

#ifdef PRIME_PLATFORM_WINDOWS
    context->windowHandle = (HWND)primeGetWindowHandle(window);
    context->handle = createWGLContext(context->windowHandle);
    context->deviceContext = GetDC(context->windowHandle);
#endif // PRIME_PLATFORM_WINDOWS
    
    glGenVertexArrays(1, &context->vao);
    glBindVertexArray(context->vao);
    return context;
}

void glDestroyContext(void* context)
{
    glContext* gl_context = (glContext*)context;

#ifdef PRIME_PLATFORM_WINDOWS
    destroyWGLContext(gl_context->handle);
    ReleaseDC(gl_context->windowHandle, gl_context->deviceContext);
#endif // PRIME_PLATFORM_WINDOWS
   
    glDeleteVertexArrays(1, &gl_context->vao);
    gl_context->windowHandle = 0;
    gl_context->handle = 0;
    gl_context->deviceContext = 0;
    
    delete gl_context;
    context = nullptr;
    gl_context = nullptr;
}

void glPresent(void* context)
{
    glContext* gl_context = (glContext*)context;
#ifdef PRIME_PLATFORM_WINDOWS
    SwapBuffers(gl_context->deviceContext);
#endif // PRIME_PLATFORM_WINDOWS
}

void glMakeActive(void* context)
{
    glContext* gl_context = (glContext*)context;
#ifdef PRIME_PLATFORM_WINDOWS
    makeWGLContextCurrent(gl_context->windowHandle, gl_context->handle);
#endif // PRIME_PLATFORM_WINDOWS
}

void glSetVsync(void* context, b8 vsync)
{
#ifdef PRIME_PLATFORM_WINDOWS
    setWGLContextVsync(vsync);
#endif // PRIME_PLATFORM_WINDOWS
}

void glSubmit(void* context, primeDrawType type, primeDrawMode mode, u32 count)
{
    GLenum gl_type = drawModeToGL(mode);
    if (type == PRIME_DRAW_TYPE_ARRAYS) {
        glDrawArrays(gl_type, 0, count);
    }
    else if (type == PRIME_DRAW_TYPE_ELEMENTS) {
        glDrawElements(gl_type, 6, GL_UNSIGNED_INT, nullptr);
    }
}

void glSubmitInstanced(void* context, primeDrawType type, primeDrawMode mode, u32 count, u32 ins_count)
{
    GLenum gl_type = drawModeToGL(mode);
    if (type == PRIME_DRAW_TYPE_ARRAYS) {
        glDrawArraysInstanced(gl_type, 0, count, ins_count);
    }
    else if (type == PRIME_DRAW_TYPE_ELEMENTS) {
        glDrawElementsInstanced(gl_type, 6, GL_UNSIGNED_INT, nullptr, ins_count);
    }
}

void _glClear(void* context)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void glSetClearColor(void* context, f32 r, f32 g, f32 b, f32 a)
{
    glClearColor(r, g, b, a);
}

void glSetView(void* context, const primeView* view)
{
    glViewport(view->pos.x, view->pos.y, view->size.x, view->size.y);
}

void* glCreateBuffer(primeBufferDesc desc)
{
    glBuffer* buffer = new glBuffer();
    buffer->type = bufferTypeToGL(desc.type);
    buffer->usage = bufferUsageToGL(desc.usage);
    glGenBuffers(1, &buffer->id);
    switch (desc.type) {
        case PRIME_BUFFER_TYPE_VERTEX: {
            glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
            glBufferData(GL_ARRAY_BUFFER, desc.size, desc.data, buffer->usage);
            break;
        }

        case PRIME_BUFFER_TYPE_INDEX: {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, desc.size, desc.data, buffer->usage);
            break;
        }

        case PRIME_BUFFER_TYPE_UNIFORM: {
            glBindBuffer(GL_UNIFORM_BUFFER, buffer->id);
            glBufferData(GL_UNIFORM_BUFFER, desc.size, desc.data, buffer->usage);
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, buffer->id);
            break;
        }

        case PRIME_BUFFER_TYPE_STORAGE: {
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer->id);
            glBufferData(GL_SHADER_STORAGE_BUFFER, desc.size, desc.data, buffer->usage);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffer->id);
            break;
        }     
    } // switch

    return buffer;
}

void glDestroyBuffer(void* buffer)
{
    glBuffer* gl_buffer = (glBuffer*)buffer;
    glDeleteBuffers(1, &gl_buffer->id);
    delete gl_buffer;
    gl_buffer = nullptr;
    buffer = nullptr;
}

void* _glCreateShader(primeShaderDesc desc)
{
    // TODO: transpiler
    std::string vertex_src;
    std::string pixel_src;
    if (desc.load) {
        vertex_src = readfile(desc.vertex_src);
        pixel_src = readfile(desc.pixel_src);
    }
    else {
        vertex_src = desc.vertex_src;
        pixel_src = desc.pixel_src;
    }

    u32 vertex_shader = generateShader(GL_VERTEX_SHADER, vertex_src.c_str());
    u32 pixel_shader = generateShader(GL_FRAGMENT_SHADER, pixel_src.c_str());
    
    glShader* shader = new glShader();
    shader->id = generateProgram(vertex_shader, pixel_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(pixel_shader);
    
    return shader;
}

void glDestroyShader(void* shader)
{
    glShader* gl_shader = (glShader*)shader;
    glDeleteProgram(gl_shader->id);
    delete gl_shader;
    gl_shader = nullptr;
    shader = nullptr;
}

void* glCreateLayout()
{
    glLayout* layout = new glLayout();
    return layout;
}

void glDestroyLayout(void* layout)
{
    glLayout* gl_layout = (glLayout*)layout;
    delete gl_layout;
    layout = nullptr;
    gl_layout = nullptr;
}

void glSetData(void* buffer, const void* data, u32 size)
{
    glBuffer* gl_buffer = (glBuffer*)buffer;
    glBufferSubData(gl_buffer->type, 0, size, data);
}

void glAddAttrib(void* layout, primeDataType type, u32 divisor, b8 normalize)
{
    glLayout* gl_layout = (glLayout*)layout;
    primeElement element;
    element.divisor = divisor;
    element.normalize = normalize;
    element.type = type;
    element.size = getDataTypeSize(type);
    gl_layout->elements.push_back(element);
}

void glSetInt(void* shader, const char* name, i32 data)
{
    glShader* gl_shader = (glShader*)shader;
    GLint location = glGetUniformLocation(gl_shader->id, name);
    glUniform1i(location, data);
}

void glSetIntArray(void* shader, const char* name, i32* data, u32 count)
{
    glShader* gl_shader = (glShader*)shader;
    GLint location = glGetUniformLocation(gl_shader->id, name);
    glUniform1iv(location, count, data);
}

void glSetFloat(void* shader, const char* name, f32 data)
{
    glShader* gl_shader = (glShader*)shader;
    GLint location = glGetUniformLocation(gl_shader->id, name);
    glUniform1f(location, data);
}

void glSetFloat2(void* shader, const char* name, primeVec2 data)
{
    glShader* gl_shader = (glShader*)shader;
    GLint location = glGetUniformLocation(gl_shader->id, name);
    glUniform2f(location, data.x, data.y);
}

void glSetFloat3(void* shader, const char* name, primeVec3 data)
{
    glShader* gl_shader = (glShader*)shader;
    GLint location = glGetUniformLocation(gl_shader->id, name);
    glUniform3f(location, data.x, data.y, data.z);
}

void glSetFloat4(void* shader, const char* name, primeVec4 data)
{
    glShader* gl_shader = (glShader*)shader;
    GLint location = glGetUniformLocation(gl_shader->id, name);
    glUniform4f(location, data.x, data.y, data.z, data.w);
}

void glSetMat2(void* shader, const char* name, primeMat2 data)
{
    glShader* gl_shader = (glShader*)shader;
    GLint location = glGetUniformLocation(gl_shader->id, name);
    glUniformMatrix2fv(location, 1, GL_FALSE, data.data);
}

void glSetMat3(void* shader, const char* name, primeMat3 data)
{
    glShader* gl_shader = (glShader*)shader;
    GLint location = glGetUniformLocation(gl_shader->id, name);
    glUniformMatrix3fv(location, 1, GL_FALSE, data.data);
}

void glSetMat4(void* shader, const char* name, primeMat4 data)
{
    glShader* gl_shader = (glShader*)shader;
    GLint location = glGetUniformLocation(gl_shader->id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, data.data);
}

void glSetBuffer(void* buffer)
{
    glBuffer* gl_buffer = (glBuffer*)buffer;
    glBindBuffer(gl_buffer->type, gl_buffer->id);
}

void glSetShader(void* shader)
{
    glShader* gl_shader = (glShader*)shader;
    glUseProgram(gl_shader->id);
}

void glSetLayout(void* layout)
{
    glLayout* gl_layout = (glLayout*)layout;
    gl_layout->stride = 0;
    u32 index = 0;
    
    for (primeElement& element : gl_layout->elements) {
        element.offset = gl_layout->stride;
        gl_layout->stride += element.size;
    }

    for (const primeElement& element : gl_layout->elements) {
        u32 count = getDataTypeCount(element.type);
        u32 type = typeToGLType(element.type);
        u32 stride = gl_layout->stride;

        switch (element.type) {
            case PRIME_DATA_TYPE_FLOAT:
            case PRIME_DATA_TYPE_FLOAT2:
            case PRIME_DATA_TYPE_FLOAT3:
            case PRIME_DATA_TYPE_FLOAT4: {
                glVertexAttribPointer(
                    index,
                    count,
                    type,
                    element.normalize,
                    stride,
                    (const void*)element.offset);

                glEnableVertexAttribArray(index);
                glVertexAttribDivisor(index, element.divisor);
                break;
            }

            case PRIME_DATA_TYPE_INT:
            case PRIME_DATA_TYPE_INT2:
            case PRIME_DATA_TYPE_INT3:
            case PRIME_DATA_TYPE_INT4:
            case PRIME_DATA_TYPE_BOOL: {
                glVertexAttribIPointer(
                    index,
                    count,
                    type,
                    stride,
                    (const void*)element.offset);

                glEnableVertexAttribArray(index);
                glVertexAttribDivisor(index, element.divisor);
                break;
            }

        } // switch
        index++;
    }
}