#pragma once

namespace csbox {
    namespace common {
        struct AppConfig {
            bool enableAntiScreenshot = true;
            bool showHelp = false;
            // 以后扩展：std::string processName = "hl.exe";
        };
    }

}