#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "OpenGL.h"

PFNGLGETSTRINGI glGetStringi = nullptr;
PFNWGLSWAPINTERVALEXT wglSwapIntervalEXT = nullptr;

bool OpenGL::bind_extensions() {
    glGetStringi = reinterpret_cast<PFNGLGETSTRINGI>(wglGetProcAddress("glGetStringi"));
    if(!glGetStringi) {
        spdlog::error("Cannot find glGetStringi.");
        return false;
    }

    wglSwapIntervalEXT = reinterpret_cast<PFNWGLSWAPINTERVALEXT>(wglGetProcAddress("wglSwapIntervalEXT"));
    if(!glGetStringi) {
        spdlog::error("Cannot find wglSwapIntervalEXT.");
        return false;
    }

    return true;
}
