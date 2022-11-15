#include <spdlog/spdlog.h>
#include "Win32OpenGLRenderingProcessor.h"

Win32OpenGLRenderingProcessor::Win32OpenGLRenderingProcessor(HWND _window) : window(_window) {}

Win32OpenGLRenderingProcessor::~Win32OpenGLRenderingProcessor() {
    destroy_context();
}

auto Win32OpenGLRenderingProcessor::process_command(std::shared_ptr<RenderingCommand> rendering_command) -> void {
    switch(rendering_command->type) {
        case RenderingCommandType::CLEAR: {
            GLbitfield mask = 0;
            mask += rendering_command->color_clear ? GL_COLOR_BUFFER_BIT : 0;
            mask += rendering_command->depth_clear ? GL_DEPTH_BUFFER_BIT : 0;
            glClear(mask);
            break;
        }
        case RenderingCommandType::CLEAR_COLOR: {
            glClearColor(rendering_command->color->r_f(), rendering_command->color->g_f(), rendering_command->color->b_f(), rendering_command->color->a_f());
            break;
        }
        case RenderingCommandType::CREATE: {
            if(!create_context()) {
                rendering_command->error = true;
            }
            break;
        }
        case RenderingCommandType::DESTROY: {
            destroy_context();
            break;
        }
        case RenderingCommandType::DRAW_FRAME: {
            SwapBuffers(device_context);
            break;
        }
        case RenderingCommandType::UPDATE_VIEWPORT: {
            glViewport(rendering_command->position->x, rendering_command->position->y, rendering_command->size->x, rendering_command->size->y);
            break;
        }
        case RenderingCommandType::CREATE_TEXTURE: {
            break;
        }
        case RenderingCommandType::DELETE_TEXTURE: {
            break;
        }
        case RenderingCommandType::APPLY_TEXTURE: {
            break;
        }
        case RenderingCommandType::UPDATE_TEXTURE: {
            break;
        }
    }
}

bool Win32OpenGLRenderingProcessor::create_context() {
    spdlog::info("OpenGL context creation started...");
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.cAuxBuffers = 0;

    device_context = GetDC(window);
    auto pf_id = ChoosePixelFormat(device_context, &pfd);
    if(!pf_id) {
        spdlog::error("Unable to get compatible pixel format.");
        return false;
    }
    SetPixelFormat(device_context, pf_id, &pfd);

    gl_render_context = wglCreateContext(device_context);
    if(!gl_render_context) {
        spdlog::error("Unable to construct OpenGL context.");
        return false;
    }
    wglMakeCurrent(device_context, gl_render_context);
    spdlog::info("OpenGL Version: {}", std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
    if(!OpenGL::bind_extensions()) {
        spdlog::error("Unable to bind OpenGL extensions");
        destroy_context();
        return false;
    }

    GLint extension_count = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &extension_count);

    spdlog::info("OpenGL Extensions Supported: {}", extension_count);
    for(auto i = 0; i < extension_count; i++) {
        spdlog::debug("-- {}", std::string(reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i))));
    }

    wglSwapIntervalEXT(0);

    return true;
}

void Win32OpenGLRenderingProcessor::destroy_context() {
    wglMakeCurrent(device_context, nullptr);
    wglDeleteContext(gl_render_context);
}
