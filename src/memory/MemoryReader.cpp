#include "MemoryReader.h"
#include "../common/Logger.h"

namespace csbox {
namespace memory {

MemoryReader::MemoryReader(void* hProcess)
    : m_hProcess(hProcess) {}

bool MemoryReader::readViewMatrix(uintptr_t baseAddress, float matrix[16]) {
    if (!isValid()) {
        LOGE("MemoryReader is not valid");
        return false;
    }

    SIZE_T bytesRead = 0;
    BOOL result = ReadProcessMemory(
        static_cast<HANDLE>(m_hProcess),
        reinterpret_cast<LPCVOID>(baseAddress),
        matrix,
        sizeof(float) * 16,
        &bytesRead
    );

    if (!result || bytesRead != sizeof(float) * 16) {
        LOGE("Failed to read view matrix at 0x%016X, bytesRead=%lu", 
             baseAddress, static_cast<unsigned long>(bytesRead));
        return false;
    }

    LOGD("View matrix read successfully from 0x%016X", baseAddress);
    return true;
}

} // namespace memory
} // namespace csbox
