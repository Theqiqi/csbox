#include "Process.h"
#include "../common/Logger.h"
#include "../external/fix_win32_compatibility.h"
#include <windows.h>
#include <tlhelp32.h>

namespace csbox {
namespace memory {

Process::~Process() {
    close();
}

bool Process::findWindow(const char* className, const char* windowName) {
    m_hwnd = FindWindowA(className, windowName);
    if (m_hwnd == nullptr) {
        LOGE("FindWindow failed: class=%s, window=%s", className, windowName);
        return false;
    }
    LOGD("FindWindow success: HWND=%p", m_hwnd);
    return true;
}

bool Process::openProcess(uint32_t desiredAccess) {
    if (m_hwnd == nullptr) {
        LOGE("Window not found, cannot open process");
        return false;
    }

    HWND hwnd = static_cast<HWND>(m_hwnd);
    if (!GetWindowThreadProcessId(hwnd, reinterpret_cast<LPDWORD>(&m_pid))) {
        LOGE("GetWindowThreadProcessId failed");
        return false;
    }
    LOGD("PID: %u", m_pid);

    m_hProcess = OpenProcess(desiredAccess, FALSE, m_pid);
    if (m_hProcess == nullptr) {
        LOGE("OpenProcess failed: PID=%u, Error=%u", m_pid, GetLastError());
        return false;
    }
    LOGD("Process handle opened: %p", m_hProcess);
    return true;
}

bool Process::refreshModules() {
    if (m_hProcess == nullptr) {
        LOGE("Process not opened");
        return false;
    }

    m_modules.clear();

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, m_pid);
    if (snapshot == INVALID_HANDLE_VALUE) {
        LOGE("CreateToolhelp32Snapshot failed: Error=%u", GetLastError());
        return false;
    }

    MODULEENTRY32W me32;
    me32.dwSize = sizeof(MODULEENTRY32W);

    if (!Module32FirstW(snapshot, &me32)) {
        LOGE("Module32First failed: Error=%u", GetLastError());
        CloseHandle(snapshot);
        return false;
    }

    do {
        std::wstring name(me32.szModule);
        std::string moduleName(name.begin(), name.end());
        m_modules[moduleName] = reinterpret_cast<uintptr_t>(me32.modBaseAddr);
        LOGD("Module found: %s, Base: %p", moduleName.c_str(), me32.modBaseAddr);
    } while (Module32NextW(snapshot, &me32));

    CloseHandle(snapshot);
    return true;
}

void Process::close() {
    if (m_hProcess != nullptr) {
        CloseHandle(m_hProcess);
        m_hProcess = nullptr;
    }
    m_hwnd = nullptr;
    m_pid = 0;
    m_modules.clear();
}

uintptr_t Process::getModuleBase(const char* moduleName) const {
    auto it = m_modules.find(moduleName);
    if (it != m_modules.end()) {
        return it->second;
    }
    LOGW("Module not found: %s", moduleName);
    return 0;
}

} // namespace memory
} // namespace csbox
