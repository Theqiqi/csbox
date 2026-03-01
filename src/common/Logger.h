#pragma once

#include <cstdarg>
#include <cstdio>
#include <ctime>

namespace csbox {
namespace common {

enum class LogLevel { Debug, Info, Warning, Error };

inline const char* logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Debug:   return "DEBUG";
        case LogLevel::Info:    return "INFO";
        case LogLevel::Warning: return "WARN";
        case LogLevel::Error:   return "ERROR";
        default:                return "UNKNOWN";
    }
}

inline void log(LogLevel level, const char* format, ...) {
    char buffer[1024];
    
    time_t now = time(nullptr);
    tm localTime;
    localtime_s(&localTime, &now);
    char timeStr[32];
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &localTime);
    
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    printf("[%s] [%s] %s\n", timeStr, logLevelToString(level), buffer);
    fflush(stdout);
}

} // namespace common
} // namespace csbox

#define LOGD(fmt, ...) csbox::common::log(csbox::common::LogLevel::Debug, "[%s:%d] " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGI(fmt, ...) csbox::common::log(csbox::common::LogLevel::Info, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) csbox::common::log(csbox::common::LogLevel::Warning, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) csbox::common::log(csbox::common::LogLevel::Error, fmt, ##__VA_ARGS__)
