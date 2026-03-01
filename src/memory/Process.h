#pragma once

#include <cstdint>
#include <unordered_map>
#include <string>

namespace csbox {
namespace memory {

class Process {
public:
    Process() = default;
    ~Process();

    bool findWindow(const char* className, const char* windowName);
    bool openProcess(uint32_t desiredAccess = 0x1F0FFF);  // PROCESS_ALL_ACCESS
    bool refreshModules();

    void close();
    bool isValid() const { return m_hProcess != nullptr; }

    void* getWindow() const { return m_hwnd; }
    void* getHandle() const { return m_hProcess; }
    uint32_t getProcessId() const { return m_pid; }
    uintptr_t getModuleBase(const char* moduleName) const;

private:
    void* m_hwnd = nullptr;
    void* m_hProcess = nullptr;
    uint32_t m_pid = 0;
    std::unordered_map<std::string, uintptr_t> m_modules;
};

} // namespace memory
} // namespace csbox
