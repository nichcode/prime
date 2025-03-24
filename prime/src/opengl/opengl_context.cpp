
#include "opengl_context.h"
#include "pch.h"
#include "opengl/opengl_funcs.h"
#include "prime/window.h"

PRIME_INLINE u32 getDataTypeSize(prime_data_type type)
{
    switch (type)
    {
        case PRIME_DATA_TYPE_INT:
        case PRIME_DATA_TYPE_FLOAT: {
            return 4;
        }

        case PRIME_DATA_TYPE_INT2:
        case PRIME_DATA_TYPE_FLOAT2: {
            return 8;
        }

        case PRIME_DATA_TYPE_INT3:
        case PRIME_DATA_TYPE_FLOAT3: {
            return 12;
        }

        case PRIME_DATA_TYPE_INT4:
        case PRIME_DATA_TYPE_FLOAT4: {
            return 16;
        }
        case PRIME_DATA_TYPE_BOOL:     return 1;
    }
    return 0;
}

PRIME_INLINE u32 getDataTypeCount(prime_data_type type)
{
    switch (type)
    {
        case PRIME_DATA_TYPE_FLOAT:
        case PRIME_DATA_TYPE_INT:
        case PRIME_DATA_TYPE_BOOL: {
            return 1;
        }

        case PRIME_DATA_TYPE_FLOAT2:
        case PRIME_DATA_TYPE_INT2: {
            return 2;
        }

        case PRIME_DATA_TYPE_FLOAT3:
        case PRIME_DATA_TYPE_INT3: {
            return 3;
        }

        case PRIME_DATA_TYPE_FLOAT4:
        case PRIME_DATA_TYPE_INT4: {
            return 4;
        }
    }
    return 0;
}

PRIME_INLINE static GLenum typeToGLType(prime_data_type type)
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

PRIME_INLINE static GLenum drawModeToGL(prime_draw_mode mode)
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

#ifdef PRIME_PLATFORM_WINDOWS

#include "win32/wgl_context.h"

struct gl_buffer
{
    u32 id = 0;
    u32 type;
    u32 usage;
};

struct gl_shader
{
    u32 id = 0;
};

struct Element
{
    prime_data_type type = PRIME_DATA_TYPE_FLOAT3;
    b8 normalize = false;
    u64 offset = 0;
    u32 size = 0;
    u32 divisor = 0;
};

struct gl_layout
{
    u32 stride = 0;
    std::vector<Element> elements;
};

struct gl_context
{
    HWND window_handle;
    HGLRC handle;
    HDC device_context;
    u32 vao = 0;
};

PRIME_INLINE u32 bufferTypeToGL(prime_buffer_type type)
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

PRIME_INLINE u32 bufferUsageToGL(prime_buffer_usage usage)
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

void* gl_create_context(prime_window* window)
{
    gl_context* gl_con = new gl_context();
    gl_con->window_handle = (HWND)prime_get_window_handle(window);
    gl_con->handle = createWGLContext(gl_con->window_handle);
    gl_con->device_context = GetDC(gl_con->window_handle);

    glGenVertexArrays(1, &gl_con->vao);
    glBindVertexArray(gl_con->vao);
    return gl_con;
}

void gl_destroy_context(void* context)
{
    gl_context* gl_con = (gl_context*)context;
    destroyWGLContext(gl_con->handle);
    ReleaseDC(gl_con->window_handle, gl_con->device_context);
    glDeleteVertexArrays(1, &gl_con->vao);
    gl_con->window_handle = 0;
    gl_con->handle = 0;
    gl_con->device_context = 0;
    
    delete gl_con;
    context = nullptr;
    gl_con = nullptr;
}

void gl_context_present(void* context)
{
    gl_context* gl_con = (gl_context*)context;
    SwapBuffers(gl_con->device_context);
}

void gl_context_make_active(void* context)
{
    gl_context* gl_con = (gl_context*)context;
    makeWGLContextCurrent(gl_con->window_handle, gl_con->handle);
}

void gl_context_set_vsync(void* context, b8 vsync)
{
    setWGLContextVsync(vsync);
}

#endif // PRIME_PLATFORM_WINDOWS

void gl_context_submit(void* context, prime_draw_type type, prime_draw_mode mode, u32 count)
{
    GLenum gl_type = drawModeToGL(mode);
    if (type == PRIME_DRAW_TYPE_ARRAYS) {
        glDrawArrays(gl_type, 0, count);
    }
    else if (type == PRIME_DRAW_TYPE_ELEMENTS) {
        glDrawElements(gl_type, 6, GL_UNSIGNED_INT, nullptr);
    }
}

void gl_context_clear(void* context)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gl_context_set_clearcolor(void* context, f32 r, f32 g, f32 b, f32 a)
{
    glClearColor(r, g, b, a);
}

void gl_context_set_clearcolor(void* context, const prime_view* view)
{
    glViewport(view->pos.x, view->pos.y, view->size.x, view->size.y);
}

void* gl_create_buffer(prime_buffer_desc desc)
{
    gl_buffer* buffer = new gl_buffer();
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

void gl_destroy_buffer(void* buffer)
{
    gl_buffer* gl_buf = (gl_buffer*)buffer;
    glDeleteBuffers(1, &gl_buf->id);
    delete gl_buf;
    gl_buf = nullptr;
    buffer = nullptr;
}

void* gl_create_shader(prime_shader_desc desc)
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
    
    gl_shader* shader = new gl_shader();
    shader->id = generateProgram(vertex_shader, pixel_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(pixel_shader);
    
    return shader;
}

void gl_destroy_shader(void* shader)
{
    gl_shader* gl_shad = (gl_shader*)shader;
    glDeleteProgram(gl_shad->id);
    delete gl_shad;
    gl_shad = nullptr;
    shader = nullptr;
}

void* gl_create_layout()
{
    gl_layout* layout = new gl_layout();
    return layout;
}

void gl_destroy_layout(void* layout)
{
    gl_layout* _layout = (gl_layout*)layout;
    delete _layout;
    layout = nullptr;
    _layout = nullptr;
}

void gl_set_buffer_data(void* buffer, const void* data, u32 size)
{
    gl_buffer* gl_buf = (gl_buffer*)buffer;
    glBufferSubData(gl_buf->type, 0, size, data);
}

void gl_add_attrib(void* layout, prime_data_type type, u32 divisor, b8 normalize)
{
    gl_layout* _layout = (gl_layout*)layout;
    Element element;
    element.divisor = divisor;
    element.normalize = normalize;
    element.type = type;
    element.size = getDataTypeSize(type);
    _layout->elements.push_back(element);
}

void gl_set_shader_int(void* shader, const char* name, i32 data)
{
    gl_shader* gl_shad = (gl_shader*)shader;
    GLint location = glGetUniformLocation(gl_shad->id, name);
    glUniform1i(location, data);
}

void gl_set_shader_int_array(void* shader, const char* name, i32* data, u32 count)
{
    gl_shader* gl_shad = (gl_shader*)shader;
    GLint location = glGetUniformLocation(gl_shad->id, name);
    glUniform1iv(location, count, data);
}

void gl_set_shader_float(void* shader, const char* name, f32 data)
{
    gl_shader* gl_shad = (gl_shader*)shader;
    GLint location = glGetUniformLocation(gl_shad->id, name);
    glUniform1f(location, data);
}

void gl_set_shader_float2(void* shader, const char* name, prime_vec2 data)
{
    gl_shader* gl_shad = (gl_shader*)shader;
    GLint location = glGetUniformLocation(gl_shad->id, name);
    glUniform2f(location, data.x, data.y);
}

void gl_set_shader_float3(void* shader, const char* name, prime_vec3 data)
{
    gl_shader* gl_shad = (gl_shader*)shader;
    GLint location = glGetUniformLocation(gl_shad->id, name);
    glUniform3f(location, data.x, data.y, data.z);
}

void gl_set_shader_float4(void* shader, const char* name, prime_vec4 data)
{
    gl_shader* gl_shad = (gl_shader*)shader;
    GLint location = glGetUniformLocation(gl_shad->id, name);
    glUniform4f(location, data.x, data.y, data.z, data.w);
}

void gl_set_shader_mat2(void* shader, const char* name, prime_mat2 data)
{
    gl_shader* gl_shad = (gl_shader*)shader;
    GLint location = glGetUniformLocation(gl_shad->id, name);
    glUniformMatrix2fv(location, 1, GL_FALSE, data.data);
}

void gl_set_shader_mat3(void* shader, const char* name, prime_mat3 data)
{
    gl_shader* gl_shad = (gl_shader*)shader;
    GLint location = glGetUniformLocation(gl_shad->id, name);
    glUniformMatrix3fv(location, 1, GL_FALSE, data.data);
}

void gl_set_shader_mat4(void* shader, const char* name, prime_mat4 data)
{
    gl_shader* gl_shad = (gl_shader*)shader;
    GLint location = glGetUniformLocation(gl_shad->id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, data.data);
}

void gl_set_buffer(void* buffer)
{
    gl_buffer* gl_buf = (gl_buffer*)buffer;
    glBindBuffer(gl_buf->type, gl_buf->id);
}

void gl_set_shader(void* shader)
{
    gl_shader* gl_shad = (gl_shader*)shader;
    glUseProgram(gl_shad->id);
}

void gl_set_layout(void* layout)
{
    gl_layout* _layout = (gl_layout*)layout;
    _layout->stride = 0;
    u32 index = 0;
    
    for (Element& element : _layout->elements) {
        element.offset = _layout->stride;
        _layout->stride += element.size;
    }

    for (const Element& element : _layout->elements) {
        u32 count = getDataTypeCount(element.type);
        u32 type = typeToGLType(element.type);
        u32 stride = _layout->stride;

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