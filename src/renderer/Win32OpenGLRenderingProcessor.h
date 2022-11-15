#ifndef _WIN32OPENGLRENDERINGPROCESSOR_H_
#define _WIN32OPENGLRENDERINGPROCESSOR_H_ \
#include <memory>
#include <Windows.h>
#include "OpenGL.h"
#include "RenderingProcessor.h"

class Win32OpenGLRenderingProcessor : public RenderingProcessor{
public:
    explicit Win32OpenGLRenderingProcessor(HWND _window);
    auto process_command(std::shared_ptr<RenderingCommand> rendering_command) -> void override;
private:
    HWND window;
    HDC device_context = nullptr;
    HGLRC gl_render_context = nullptr;
    auto create_context() -> bool;
    auto destroy_context() -> void;
};

#endif //_WIN32OPENGLRENDERINGPROCESSOR_H_