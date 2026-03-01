#pragma once

#include <cmath>

namespace csbox {
namespace math {

struct Vector3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    Vector3() = default;

    Vector3(float x, float y, float z) 
        : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    float distanceTo(const Vector3& other) const {
        return (*this - other).length();
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3 normalized() const {
        float len = length();
        if (len > 0.0001f) {
            return *this * (1.0f / len);
        }
        return Vector3(0.0f, 0.0f, 0.0f);
    }
};

} // namespace math
} // namespace csbox
