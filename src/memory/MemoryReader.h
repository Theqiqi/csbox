#pragma once

#include <vector>
#include <cstdint>
#include "../external/fix_win32_compatibility.h"
#include <windows.h>

namespace csbox {
namespace memory {

class MemoryReader {
public:
    explicit MemoryReader(void* hProcess);

    template<typename T>
    bool read(uintptr_t address, T& outValue) {
        if (!m_hProcess) return false;
        
        SIZE_T bytesRead = 0;
        BOOL result = ReadProcessMemory(
            static_cast<HANDLE>(m_hProcess),
            reinterpret_cast<LPCVOID>(address),
            &outValue,
            sizeof(T),
            &bytesRead
        );
        return (result != 0) && (bytesRead == sizeof(T));
    }

    template<typename T>
    bool readMultiLevel(uintptr_t base, const std::vector<uintptr_t>& offsets, T& outValue) {
        if (!m_hProcess) return false;
        
        uintptr_t current = base;
        for (size_t i = 0; i < offsets.size(); ++i) {
            uintptr_t next = 0;
            if (!read(current, next)) return false;
            current = next + offsets[i];
        }
        
        return read(current, outValue);
    }

    bool readViewMatrix(uintptr_t baseAddress, float matrix[16]);

    bool readBytes(uintptr_t address, void* buffer, size_t size) {
        if (!m_hProcess) return false;
        
        SIZE_T bytesRead = 0;
        return ReadProcessMemory(
            static_cast<HANDLE>(m_hProcess),
            reinterpret_cast<LPCVOID>(address),
            buffer,
            size,
            &bytesRead
        ) != 0 && bytesRead == size;
    }

    bool isValid() const { return m_hProcess != nullptr; }

private:
    void* m_hProcess = nullptr;
};

} // namespace memory
} // namespace csbox
