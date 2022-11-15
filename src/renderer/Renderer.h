#ifndef _RENDERER_H_
#define _RENDERER_H_
#include <thread>
#include <queue>
#include "../ThreadSafeQueue.h"
#include "../types.h"
#include "../vector.h"
#include "RenderingCommand.h"
#include "RenderingProcessor.h"
#include "Texture.h"

class Renderer {

public:
    Renderer(std::unique_ptr<RenderingProcessor> _rendering_processor);
    auto prepare_renderer() -> void;
    auto create_renderer() -> void;
    auto destroy_renderer() -> void;

    auto clear(bool color_buffer = true, bool depth_buffer = true) -> void;
    auto clear_color(const Color& color) -> void;
    auto draw_frame() -> void;

    auto update_viewport(const vec2i& position, const vec2i& size) -> void;

    auto create_texture(s32 width, s32 height) -> texture_id;
    auto create_texture(const vec2i& size) -> texture_id;
    auto delete_texture(texture_id texture_id) -> void;
    auto apply_texture(texture_id texture_id) -> void;
    auto update_texture(texture_id texture_id, const Texture& texture) -> void;
private:
    ThreadSafeQueue<std::shared_ptr<RenderingCommand>> rendering_queue;
    std::unique_ptr<RenderingProcessor> rendering_processor;

    auto submit(const std::shared_ptr<RenderingCommand>& command) -> void;
    auto process_thread() -> void;

    std::thread background_thread;
    std::atomic<bool> running;
};

#endif //_RENDERER_H_