#pragma once

#include <cstdint>
#include "Entity.h"

namespace csbox {
namespace render {

struct ESPBox {
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
};

struct Color {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255;
};

struct RenderConfig {
    Color enemyColor = {255, 0, 0, 255};
    Color teammateColor = {0, 255, 0, 255};
    float lineThickness = 1.5f;
    bool showHealth = true;
    bool showDistance = true;
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(int screenWidth, int screenHeight);
    void shutdown();

    void beginFrame();
    void endFrame();

    void drawESPBox(const ESPBox& box, const Color& color, float thickness);
    void drawHealthBar(const ESPBox& box, int health);
    void drawText(const char* text, float x, float y, int fontSize, const Color& color);
    void drawDistance(float x, float y, float distance);

    void setConfig(const RenderConfig& config);
    const RenderConfig& getConfig() const { return m_config; }

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

private:
    RenderConfig m_config;
    int m_width = 0;
    int m_height = 0;
    bool m_initialized = false;
};

} // namespace render
} // namespace csbox
