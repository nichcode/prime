
#pragma once

#include "prime/defines.h"
#include "vendor/glcorearb.h"

struct GLVersion
{
    i32 major = 0;
    i32 minor = 0;
};

static GLVersion glVersion;

static PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
static PFNGLDELETETEXTURESPROC glDeleteTextures = nullptr;
static PFNGLGENTEXTURESPROC glGenTextures = nullptr;
static PFNGLBINDTEXTUREPROC glBindTexture = nullptr;
static PFNGLDRAWBUFFERPROC glDrawBuffer = nullptr;
static PFNGLDRAWARRAYSPROC glDrawArrays = nullptr;
static PFNGLCREATESHADERPROC glCreateShader = nullptr;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
static PFNGLUNIFORM1FPROC glUniform1f = nullptr;
static PFNGLUNIFORM2FVPROC glUniform2fv = nullptr;
static PFNGLUNIFORM3FVPROC glUniform3fv = nullptr;
static PFNGLUNIFORM1IPROC glUniform1i = nullptr;
static PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;
static PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor = nullptr;
static PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;
static PFNGLBUFFERSUBDATAPROC glBufferSubData = nullptr;
static PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced = nullptr;
static PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = nullptr;
static PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = nullptr;
static PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = nullptr;
static PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = nullptr;
static PFNGLDRAWBUFFERSPROC glDrawBuffers = nullptr;
static PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = nullptr;
static PFNGLBLENDFUNCIPROC glBlendFunci = nullptr;
static PFNGLBLENDEQUATIONPROC glBlendEquation = nullptr;
static PFNGLCLEARBUFFERFVPROC glClearBufferfv = nullptr;
static PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
static PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
static PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
static PFNGLATTACHSHADERPROC glAttachShader = nullptr;
static PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
static PFNGLVALIDATEPROGRAMPROC glValidateProgram = nullptr;
static PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
static PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
static PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = nullptr;
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
static PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
static PFNGLBINDBUFFERBASEPROC glBindBufferBase = nullptr;
static PFNGLBUFFERDATAPROC glBufferData = nullptr;
static PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = nullptr;
static PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
static PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;
static PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
static PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
static PFNGLDETACHSHADERPROC glDetachShader = nullptr;
static PFNGLDELETESHADERPROC glDeleteShader = nullptr;
static PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced = nullptr;
static PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;
static PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback = nullptr;
static PFNGLGETSTRINGPROC glGetstring = nullptr;

static PFNGLTEXIMAGE2DPROC glTexImage2D;
static PFNGLTEXPARAMETERIPROC glTexParameteri;
static PFNGLTEXPARAMETERFVPROC glTexParameterfv;
static PFNGLCLEARPROC glClear;
static PFNGLCLEARCOLORPROC glClearColor;
static PFNGLREADBUFFERPROC glReadBuffer;
static PFNGLDEPTHMASKPROC glDepthMask;
static PFNGLDISABLEPROC glDisable;
static PFNGLENABLEPROC glEnable;
static PFNGLSCISSORPROC glScissor;
static PFNGLVIEWPORTPROC glViewport;
static PFNGLDEPTHFUNCPROC glDepthFunc;
static PFNGLCULLFACEPROC glCullFace;
static PFNGLBLENDFUNCPROC glBlendFunc;
static PFNGLFRONTFACEPROC glFrontFace;
static PFNGLUNIFORM2FPROC glUniform2f;
static PFNGLUNIFORM3FPROC glUniform3f;
static PFNGLUNIFORM4FPROC glUniform4f;
static PFNGLUNIFORM1IVPROC glUniform1iv;
static PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
static PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
static PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;
static PFNGLDRAWELEMENTSPROC glDrawElements;

void loadOpenGLFunctions();