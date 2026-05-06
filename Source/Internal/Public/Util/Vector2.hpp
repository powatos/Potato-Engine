#pragma once

#include <string>
#include <cmath>

struct Vector2
{
    int x;
    int y;

    constexpr Vector2() : x{0}, y{0} {}
    constexpr Vector2(int x, int y) : x(x), y(y) {}
    constexpr Vector2(const Vector2& vec) : x(vec.x), y(vec.y) {} 

    inline Vector2 operator +(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
    inline Vector2 operator -(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }
    inline Vector2 operator *(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
    inline Vector2 operator *(const Vector2& other) const {
        return Vector2(x*other.x, y*other.y);
    }
    inline Vector2 operator / (float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }
    inline Vector2 operator -() const {
        return Vector2(-x, -y);
    }

    inline Vector2 Swizzled() const {
        return Vector2(y, x);
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
