#include "Color.h"

Color::Color() : n(0xFFFFFFFF) {}

Color::Color(u8 _r, u8 _g, u8 _b, u8 _a) : r(_r), g(_g), b(_b), a(_a) {}

Color::Color(u32 _n) : n(_n) {}

auto Color::r_f() const -> f32 {
    return static_cast<f32>(r) / 255.0f;
}

auto Color::g_f() const -> f32 {
    return static_cast<f32>(g) / 255.0f;
}

auto Color::b_f() const -> f32 {
    return static_cast<f32>(b) / 255.0f;
}

auto Color::a_f() const -> f32 {
    return static_cast<f32>(a) / 255.0f;
}

auto Color::operator+(const Color& other) const -> Color {
    return {
        u8(std::min(255, std::max(0, r + other.r))),
        u8(std::min(255, std::max(0, g + other.g))),
        u8(std::min(255, std::max(0, b + other.b))),
        a
    };
}

auto Color::operator-(const Color& other) const -> Color {
    return {
        u8(std::min(255, std::max(0, r - other.r))),
        u8(std::min(255, std::max(0, g - other.g))),
        u8(std::min(255, std::max(0, b - other.b))),
        a
    };
}

auto Color::operator+=(const Color& other) -> Color& {
    r = u8(std::min(255, std::max(0, r + other.r)));
    g = u8(std::min(255, std::max(0, g + other.g)));
    b = u8(std::min(255, std::max(0, b + other.b)));
    return *this;
}

auto Color::operator-=(const Color& other) -> Color& {
    r = u8(std::min(255, std::max(0, r - other.r)));
    g = u8(std::min(255, std::max(0, g - other.g)));
    b = u8(std::min(255, std::max(0, b - other.b)));
    return *this;
}

auto Color::operator==(const Color& other) const -> bool {
    return n == other.n;
}

auto Color:: operator!=(const Color& other) const -> bool {
    return n != other.n;
}