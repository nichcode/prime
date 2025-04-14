
#include "pch.h"
#include "opengl_funcs.h"
#include "prime/platform.h"

void* s_Dll;
void* _Load(const char* func_name);

#ifdef PR_PLATFORM_WINDOWS
    void* _Load(const char* func_name)
    {
        PROC proc = wglGetProcAddress(func_name);
        if (!proc) {
            proc = GetProcAddress((HMODULE)s_Dll, func_name);
            PR_ASSERT(proc, "failed to load gl function %s", func_name);
        }
        return (void*)proc;
    }
#endif // PRIME_PLATFORM_WINDOWS

void _LoadGL()
{
    s_Dll = prLoadLibrary("opengl32.dll");

    glGetstring = (PFNGLGETSTRINGPROC)_Load("glGetString");
    const char* version = (const char*) glGetstring(GL_VERSION);
    PR_ASSERT(version, "failed to get opengl version");

#ifdef _MSC_VER
    sscanf_s(version, "%d.%d", &major, &minor);
#else
    sscanf(version, "%d.%d", &glVersion.major, &glVersion.minor);
#endif

    glCreateProgram = (PFNGLCREATEPROGRAMPROC)_Load("glCreateProgram");
    glDeleteTextures = (PFNGLDELETETEXTURESPROC)_Load("glDeleteTextures");
    glGenTextures = (PFNGLGENTEXTURESPROC)_Load("glGenTextures");
    glBindTexture = (PFNGLBINDTEXTUREPROC)_Load("glBindTexture");
    glDrawArrays = (PFNGLDRAWARRAYSPROC)_Load("glDrawArrays");
    glCreateShader = (PFNGLCREATESHADERPROC) _Load("glCreateShader");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) _Load("glGetUniformLocation");
    glUniform1f = (PFNGLUNIFORM1FPROC) _Load("glUniform1f");
    glUniform2fv = (PFNGLUNIFORM2FVPROC) _Load("glUniform2fv");
    glUniform3fv = (PFNGLUNIFORM3FVPROC) _Load("glUniform3fv");
    glUniform1i = (PFNGLUNIFORM1IPROC) _Load("glUniform1i");
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) _Load("glUniformMatrix4fv");
    glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC) _Load("glVertexAttribDivisor");
    glActiveTexture = (PFNGLACTIVETEXTUREPROC) _Load("glActiveTexture");
    glBufferSubData = (PFNGLBUFFERSUBDATAPROC) _Load("glBufferSubData");
    glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC) _Load("glDrawArraysInstanced");
    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) _Load("glBindFramebuffer");
    glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) _Load("glCheckFramebufferStatus");
    glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) _Load("glGenFramebuffers");
    glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) _Load("glFramebufferTexture2D");
    glDrawBuffers = (PFNGLDRAWBUFFERSPROC) _Load("glDrawBuffers");
    glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) _Load("glDeleteFramebuffers");
    glBlendFunci = (PFNGLBLENDFUNCIPROC) _Load("glBlendFunci");
    glBlendEquation = (PFNGLBLENDEQUATIONPROC) _Load("glBlendEquation");
    glClearBufferfv = (PFNGLCLEARBUFFERFVPROC) _Load("glClearBufferfv");
    glShaderSource = (PFNGLSHADERSOURCEPROC) _Load("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC) _Load("glCompileShader");
    glGetShaderiv = (PFNGLGETSHADERIVPROC) _Load("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) _Load("glGetShaderInfoLog");
    glAttachShader = (PFNGLATTACHSHADERPROC) _Load("glAttachShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC) _Load("glLinkProgram");
    glValidateProgram = (PFNGLVALIDATEPROGRAMPROC) _Load("glValidateProgram");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC) _Load("glGetProgramiv");
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) _Load("glGetProgramInfoLog");
    glGenBuffers = (PFNGLGENBUFFERSPROC) _Load("glGenBuffers");
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) _Load("glGenVertexArrays");
    glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) _Load("glGetAttribLocation");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) _Load("glBindVertexArray");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) _Load("glEnableVertexAttribArray");
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) _Load("glVertexAttribPointer");
    glBindBuffer = (PFNGLBINDBUFFERPROC) _Load("glBindBuffer");
    glBindBufferBase = (PFNGLBINDBUFFERBASEPROC) _Load("glBindBufferBase");
    glBufferData = (PFNGLBUFFERDATAPROC) _Load("glBufferData");
    glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC) _Load("glGetVertexAttribPointerv");
    glUseProgram = (PFNGLUSEPROGRAMPROC) _Load("glUseProgram");
    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) _Load("glDeleteVertexArrays");
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) _Load("glDeleteBuffers");
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC) _Load("glDeleteProgram");
    glDetachShader = (PFNGLDETACHSHADERPROC) _Load("glDetachShader");
    glDeleteShader = (PFNGLDELETESHADERPROC) _Load("glDeleteShader");
    glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC) _Load("glDrawElementsInstanced");
    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) _Load("glGenerateMipmap");
    glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)_Load("glDebugMessageCallback");

    glTexImage2D = (PFNGLTEXIMAGE2DPROC)_Load("glTexImage2D");
    glTexParameteri = (PFNGLTEXPARAMETERIPROC)_Load("glTexParameteri");
    glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)_Load("glTexParameterfv");
    glClear = (PFNGLCLEARPROC)_Load("glClear");
    glClearColor = (PFNGLCLEARCOLORPROC)_Load("glClearColor");
    glReadBuffer = (PFNGLREADBUFFERPROC)_Load("glReadBuffer");
    glDepthMask = (PFNGLDEPTHMASKPROC)_Load("glDepthMask");
    glDisable = (PFNGLDISABLEPROC)_Load("glDisable");
    glEnable = (PFNGLENABLEPROC)_Load("glEnable");
    glScissor = (PFNGLSCISSORPROC)_Load("glScissor");
    glViewport = (PFNGLVIEWPORTPROC)_Load("glViewport");
    glDepthFunc = (PFNGLDEPTHFUNCPROC)_Load("glDepthFunc");
    glCullFace = (PFNGLCULLFACEPROC)_Load("glCullFace");
    glBlendFunc = (PFNGLBLENDFUNCPROC)_Load("glBlendFunc");
    glFrontFace = (PFNGLFRONTFACEPROC)_Load("glFrontFace");

    glUniform2f = (PFNGLUNIFORM2FPROC)_Load("glUniform2f");
    glUniform3f = (PFNGLUNIFORM3FPROC)_Load("glUniform3f");
    glUniform4f = (PFNGLUNIFORM4FPROC)_Load("glUniform4f");
    glUniform1iv = (PFNGLUNIFORM1IVPROC)_Load("glUniform1iv");
    glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)_Load("glUniformMatrix2fv");
    glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)_Load("glUniformMatrix3fv");
    glVertexAttribIPointer =  (PFNGLVERTEXATTRIBIPOINTERPROC)_Load("glVertexAttribIPointer");
    glDrawElements = (PFNGLDRAWELEMENTSPROC)_Load("glDrawElements");
    glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)_Load("glDisableVertexAttribArray");

    glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)_Load("glGenRenderbuffers");
    glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)_Load("glBindRenderbuffer");
    glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)_Load("glRenderbufferStorage");
    glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)_Load("glFramebufferRenderbuffer");
    glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)_Load("glDeleteRenderbuffers");
    glPixelStorei = (PFNGLPIXELSTOREIPROC)_Load("glPixelStorei");
    glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)_Load("glTexSubImage2D");
}