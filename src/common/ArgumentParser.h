//
// Created by kali on 4/6/26.
//

#ifndef CSBOX_ARGUMENTPARSER_H
#define CSBOX_ARGUMENTPARSER_H
#include "Config.h"
#include <sstream>
#include <string>
#include <iostream>
#include <windows.h>

namespace csbox {
    namespace common {
        class ArgumentParser {
        public:
            static AppConfig parse(int argc, char* argv[]) {
                AppConfig config;
                for (int i = 1; i < argc; ++i) {
                    std::string arg = argv[i];
                    if (arg == "--no-anti-screenshot") config.enableAntiScreenshot = false;
                    else if (arg == "-h" || arg == "--help") {
                        config.showHelp = true;
                        break;
                    }
                    else {
                        // 边界检查：发现了既不是 help 也不是功能开关的未知参数//
                        std::string errorMsg = "错误: 未知参数 '" + arg + "'\n\n点击确定查看可用选项。";
                        // 注意这里是 4 个参数：HWND, Text, Caption, Type
                        MessageBoxA(NULL, errorMsg.c_str(), "CSBox Error", MB_OK | MB_ICONERROR);
                        config.showHelp = true;
                        break;
                    }
                }
                return config;
            }

            static void showUsage() {
                std::stringstream ss;
                ss << "Usage: csbox.exe [options]\n\n"
                          << "Options:\n"
                          << "  -h, --help              Show this help message\n"
                          << "  --no-anti-screenshot    Disable anti-screenshot protection (Allow Sunshine/OBS capture)\n\n"
                          << "Note:\n"
                          << "  By default, WDA_EXCLUDEFROMCAPTURE is enabled for privacy and security.\n";
                // 通过 .str() 拿到最终的字符串
                std::string usageText = ss.str();
                MessageBoxA(NULL, usageText.c_str(), "CSBox Help", MB_OK | MB_ICONINFORMATION);
            }
        };
    }
}

#endif //CSBOX_ARGUMENTPARSER_H
