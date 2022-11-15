#ifndef _SCENE_H_
#define _SCENE_H_
#include <vector>
#include "../types.h"
#include "../vector.h"
#include "Texture.h"

class Scene {
public:
    Scene(s32 width, s32 height);
    ~Scene();

    auto create_layer() -> void;

    auto draw_pixel(s32 x, s32 y, const Color& color, size_t layer = 0) -> bool;
    auto draw_pixel(const vec2i& position, const Color& color, size_t layer = 0) -> bool;
    auto draw_line(s32 x0, s32 y0, s32 x1, s32 y1, const Color& color, u8 pattern = 0xFF, size_t layer = 0) -> void;
    auto draw_line(const vec2i& p0, const vec2i& p1, const Color& color, u8 pattern = 0xFF, size_t layer = 0) -> void;

private:
    s32 width, height;
    std::vector<Texture> layers;
};

#endif //_SCENE_H_