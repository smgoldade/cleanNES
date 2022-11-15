#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "Renderer.h"

Renderer::Renderer(std::unique_ptr<RenderingProcessor> _rendering_processor) : rendering_processor(std::move(_rendering_processor)) {
    spdlog::info("Starting rendering thread...");
    running = true;
    destroyed = false;
    background_thread = std::thread(&Renderer::process_thread, this);
    spdlog::info("Rendering thread ID: [{}]", background_thread.get_id());
}

Renderer::~Renderer() {
    if(!destroyed) {
        spdlog::warn("Renderer deconstructed without being destroyed.");
        destroy_renderer();
    }
    running = false;
    background_thread.join();
}

auto Renderer::prepare_renderer() -> void {

}

auto Renderer::create_renderer() -> void {
    auto command = std::make_shared<RenderingCommand>(RenderingCommand{
        .type = RenderingCommandType::CREATE,
    });
    submit(command);
    while(!command->executed);
    if(command->error) {
        spdlog::error("Error creating renderer.");
        return;
    }
    destroyed = false;
}

auto Renderer::destroy_renderer() -> void {
    if(destroyed) {
        spdlog::warn("Already destroyed renderer told to destroy again.");
        return;
    }

    auto command = std::make_shared<RenderingCommand>(RenderingCommand{
        .type = RenderingCommandType::DESTROY,
    });
    rendering_queue.clear();
    submit(command);
    spdlog::debug("Renderer destruction issued.");
    while(!command->executed);
    spdlog::debug("Renderer destruction complete.");
    destroyed = true;
}

auto Renderer::clear(bool color_buffer, bool depth_buffer) -> void {
    submit(std::make_shared<RenderingCommand>(RenderingCommand{
        .type = RenderingCommandType::CLEAR,
        .color_clear = color_buffer,
        .depth_clear = depth_buffer
    }));
}

auto Renderer::clear_color(const Color& color) -> void {
    submit(std::make_shared<RenderingCommand>(RenderingCommand{
        .type = RenderingCommandType::CLEAR_COLOR,
        .color = &color
    }));
}

auto Renderer::draw_frame() -> void {
    submit(std::make_shared<RenderingCommand>(RenderingCommand{
        .type = RenderingCommandType::DRAW_FRAME
    }));
}

auto Renderer::update_viewport(const vec2i& position, const vec2i& size) -> void {
    submit(std::make_shared<RenderingCommand>(RenderingCommand{
        .type = RenderingCommandType::UPDATE_VIEWPORT,
        .position = &position,
        .size = &size,
    }));
}

auto Renderer::create_texture(const vec2i& size) -> texture_id {
    auto command = std::make_shared<RenderingCommand>(RenderingCommand{
        .type = RenderingCommandType::CREATE_TEXTURE,
        .size = &size
    });
    submit(command);
    while(!command->executed);
    return command->texture_id;
}

auto Renderer::create_texture(s32 width, s32 height) -> texture_id {
    return create_texture({width, height});
}

auto Renderer::delete_texture(texture_id texture_id) -> void {
    submit(std::make_shared<RenderingCommand>(RenderingCommand{
        .type = RenderingCommandType::DELETE_TEXTURE,
        .texture_id = texture_id
    }));
}

auto Renderer::apply_texture(texture_id texture_id) -> void {
    submit(std::make_shared<RenderingCommand>(RenderingCommand{
        .type = RenderingCommandType::APPLY_TEXTURE,
        .texture_id = texture_id
    }));
}

auto Renderer::update_texture(texture_id texture_id, const Texture& texture) -> void {
    submit(std::make_shared<RenderingCommand>(RenderingCommand{
        .type = RenderingCommandType::APPLY_TEXTURE,
        .texture_id = texture_id,
        .texture = &texture
    }));
}

auto Renderer::submit(const std::shared_ptr<RenderingCommand>& command) -> void {
    auto back = rendering_queue.back_or_nullptr();
    if(!back) {
        rendering_queue.push(command);
        return;
    }
    if((*back)->type != RenderingCommandType::DRAW_FRAME)  {
        rendering_queue.push(command);
        return;
    }
    while(!rendering_queue.empty());
    rendering_queue.push(command);
}

auto Renderer::process_thread() -> void {
    while(running) {
        if(!rendering_queue.empty()) {
            auto command = rendering_queue.front();
            rendering_processor->process_command(command);
            rendering_queue.pop();
            command->executed = true;
        }
    }
}
