#include "Scene.h"

Scene::Scene(s32 width, s32 height) : width(width), height(height) {
    layers.resize(1, Texture(width, height));
}

Scene::~Scene() {
    layers.clear();
}

auto Scene::create_layer() -> void {
    layers.resize(layers.size() + 1, Texture(width, height));
}

auto Scene::draw_pixel(s32 x, s32 y, const Color& color, size_t layer) -> bool {
    return layers[layer].set_pixel(x, y, color);
}

auto Scene::draw_pixel(const vec2i& position, const Color& color, size_t layer) -> bool {
    return draw_pixel(position.x, position.y, color, layer);
}

auto Scene::draw_line(s32 x0, s32 y0, s32 x1, s32 y1, const Color& color, u8 pattern, size_t layer) -> void {
    auto dx = std::abs(x1 - x0);
    auto dy = std::abs(y1 - y0);
    auto x_dir = x0 < x1 ? 1 : -1;
    auto y_dir = y0 < y1 ? 1 : -1;
    auto error = dx - dy;

    auto pat_check = [&] {
        pattern = (pattern << 1) | (pattern >> 7);
        return bool(pattern & 1);
    };

    // guaranteed to terminate as eventually x0 will equal x1 or y0 will equal y1
    while(true) {
        if(pat_check()) {
            draw_pixel(x0, y0, color, layer);
        }
        auto double_error = error * 2;
        if(double_error >= -dy) {
            if(x0 == x1) {
                return;
            }
            error -= dy;
            x0 += x_dir;
        }
        if(double_error <= dx) {
            if(y0 == y1) {
                return;
            }
            error += dx;
            y0 = y0 + y_dir;
        }
    }
}

auto Scene::draw_line(const vec2i& p0, const vec2i& p1, const Color& color, u8 pattern, size_t layer) -> void {
    draw_line(p0.x, p0.y, p1.x, p1.y, color, pattern, layer);
}