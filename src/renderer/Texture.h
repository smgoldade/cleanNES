#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <vector>
#include "../types.h"
#include "../vector.h"
#include "Color.h"

using texture_id = s32;

class Texture {
public:
    Texture(s32 width, s32 height);
    ~Texture();

    auto set_pixel(s32 x, s32 y, const Color& color) -> bool;
    auto set_pixel(const vec2i& position, const Color& color) -> bool;
    [[nodiscard]] auto get_pixel(s32 x, s32 y) const -> Color;
    [[nodiscard]] auto get_pixel(const vec2i& position) const -> Color;

    [[nodiscard]] auto is_modified() const -> bool;
    [[nodiscard]] auto get_data() -> const Color*;
private:
    std::vector<Color> pixels;
    s32 width, height;
    bool modified = false;
};

#endif //_TEXTURE_H_