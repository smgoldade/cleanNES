#include "vector.h"

template <typename T>
vec2<T>::vec2() : x(0), y(0) {}

template <typename T>
vec2<T>::vec2(T _x, T _y) : x(_x), y(_y) {}

template <typename T>
vec2<T>::vec2(const vec2& other) : x(other.x), y(other.y) {}

template <typename T>
auto vec2<T>::yx() -> vec2 {
    return vec2(y, x);
}

template <typename T>
auto vec2<T>::ba() -> vec2 {
    return yx();
}

template <typename T>
vec2<T> vec2<T>::from_angle(const T angle) {
    return {std::cos(angle), std::sin(angle)};
}

template <typename T>
auto vec2<T>::magnitude() const -> T {
    return T(std::sqrt(x * x + y * y));
}

template <typename T>
auto vec2<T>::square_magnitude() const -> T {
    return T(x * x + y * y);
}

template <typename T>
auto vec2<T>::norm() const -> vec2 {
    return *this / magnitude();
}

template <typename T>
auto vec2<T>::perpendicular() const -> vec2  {
    return vec2(-y, x);
}

template <typename T>
auto vec2<T>::floor() const -> vec2 {
    return vec2(std::floor(x), std::floor(y));
}

template <typename T>
auto vec2<T>::ceil() const -> vec2 {
    return vec2(std::ceil(x), std::ceil(y));
}

template <typename T>
auto vec2<T>::dot(const vec2& other) const -> T {
    return T(x * other.x + y * other.y);
}

template <typename T>
auto vec2<T>::angle() const -> T {
    return T(std::atan2(y, x));
}

template <typename T>
auto vec2<T>::operator+() const -> vec2 {
    return vec2(+x, +y);
}

template <typename T>
auto vec2<T>::operator-() const -> vec2 {
    return vec2(-x, -y);
}

template <typename T>
auto vec2<T>::operator+(const vec2& other) const -> vec2 {
    return vec2(x + other.x, y + other.y);
}

template <typename T>
auto vec2<T>::operator-(const vec2& other) const -> vec2 {
    return vec2(x - other.x, y - other.y);
}

template <typename T>
auto vec2<T>::operator*(const T& scalar) const -> vec2{
    return vec2(x * scalar, y * scalar);
}

template <typename T>
auto vec2<T>::operator/(const T& scalar) const -> vec2{
    return vec2(x / scalar, y / scalar);
}

template <typename T>
auto vec2<T>::operator+=(const vec2& other) -> vec2& {
    x += other.x;
    y += other.y;
    return *this;
}

template <typename T>
auto vec2<T>::operator-=(const vec2& other) -> vec2& {
    x -= other.x;
    y -= other.y;
    return *this;
}

template <typename T>
auto vec2<T>::operator*=(const T& scalar) -> vec2& {
    x *= scalar;
    y *= scalar;
    return *this;
}

template <typename T>
auto vec2<T>::operator/=(const T& scalar) -> vec2& {
    x /= scalar;
    y /= scalar;
    return *this;
}

template <typename T>
auto vec2<T>::operator==(const vec2& other) const -> bool {
    return x == other.x && y == other.y;
}

template <typename T>
auto vec2<T>::operator!=(const vec2& other) const -> bool  {
    return x != other.x || y != other.y;
}

template <typename T, typename U>
auto operator*(const T& scalar, vec2<U>& vec) -> vec2<U> {
    return vec2<U>(scalar * vec.x, scalar * vec.y);
}

template <typename T, typename U>
auto operator/(const T& scalar, vec2<U>& vec) -> vec2<U> {
    return vec2<U>(scalar / vec.x, scalar / vec.y);
}
