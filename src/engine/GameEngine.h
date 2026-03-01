#pragma once

#include <memory>
#include <string>
#include "memory/Process.h"
#include "memory/MemoryReader.h"
#include "math/WorldToScreen.h"
#include "game/GameContext.h"
#include "render/Renderer.h"
#include "WindowUtils/WindowUtils.h"

namespace csbox {
namespace engine {

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    bool init();
    void run();
    void shutdown();

private:
    bool tryAttachProcess();
    bool updateMemory();
    void renderESP();
    void renderDebugOverlay();

private:
    std::unique_ptr<memory::Process> m_process;
    std::unique_ptr<memory::MemoryReader> m_reader;
    std::unique_ptr<render::Renderer> m_renderer;
    std::unique_ptr<window::WindowUtils> m_windowUtils;
    
    math::WorldToScreen m_w2s;
    game::GameContext m_ctx;
    
    uintptr_t m_hwBase = 0;
    int m_screenWidth = 1920;
    int m_screenHeight = 1080;
    bool m_isRunning = false;
};

} // namespace engine
} // namespace csbox
