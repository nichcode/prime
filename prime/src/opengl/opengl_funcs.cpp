
#pragma once

#include "pch.h"
#include "opengl_funcs.h"
#include "prime/platform.h"

static void* s_Dll = nullptr;

#ifdef PRIME_PLATFORM_WINDOWS

static void* gl_load(const char* func_name)
{
    PROC proc = wglGetProcAddress(func_name);
    if (!proc) {
        proc = GetProcAddress((HMODULE)s_Dll, func_name);
        PRIME_ASSERT_MSG(proc, "failed to load gl function %s", func_name);
    }
    return (void*)proc;
}

#endif // PRIME_PLATFORM_WINDOWS

void loadOpenGLFunctions()
{
    s_Dll = prime_load_library("opengl32.dll");

    glGetstring = (PFNGLGETSTRINGPROC)gl_load("glGetString");
    const char* version = (const char*) glGetstring(GL_VERSION);
    PRIME_ASSERT_MSG(version, "failed to get opengl version");

#ifdef _MSC_VER
    sscanf_s(version, "%d.%d", &major, &minor);
#else
    sscanf(version, "%d.%d", &glVersion.major, &glVersion.minor);
#endif

    PRIME_ASSERT_MSG(
        glVersion.major >= 4 || (glVersion.major == 3 && glVersion.minor >= 3),
        "Prime requires at least OpenGL version 3.3!");

    glCreateProgram = (PFNGLCREATEPROGRAMPROC)gl_load("glCreateProgram");
    glDeleteTextures = (PFNGLDELETETEXTURESPROC)gl_load("glDeleteTextures");
    glGenTextures = (PFNGLGENTEXTURESPROC)gl_load("glGenTextures");
    glBindTexture = (PFNGLBINDTEXTUREPROC)gl_load("glBindTexture");
    glDrawArrays = (PFNGLDRAWARRAYSPROC)gl_load("glDrawArrays");
    glCreateShader = (PFNGLCREATESHADERPROC) gl_load("glCreateShader");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) gl_load("glGetUniformLocation");
    glUniform1f = (PFNGLUNIFORM1FPROC) gl_load("glUniform1f");
    glUniform2fv = (PFNGLUNIFORM2FVPROC) gl_load("glUniform2fv");
    glUniform3fv = (PFNGLUNIFORM3FVPROC) gl_load("glUniform3fv");
    glUniform1i = (PFNGLUNIFORM1IPROC) gl_load("glUniform1i");
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) gl_load("glUniformMatrix4fv");
    glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC) gl_load("glVertexAttribDivisor");
    glActiveTexture = (PFNGLACTIVETEXTUREPROC) gl_load("glActiveTexture");
    glBufferSubData = (PFNGLBUFFERSUBDATAPROC) gl_load("glBufferSubData");
    glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC) gl_load("glDrawArraysInstanced");
    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) gl_load("glBindFramebuffer");
    glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) gl_load("glCheckFramebufferStatus");
    glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) gl_load("glGenFramebuffers");
    glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) gl_load("glFramebufferTexture2D");
    glDrawBuffers = (PFNGLDRAWBUFFERSPROC) gl_load("glDrawBuffers");
    glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) gl_load("glDeleteFramebuffers");
    glBlendFunci = (PFNGLBLENDFUNCIPROC) gl_load("glBlendFunci");
    glBlendEquation = (PFNGLBLENDEQUATIONPROC) gl_load("glBlendEquation");
    glClearBufferfv = (PFNGLCLEARBUFFERFVPROC) gl_load("glClearBufferfv");
    glShaderSource = (PFNGLSHADERSOURCEPROC) gl_load("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC) gl_load("glCompileShader");
    glGetShaderiv = (PFNGLGETSHADERIVPROC) gl_load("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) gl_load("glGetShaderInfoLog");
    glAttachShader = (PFNGLATTACHSHADERPROC) gl_load("glAttachShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC) gl_load("glLinkProgram");
    glValidateProgram = (PFNGLVALIDATEPROGRAMPROC) gl_load("glValidateProgram");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC) gl_load("glGetProgramiv");
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) gl_load("glGetProgramInfoLog");
    glGenBuffers = (PFNGLGENBUFFERSPROC) gl_load("glGenBuffers");
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) gl_load("glGenVertexArrays");
    glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) gl_load("glGetAttribLocation");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) gl_load("glBindVertexArray");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) gl_load("glEnableVertexAttribArray");
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) gl_load("glVertexAttribPointer");
    glBindBuffer = (PFNGLBINDBUFFERPROC) gl_load("glBindBuffer");
    glBindBufferBase = (PFNGLBINDBUFFERBASEPROC) gl_load("glBindBufferBase");
    glBufferData = (PFNGLBUFFERDATAPROC) gl_load("glBufferData");
    glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC) gl_load("glGetVertexAttribPointerv");
    glUseProgram = (PFNGLUSEPROGRAMPROC) gl_load("glUseProgram");
    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) gl_load("glDeleteVertexArrays");
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) gl_load("glDeleteBuffers");
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC) gl_load("glDeleteProgram");
    glDetachShader = (PFNGLDETACHSHADERPROC) gl_load("glDetachShader");
    glDeleteShader = (PFNGLDELETESHADERPROC) gl_load("glDeleteShader");
    glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC) gl_load("glDrawElementsInstanced");
    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) gl_load("glGenerateMipmap");
    glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)gl_load("glDebugMessageCallback");

    glTexImage2D = (PFNGLTEXIMAGE2DPROC)gl_load("glTexImage2D");
    glTexParameteri = (PFNGLTEXPARAMETERIPROC)gl_load("glTexParameteri");
    glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)gl_load("glTexParameterfv");
    glClear = (PFNGLCLEARPROC)gl_load("glClear");
    glClearColor = (PFNGLCLEARCOLORPROC)gl_load("glClearColor");
    glReadBuffer = (PFNGLREADBUFFERPROC)gl_load("glReadBuffer");
    glDepthMask = (PFNGLDEPTHMASKPROC)gl_load("glDepthMask");
    glDisable = (PFNGLDISABLEPROC)gl_load("glDisable");
    glEnable = (PFNGLENABLEPROC)gl_load("glEnable");
    glScissor = (PFNGLSCISSORPROC)gl_load("glScissor");
    glViewport = (PFNGLVIEWPORTPROC)gl_load("glViewport");
    glDepthFunc = (PFNGLDEPTHFUNCPROC)gl_load("glDepthFunc");
    glCullFace = (PFNGLCULLFACEPROC)gl_load("glCullFace");
    glBlendFunc = (PFNGLBLENDFUNCPROC)gl_load("glBlendFunc");
    glFrontFace = (PFNGLFRONTFACEPROC)gl_load("glFrontFace");

    prime_free_library(s_Dll);
}