#pragma once

#include <string>
#include <cmath>

struct Vector2
{
    float x;
    float y;

    constexpr Vector2() : x{0.f}, y{0.f} {}
    constexpr Vector2(float x, float y) : x{x}, y{y} {}

    inline Vector2 operator +(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
    inline Vector2 operator -(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }
    inline Vector2 operator *(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
    inline Vector2 operator / (float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }
    inline Vector2 operator -() const {
        return Vector2(-x, -y);
    }

    inline float Dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }
    inline float Magnitude() const {
        return std::sqrt(x * x + y * y);
    }
    inline Vector2 Normalized() const {
        float mag = Magnitude();
        if (mag == 0) return Vector2(0, 0);
        return Vector2(x / mag, y / mag);
    }

    inline std::string ToString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

};

inline Vector2 operator *(float scalar, const Vector2& vec) {
    return vec * scalar;
}
