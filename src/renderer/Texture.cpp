#include "Texture.h"

Texture::Texture(const s32 width, const s32 height) : width(width), height(height) {
    pixels.resize(width*height, WHITE);
}

Texture::~Texture() {
    pixels.clear();
}

auto Texture::set_pixel(const s32 x, const s32 y, const Color& color) -> bool {
    if(x >= 0 && x < width && y >= 0 && y < height) {
        pixels[y*width + x] = color;
        modified = true;
        return true;
    }
    return false;
}

auto Texture::set_pixel(const vec2i& position, const Color& color) -> bool {
    return set_pixel(position.x, position.y, color);
}

auto Texture::get_pixel(const s32 x, const s32 y) const -> Color {
    if(x >= 0 && x < width && y >= 0 && y < height) {
        return pixels[y*width + x];
    }
    return BLANK;
}

auto Texture::get_pixel(const vec2i& position) const -> Color {
    return get_pixel(position.x, position.y);
}

auto Texture::is_modified() const -> bool {
    return modified;
}

auto Texture::get_data() -> const Color* {
    modified = false;
    return pixels.data();
}
