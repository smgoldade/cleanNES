/**
 * This header contains any OpenGL extensions definitions we need
 */
#ifndef _OPENGL_H_
#define _OPENGL_H_
#include <Windows.h>
#include <GL/GL.h>

#define GL_NUM_EXTENSIONS 0x821D
using PFNGLGETSTRINGI = GLubyte* (WINAPI *)(GLenum name, GLuint index);
using PFNWGLSWAPINTERVALEXT =  bool (WINAPI *)(int interval);

extern PFNGLGETSTRINGI glGetStringi;
extern PFNWGLSWAPINTERVALEXT wglSwapIntervalEXT;

namespace OpenGL {
    bool bind_extensions();
};

#endif //_OPENGL_H_