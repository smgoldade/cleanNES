#ifndef _COLOR_H_
#define _COLOR_H_
#include <algorithm>
#include "../types.h"

struct Color {
    union {
        u32 n = 0xFFFFFFFF;
        struct {
            u8 r;
            u8 g;
            u8 b;
            u8 a;
        };
    };

    Color();
    Color(u8 _r, u8 _g, u8 _b, u8 _a = 255);
    Color(u32 _n);

    auto r_f() const -> f32;
    auto g_f() const -> f32;
    auto b_f() const -> f32;
    auto a_f() const -> f32;

    auto operator+(const Color& other) const -> Color;
    auto operator-(const Color& other) const -> Color;
    template <typename T>
    auto operator*(const T& scalar) const -> Color;
    template <typename T>
    auto operator/(const T& scalar) const -> Color;

    auto operator=(const Color& other) -> Color& = default;
    auto operator+=(const Color& other) -> Color&;
    auto operator-=(const Color& other) -> Color&;
    template <typename T>
    auto operator*=(const T& scalar) -> Color&;
    template <typename T>
    auto operator/=(const T& scalar) -> Color&;

    auto operator==(const Color& other) const -> bool;
    auto operator!=(const Color& other) const -> bool;
};

template <typename T>
auto operator*(const T& scalar, Color& vec) -> Color;
template <typename T>
auto operator/(const T& scalar, Color& vec) -> Color;

static const Color
    RED(255,0,0), PINK(255,175,175), ORANGE(255,200,0), YELLOW(255,255,0), GREEN(0,255,0), MAGENTA(255,0,255), CYAN(0,255,255), BLUE(0,0,255),
    WHITE(255, 255, 255), LIGHT_GRAY(192,192,192), GRAY(128,128,128), DARK_GRAY(64,64,64), BLACK(0,0,0), BLANK(0,0,0,0);
#endif //_COLOR_H_