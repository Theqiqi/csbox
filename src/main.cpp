#include "engine/GameEngine.h"
#include "common/Logger.h"
#include <windows.h>

// 增加无控制台编译选项（Release 模式下生效）
#ifdef NDEBUG
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main() {
    // 强制声明 DPI 感知，防止 Windows 自动缩放导致调整分辨率时 Overlay 坐标严重偏移
    SetProcessDPIAware();

    using namespace csbox;

    LOGI("CSBox 启动中...");

    engine::GameEngine engine;
    
    if (!engine.init()) {
        LOGE("引擎初始化失败");
        return -1;
    }

    LOGI("引擎运行中...");
    engine.run();

    LOGI("CSBox 退出");
    engine.shutdown();

    return 0;
}
