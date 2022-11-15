#ifndef _WIN32WINDOW_H_
#define _WIN32WINDOW_H_
#include <spdlog/spdlog.h>
#include <memory>
#include <Windows.h>
#include "../types.h"
#include "Window.h"

class Win32Window : public Window {
public:
    ~Win32Window();
    auto create(s32 x, s32 y, s32 _width, s32 _height, const std::string& _title) -> bool override;
    auto create(const vec2i& _position, const vec2i& dimension, const std::string& _title) -> bool override;
    auto set_title(const std::string& _title) -> void override;
    auto process_events() -> void override;
    auto should_close() -> bool override;
    auto get_renderer() -> std::shared_ptr<Renderer> override;
private:
    std::shared_ptr<Renderer> renderer;
    vec2i position;
    s32 width, height;
    std::string title;
    HWND window;
    bool close_request = false;


    auto individual_callback(UINT msg, WPARAM w_param, LPARAM l_param) -> LRESULT;
    // Static method is required, we dispatch to individual callbacks as necessary
    static auto CALLBACK windows_event_callback(HWND window, UINT msg, WPARAM w_param, LPARAM l_param) -> LRESULT;
};

#endif //_WIN32WINDOW_H_