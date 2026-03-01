#include "WindowUtils.h"
#include "../common/Logger.h"
#include "../external/fix_win32_compatibility.h"
#include <windows.h>

namespace csbox {
namespace window {

bool WindowUtils::findWindow(const char* windowTitle, const char* className) {
    m_windowTitle = windowTitle;
    m_className = className;
    
    HWND hwnd = FindWindowA(className, windowTitle);
    if (!hwnd) {
        LOGE("FindWindow failed: title=%s, class=%s", windowTitle, className);
        return false;
    }
    
    m_windowHandle = hwnd;
    LOGD("Window found: HWND=%p", m_windowHandle);
    return true;
}

ClientAreaInfo WindowUtils::getClientInfo() {
    ClientAreaInfo info = {0, 0, 0, 0, false};
    
    if (!m_windowHandle) {
        return info;
    }
    
    HWND hwnd = static_cast<HWND>(m_windowHandle);
    
    if (!IsWindow(hwnd)) {
        return info;
    }
    
    bool isMinimized = IsIconic(hwnd);
    info.isVisible = !isMinimized;
    
    RECT cRect;
    GetClientRect(hwnd, &cRect);
    info.width = cRect.right - cRect.left;
    info.height = cRect.bottom - cRect.top;
    
    POINT pt = {0, 0};
    ClientToScreen(hwnd, &pt);
    info.x = pt.x;
    info.y = pt.y;
    
    return info;
}

void WindowUtils::syncOverlayPosition(void* overlayHandle) {
    if (!overlayHandle || !m_windowHandle) {
        return;
    }
    
    HWND myHwnd = static_cast<HWND>(overlayHandle);
    HWND gameHwnd = static_cast<HWND>(m_windowHandle);
    ClientAreaInfo info = getClientInfo();
    
    HWND foregroundHwnd = GetForegroundWindow();
    bool isForeground = (foregroundHwnd == gameHwnd || foregroundHwnd == myHwnd);
    
    if (info.width > 0 && info.isVisible && isForeground) {
        if (!IsWindowVisible(myHwnd)) {
            ShowWindow(myHwnd, SW_SHOWNOACTIVATE);
        }
        
        SetWindowPos(myHwnd, HWND_TOPMOST, info.x, info.y, info.width, info.height, SWP_NOACTIVATE);
    } else {
        if (IsWindowVisible(myHwnd)) {
            ShowWindow(myHwnd, SW_HIDE);
        }
    }
}

} // namespace window
} // namespace csbox
