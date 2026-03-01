#pragma once

#include "Matrix4x4.h"
#include <cmath>

namespace csbox {
namespace math {

struct ScreenPoint {
    bool valid = false;
    float x = 0.0f;
    float y = 0.0f;
    float depth = 0.0f;
};

class WorldToScreen {
public:
    WorldToScreen() = default;

    void setViewMatrix(const Matrix4x4& matrix) {
        m_viewMatrix = matrix;
    }

    void setScreenSize(float width, float height) {
        m_screenWidth = width;
        m_screenHeight = height;
    }

    void setCameraPosition(const Vector3& pos) {
    }

    ScreenPoint calculate(const Vector3& worldPos) {
        ScreenPoint result;
        const float* m = m_viewMatrix.data();

        // Standard GoldSrc VP Matrix is typically Column-Major in memory
        // We calculate W first to determine if we should use Column or Row major
        
        // Try Column-Major (Pattern A)
        float w = worldPos.x * m[3] + worldPos.y * m[7] + worldPos.z * m[11] + m[15];
        float x, y;

        if (fabsf(w) < 0.01f || fabsf(w) > 30000.0f) {
            // Try Row-Major (Pattern B) — 必须同时重算 w，否则透视除法错误
            x = worldPos.x * m[0] + worldPos.y * m[1] + worldPos.z * m[2] + m[3];
            y = worldPos.x * m[4] + worldPos.y * m[5] + worldPos.z * m[6] + m[7];
            w = worldPos.x * m[12] + worldPos.y * m[13] + worldPos.z * m[14] + m[15];
        } else {
            x = worldPos.x * m[0] + worldPos.y * m[4] + worldPos.z * m[8] + m[12];
            y = worldPos.x * m[1] + worldPos.y * m[5] + worldPos.z * m[9] + m[13];
        }

        result.depth = w;
        if (w < 0.01f) return result;

        float invW = 1.0f / w;
        float nx = x * invW;
        float ny = y * invW;

        // Map to screen pixels
        result.x = (m_screenWidth / 2.0f) + (nx * m_screenWidth / 2.0f);
        result.y = (m_screenHeight / 2.0f) - (ny * m_screenHeight / 2.0f);

        if (result.x >= 0.0f && result.x <= m_screenWidth &&
            result.y >= 0.0f && result.y <= m_screenHeight) {
            result.valid = true;
        }

        return result;
    }

    ScreenPoint calculateFoot(const Vector3& worldPos) {
        return calculate(worldPos);
    }

    ScreenPoint calculateHead(const Vector3& footPos, float height = 72.0f) {
        Vector3 headPos = footPos;
        headPos.z += height;
        return calculate(headPos);
    }

private:
    Matrix4x4 m_viewMatrix;
    float m_screenWidth = 1920.0f;
    float m_screenHeight = 1080.0f;
};

} // namespace math
} // namespace csbox
