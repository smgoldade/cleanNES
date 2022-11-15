#ifndef _WINDOW_H_
#define _WINDOW_H_
#include <string>
#include "../types.h"
#include "../vector.h"
#include "../vector.tpp"
#include "../renderer/Renderer.h"

class Window {
public:
    virtual ~Window() = default;
    virtual auto create(s32 x, s32 y, s32 width, s32 height, const std::string& title) -> bool = 0;
    virtual auto create(const vec2i& position, const vec2i& dimension, const std::string& title) -> bool = 0;
    virtual auto set_title(const std::string& title) -> void = 0;
    virtual auto process_events() -> void = 0;
    virtual auto should_close() -> bool = 0;
    virtual auto get_renderer() -> std::shared_ptr<Renderer> = 0;
};

#endif //_WINDOW_H_