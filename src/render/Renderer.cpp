#include "Renderer.h"
#include "../common/Logger.h"
#include <raylib.h>

namespace csbox {
namespace render {

namespace {
::Color toRaylibColor(const Color& c) {
    return {c.r, c.g, c.b, c.a};
}
}

Renderer::Renderer() 
    : m_initialized(false) {}

Renderer::~Renderer() {
    if (m_initialized) {
        shutdown();
    }
}

bool Renderer::init(int screenWidth, int screenHeight) {
    if (m_initialized) {
        LOGW("Renderer already initialized");
        return true;
    }

    m_width = screenWidth;
    m_height = screenHeight;

    m_config.enemyColor = {255, 0, 0, 255};
    m_config.teammateColor = {0, 255, 0, 255};
    m_config.lineThickness = 1.5f;
    m_config.showHealth = true;
    m_config.showDistance = true;

    m_initialized = true;
    LOGI("Renderer initialized: %dx%d", m_width, m_height);
    return true;
}

void Renderer::shutdown() {
    if (!m_initialized) {
        return;
    }

    m_initialized = false;
    LOGI("Renderer shutdown");
}

void Renderer::beginFrame() {
    ClearBackground(toRaylibColor(Color{0, 0, 0, 0}));
}

void Renderer::endFrame() {
}

void Renderer::drawESPBox(const ESPBox& box, const Color& color, float thickness) {
    if (!m_initialized) return;

    if (box.width < 1.0f || box.height < 1.0f) return;

    DrawRectangleLinesEx(
        Rectangle{ box.x, box.y, box.width, box.height },
        thickness,
        toRaylibColor(color)
    );
}

void Renderer::drawHealthBar(const ESPBox& box, int health) {
    if (!m_initialized) return;
    if (health <= 0) return;

    // 缩窄血量条，避免遮挡，增加一点间距
    float barWidth = 3.0f;
    float barHeight = box.height;
    float barX = box.x - barWidth - 6.0f;
    float barY = box.y;

    float healthRatio = static_cast<float>(health) / 100.0f;
    if (healthRatio > 1.0f) healthRatio = 1.0f;

    float fillHeight = barHeight * healthRatio;

    Color bgColor = {50, 50, 50, 180};
    DrawRectangle(barX, barY, barWidth, barHeight, toRaylibColor(bgColor));

    Color healthColor;
    if (healthRatio > 0.6f) {
        healthColor = {0, 255, 0, 255};
    } else if (healthRatio > 0.3f) {
        healthColor = {255, 255, 0, 255};
    } else {
        healthColor = {255, 0, 0, 255};
    }

    DrawRectangle(barX, barY + (barHeight - fillHeight), barWidth, fillHeight, toRaylibColor(healthColor));
    
    // 画一个细边框
    DrawRectangleLinesEx(Rectangle{barX - 1, barY - 1, barWidth + 2, barHeight + 2}, 1.0f, toRaylibColor(Color{0, 0, 0, 150}));
}

void Renderer::drawText(const char* text, float x, float y, int fontSize, const Color& color) {
    if (!m_initialized) return;
    if (!text) return;

    DrawText(text, static_cast<int>(x), static_cast<int>(y), fontSize, toRaylibColor(color));
}

void Renderer::drawDistance(float x, float y, float distance) {
    if (!m_initialized) return;

    char distText[32];
    snprintf(distText, sizeof(distText), "%.0fm", distance);

    DrawText(
        distText,
        static_cast<int>(x - MeasureText(distText, 10) / 2),
        static_cast<int>(y),
        10,
        toRaylibColor(Color{255, 255, 255, 255})
    );
}

void Renderer::setConfig(const RenderConfig& config) {
    m_config = config;
}

} // namespace render
} // namespace csbox
