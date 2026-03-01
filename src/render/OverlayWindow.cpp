#include "OverlayWindow.h"
#include "../common/Logger.h"
#include <windows.h>

namespace csbox {
namespace render {

OverlayWindow::OverlayWindow()
    : m_window(nullptr) {}

OverlayWindow::~OverlayWindow() {
    destroy();
}

bool OverlayWindow::create(int screenWidth, int screenHeight) {
    (void)screenWidth;
    (void)screenHeight;
    
    if (m_window != nullptr) {
        LOGW("OverlayWindow already created");
        return true;
    }

    HWND hwnd = GetForegroundWindow();
    if (hwnd == nullptr) {
        LOGE("Failed to get window handle");
        return false;
    }

    m_window = hwnd;
    LOGI("OverlayWindow created: HWND=%p", m_window);
    return true;
}

void OverlayWindow::destroy() {
    if (m_window != nullptr) {
        m_window = nullptr;
        LOGI("OverlayWindow destroyed");
    }
}

void OverlayWindow::enableTransparent() {
    if (m_window == nullptr) {
        LOGW("Window not created, cannot enable transparent");
        return;
    }

    HWND hwnd = static_cast<HWND>(m_window);

    SetWindowLongPtr(
        hwnd,
        GWL_EXSTYLE,
        GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED
    );

    SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);

    LOGD("Transparent enabled");
}

void OverlayWindow::enableTopMost() {
    if (m_window == nullptr) {
        LOGW("Window not created, cannot enable topmost");
        return;
    }

    HWND hwnd = static_cast<HWND>(m_window);

    SetWindowPos(
        hwnd,
        HWND_TOPMOST,
        0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE
    );

    LOGD("Topmost enabled");
}

void OverlayWindow::enableMousePassthrough() {
    if (m_window == nullptr) {
        LOGW("Window not created, cannot enable mouse passthrough");
        return;
    }

    HWND hwnd = static_cast<HWND>(m_window);

    SetWindowLongPtr(
        hwnd,
        GWL_EXSTYLE,
        GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_TRANSPARENT
    );

    LOGD("Mouse passthrough enabled");
}

} // namespace render
} // namespace csbox
