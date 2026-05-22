/** @file Vector2.hpp */
#pragma once

#include <string>
#include <cmath>

/**
 * @brief Standard 2-dimensional vector
 */
struct Vector2
{
    /** @brief X Component */
    float x;
    /** @brief Y Component */
    float y;

    /** @brief Constructs zero vector */
    constexpr Vector2() : x{0.f}, y{0.f} {}
    /** @brief Constructs custom vector @param x X @param y Y */
    constexpr Vector2(float x, float y) : x(x), y(y) {}
    /** @brief Constructs vector from copy @param vec Vector to copy */
    constexpr Vector2(const Vector2& vec) : x(vec.x), y(vec.y) {} 

    inline static constexpr Vector2 Up() { return Vector2{0.f,1.f}; }
    inline static constexpr Vector2 Right() { return Vector2{1.f,0.f}; }

    /** @returns addition of two vectors */
    inline Vector2 operator +(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
    /** @brief Adds to vector */
    inline void operator +=(const Vector2& other) {
        x += other.x;
        y += other.y;
    }
    /** @returns subtraction of two vectors */
    inline Vector2 operator -(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }
    /** @brief Subtracts from vector */
    inline void operator -=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
    }
    /** @returns amplification by a scalar */
    inline Vector2 operator *(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
    /** @returns [hadamard product](https://en.wikipedia.org/wiki/Hadamard_product_(matrices)) of two vectors */
    inline Vector2 operator *(const Vector2& other) const {
        return Vector2(x*other.x, y*other.y);
    }
    /** @returns division of two vectors */
    inline Vector2 operator /(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }
    /** @returns negation of vector */
    inline Vector2 operator -() const {
        return Vector2(-x, -y);
    }

    /** @returns swizzled vector (x,y)->(y,x) */
    inline Vector2 Swizzled() const {
        return Vector2(y, x);
    }
    /** @returns [dot product](https://en.wikipedia.org/wiki/Euclidean_vector#Dot_product) of two vectors */
    inline float Dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }
    /** @returns [magnitude](https://en.wikipedia.org/wiki/Euclidean_vector#Length) of vector */
    inline float Magnitude() const {
        return std::hypotf(x,y);
    }
    /** @returns [unit](https://en.wikipedia.org/wiki/Euclidean_vector#Unit_vector) vector */
    inline Vector2 Normalized() const {
        float mag = Magnitude();
        if (mag == 0.f) return Vector2(0.f, 0.f);
        return Vector2(x / mag, y / mag);
    }
    /** @returns distance to another vector */
    inline float Distance(const Vector2& other) const {
        const float dx = x-other.x;
        const float dy = y-other.y;

        return std::sqrt(dx * dx + dy * dy );
    }
    /** @returns the square of the distance to another vector */
    inline float SquaredDistance(const Vector2& other) const {
        const float dx = x-other.x;
        const float dy = y-other.y;

        return  dx * dx + dy * dy;
    }

    /** @returns string representation of vector */
    inline std::string ToString() const {
        return "(" + std::to_string((int)x) + ", " + std::to_string((int)y) + ")";
    }
    /** @returns string representation of vector using float */
    inline std::string ToStringF() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

};

inline Vector2 operator *(float scalar, const Vector2& vec) {
    return vec * scalar;
}
