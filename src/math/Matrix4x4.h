#pragma once

#include "Vector3.h"

namespace csbox {
namespace math {

class Matrix4x4 {
public:
    Matrix4x4() = default;

    explicit Matrix4x4(const float data[16]) {
        for (int i = 0; i < 16; ++i) {
            m[i] = data[i];
        }
    }

    static Matrix4x4 identity() {
        Matrix4x4 result;
        result.m[0] = 1.0f; result.m[1] = 0.0f; result.m[2] = 0.0f; result.m[3] = 0.0f;
        result.m[4] = 0.0f; result.m[5] = 1.0f; result.m[6] = 0.0f; result.m[7] = 0.0f;
        result.m[8] = 0.0f; result.m[9] = 0.0f; result.m[10] = 1.0f; result.m[11] = 0.0f;
        result.m[12] = 0.0f; result.m[13] = 0.0f; result.m[14] = 0.0f; result.m[15] = 1.0f;
        return result;
    }

    Vector3 transform(const Vector3& v) const {
        return Vector3(
            m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12],
            m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13],
            m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14]
        );
    }

    Vector3 transformPerspective(const Vector3& v) const {
        Vector3 transformed = transform(v);
        float w = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15];
        
        if (std::abs(w) > 0.0001f) {
            transformed.x /= w;
            transformed.y /= w;
            transformed.z /= w;
        }
        
        return transformed;
    }

    float operator()(int row, int col) const {
        return m[col * 4 + row];
    }

    float& operator()(int row, int col) {
        return m[col * 4 + row];
    }

    const float* data() const { return m; }
    float* data() { return m; }

private:
    float m[16] = {};
};

} // namespace math
} // namespace csbox
