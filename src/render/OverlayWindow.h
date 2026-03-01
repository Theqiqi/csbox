#pragma once

#include <cstdint>

namespace csbox {
namespace render {

class OverlayWindow {
public:
    OverlayWindow();
    ~OverlayWindow();

    bool create(int screenWidth, int screenHeight);
    void destroy();

    void enableTransparent();
    void enableTopMost();
    void enableMousePassthrough();

    bool isValid() const { return m_window != 0; }

private:
    void* m_window = nullptr;
};

} // namespace render
} // namespace csbox
