#include "engine/GameEngine.h"
#include "common/Logger.h"

int main() {
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
