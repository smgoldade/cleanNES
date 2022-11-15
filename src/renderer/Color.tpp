#include "Color.h"

template <typename T>
auto Color::operator*(const T& scalar) const -> Color {
    return Color(
        std::min(255, std::max(0, r * scalar)),
        std::min(255, std::max(0, g * scalar)),
        std::min(255, std::max(0, b * scalar)),
        a
    );
}

template <typename T>
auto Color::operator/(const T& scalar) const -> Color {
    return Color(
        std::min(255, std::max(0, r / scalar)),
        std::min(255, std::max(0, g / scalar)),
        std::min(255, std::max(0, b / scalar)),
        a
    );
}

template <typename T>
auto Color::operator*=(const T& scalar) -> Color& {
    r = std::min(255, std::max(0, r * scalar));
    g = std::min(255, std::max(0, g * scalar));
    b = std::min(255, std::max(0, b * scalar));
    return *this;
}

template <typename T>
auto Color::operator/=(const T& scalar) -> Color& {
    r = std::min(255, std::max(0, r / scalar));
    g = std::min(255, std::max(0, g / scalar));
    b = std::min(255, std::max(0, b / scalar));
    return *this;
}



template <typename T>
auto operator*(const T& scalar, Color& vec) -> Color {
    return Color(
        std::min(255, std::max(0, scalar * vec.r)),
        std::min(255, std::max(0, scalar * vec.g)),
        std::min(255, std::max(0, scalar * vec.b)),
        vec.a
    );
}

template <typename T>
auto operator/(const T& scalar, Color& vec) -> Color {
    return Color(
        std::min(255, std::max(0, scalar / vec.r)),
        std::min(255, std::max(0, scalar / vec.g)),
        std::min(255, std::max(0, scalar / vec.b)),
        vec.a
    );
}
