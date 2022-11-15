#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <cmath>
#include "types.h"

template <typename T>
struct vec2 {
    union {
        T x = 0;
        T a;
    };
    union {
        T y = 0;
        T b;
    };

    vec2();
    vec2(T _x, T _y);
    vec2(const vec2& other);
    static vec2<T> from_angle(T angle);

    auto yx() -> vec2;
    auto ba() -> vec2;

    auto magnitude() const -> T;
    auto square_magnitude() const -> T;
    auto norm() const -> vec2;
    auto perpendicular() const -> vec2;
    auto floor() const -> vec2;
    auto ceil() const -> vec2;
    auto dot(const vec2& other) const -> T;
    auto angle() const -> T;

    auto operator+() const -> vec2;
    auto operator-() const -> vec2;
    auto operator+(const vec2& other) const -> vec2;
    auto operator-(const vec2& other) const -> vec2;
    auto operator*(const T& scalar) const -> vec2;
    auto operator/(const T& scalar) const -> vec2;

    auto operator=(const vec2& other) -> vec2& = default;
    auto operator+=(const vec2& other) -> vec2&;
    auto operator-=(const vec2& other) -> vec2&;
    auto operator*=(const T& scalar) -> vec2&;
    auto operator/=(const T& scalar) -> vec2&;

    auto operator==(const vec2& other) const -> bool;
    auto operator!=(const vec2& other) const -> bool;
};
template <typename T, typename U>
auto operator*(const T& scalar, vec2<U>& vec) -> vec2<U>;
template <typename T, typename U>
auto operator/(const T& scalar, vec2<U>& vec) -> vec2<U>;

using vec2f = vec2<f32>;
using vec2d = vec2<f64>;
using vec2i = vec2<s32>;

#endif //_VECTOR_H_