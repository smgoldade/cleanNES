#include "../renderer/Win32OpenGLRenderingProcessor.h"
#include "Win32Window.h"

Win32Window::~Win32Window() {
    if(renderer) {
        renderer->destroy_renderer();
    }
}

auto Win32Window::create(const vec2i& _position, const vec2i& dimension, const std::string& _title) -> bool {
    return create(_position.x, _position.y, dimension.x, dimension.y, _title);
}

auto Win32Window::create(const s32 x, const s32 y, const s32 _width, const s32 _height, const std::string& _title) -> bool {
    position = vec2i(x, y);
    width = _width;
    height = _height;
    title = _title;

    LPCSTR cleanNES_class = "cleanNES";
    auto h_instance = GetModuleHandle(nullptr);

    WNDCLASS wc = {};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = windows_event_callback;
    wc.hInstance = h_instance;
    wc.lpszClassName = cleanNES_class;
    wc.cbWndExtra = sizeof(Win32Window*); // NOLINT(bugprone-sizeof-expression) -> We do want the size of the pointer!
    if(!RegisterClass(&wc)) {
        spdlog::error("Unable to register window class.");
        return false;
    }

    window = CreateWindowEx(
        0,
        cleanNES_class,
        _title.c_str(),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,

        x, y, _width, _height,
        nullptr,
        nullptr,
        h_instance,
        this
    );

    if(!window) {
        spdlog::error("Unable to create Win32Window.");
        return false;
    }

    close_request = false;
    return true;
}

void Win32Window::set_title(const std::string& _title) {
    this->title = _title;
    SetWindowText(window, _title.c_str());
}

void Win32Window::process_events() {
    MSG msg {};
    if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if(msg.message == WM_QUIT) {
            if(renderer) {
                renderer->destroy_renderer();
            }
            DestroyWindow(window);
            close_request = true;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

bool Win32Window::should_close() {
    return close_request;
}

auto Win32Window::individual_callback(UINT msg, WPARAM w_param, LPARAM l_param) -> LRESULT {
    switch(msg) {
        case WM_CLOSE:
            spdlog::info("Window close request received.");
            renderer->destroy_renderer();
            close_request = true;
            DestroyWindow(window);
            return 0;
        case WM_CREATE:
            renderer = std::make_shared<Renderer>(std::make_unique<Win32OpenGLRenderingProcessor>(window));
            renderer->create_renderer();
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            ValidateRect(window, nullptr);
            return 0;
        default:
            return DefWindowProc(window, msg, w_param, l_param);
    }
}

auto Win32Window::windows_event_callback(HWND window, UINT msg, WPARAM w_param, LPARAM l_param) -> LRESULT {
    Win32Window* target_window;

    if(msg == WM_NCCREATE) {
        // point the user data to our instance which was passed as the create parameter;
        auto lpcs = reinterpret_cast<LPCREATESTRUCT>(l_param);
        target_window = static_cast<Win32Window*>(lpcs->lpCreateParams);
        target_window->window = window;
        SetWindowLongPtr(window, 0, reinterpret_cast<LONG_PTR>(target_window));
    } else {
        target_window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(window, 0));
    }

    if(target_window) {
        return target_window->individual_callback(msg, w_param, l_param);
    }
    return DefWindowProc(window, msg, w_param, l_param);
}

auto Win32Window::get_renderer() -> std::shared_ptr<Renderer> {
    return renderer;
}

