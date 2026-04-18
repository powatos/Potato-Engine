#pragma once

#include <string>
#include <cmath>

struct Vector
{
    float x;
    float y;

    constexpr Vector() : x{0.f}, y{0.f} {}
    constexpr Vector(float x, float y) : x{x}, y{y} {}

    inline Vector operator +(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }
    inline Vector operator -(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }
    inline Vector operator *(float scalar) const {
        return Vector(x * scalar, y * scalar);
    }
    inline Vector operator / (float scalar) const {
        return Vector(x / scalar, y / scalar);
    }
    inline Vector operator -() const {
        return Vector(-x, -y);
    }

    inline float Dot(const Vector& other) const {
        return x * other.x + y * other.y;
    }
    inline float Magnitude() const {
        return std::sqrt(x * x + y * y);
    }
    inline Vector Normalized() const {
        float mag = Magnitude();
        if (mag == 0) return Vector(0, 0);
        return Vector(x / mag, y / mag);
    }

    inline std::string ToString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

};

inline Vector operator *(float scalar, const Vector& vec) {
    return vec * scalar;
}
