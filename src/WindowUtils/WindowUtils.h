#pragma once

#include <cstdint>
#include <string>

namespace csbox {
namespace window {

struct ClientAreaInfo {
    int32_t x = 0;
    int32_t y = 0;
    int32_t width = 0;
    int32_t height = 0;
    bool isVisible = false;
};

class WindowUtils {
public:
    WindowUtils() = default;
    ~WindowUtils() = default;

    bool findWindow(const char* windowTitle, const char* className = "");
    ClientAreaInfo getClientInfo();
    void syncOverlayPosition(void* overlayHandle);

    void* getWindowHandle() const { return m_windowHandle; }
    void setWindowHandle(void* handle) { m_windowHandle = handle; }

private:
    void* m_windowHandle = nullptr;
    std::string m_windowTitle;
    std::string m_className;
};

} // namespace window
} // namespace csbox
