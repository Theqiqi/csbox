#include "engine/GameEngine.h"
#include "common/Logger.h"
#include "common/Config.h"
#include "common/ArgumentParser.h"
#include <windows.h>

// 增加无控制台编译选项（Release 模式下生效）
#ifdef NDEBUG
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, char* argv[]) {
    // 1. 解析参数
    auto config = csbox::common::ArgumentParser::parse(argc, argv);

    // 2. 预处理逻辑（如显示帮助信息）
    if (config.showHelp) {
        csbox::common::ArgumentParser::showUsage(); // 调用这里的实现
        return 0;
    }
    // 强制声明 DPI 感知，防止 Windows 自动缩放导致调整分辨率时 Overlay 坐标严重偏移
    SetProcessDPIAware();

    LOGI("CSBox 启动中...");

    // 3. 注入配置并启动
    auto engine = std::make_unique<csbox::engine::GameEngine>();
    if (!engine->init(config)) { // 整个 config 对象传进去
        return -1;
    }

    LOGI("引擎运行中...");
    engine->run();

    LOGI("CSBox 退出");
    engine->shutdown();

    return 0;
}
