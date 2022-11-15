#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include "types.h"
#include "window/Win32Window.h"

bool running;
std::unique_ptr<std::thread> render_thread;

auto init_logging() -> void {
    auto new_logger = spdlog::basic_logger_mt("logger", "logs/cleanNES.log");
    spdlog::set_default_logger(new_logger);
    spdlog::enable_backtrace(32);
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%D %H:%M:%S %z] [%t] (%l) %v");
    spdlog::flush_on(spdlog::level::info);
    spdlog::info("cleanNES logging initialized.");
}

auto main() -> int {
    init_logging();

    auto win32_window = Win32Window();
    if(!win32_window.create(30,30,800,680,"cleanNES")) {
        return -1;
    }

    win32_window.get_renderer()->clear_color({0, 64, 64});
    while(!win32_window.should_close()) {
        win32_window.get_renderer()->clear();
        win32_window.process_events();
        win32_window.get_renderer()->draw_frame();
    }

    return 0;
}