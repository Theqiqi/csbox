#include "external/fix_win32_compatibility.h"
#include <raylib.h>
#include "GameEngine.h"
#include "common/Logger.h"
#include "memory/AddressOffsets.h"

namespace csbox {
namespace engine {

GameEngine::GameEngine() {
    m_process = std::make_unique<memory::Process>();
    m_renderer = std::make_unique<render::Renderer>();
    m_windowUtils = std::make_unique<window::WindowUtils>();
}

GameEngine::~GameEngine() {
}

bool GameEngine::init() {
    LOGI("GameEngine 初始化 (Calibration Build)...");

    if (!m_process->findWindow("Valve001", "Counter-Strike")) {
        LOGE("未找到 CS1.6 窗口");
        return false;
    }

    if (!m_process->openProcess()) {
        LOGE("无法打开进程句柄");
        return false;
    }

    if (!m_process->refreshModules()) {
        LOGE("无法刷新模块基址");
        return false;
    }

    m_hwBase = m_process->getModuleBase("hw.dll");
    if (!m_hwBase) {
        LOGE("找不到 hw.dll");
        return false;
    }
    LOGI("hw.dll 基址: 0x%08X", m_hwBase);

    m_reader = std::make_unique<memory::MemoryReader>(static_cast<HANDLE>(m_process->getHandle()));

    window::ClientAreaInfo gameInfo;
    m_windowUtils->setWindowHandle(m_process->getWindow());
    gameInfo = m_windowUtils->getClientInfo();
    m_screenWidth = (gameInfo.width > 0) ? gameInfo.width : 800;
    m_screenHeight = (gameInfo.height > 0) ? gameInfo.height : 600;

    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_MOUSE_PASSTHROUGH);
    InitWindow(m_screenWidth, m_screenHeight, "CSBox Calibration Overlay");
    SetTargetFPS(60);

    HWND hwnd = (HWND)GetWindowHandle();
    SetWindowLongPtr(hwnd, GWL_EXSTYLE, GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA | LWA_COLORKEY);

    if (!m_renderer->init(m_screenWidth, m_screenHeight)) {
        LOGE("渲染器初始化失败");
        return false;
    }

    m_isRunning = true;
    LOGI("初始化完成，进入主循环。");
    return true;
}

void GameEngine::run() {
    while (!WindowShouldClose() && m_isRunning) {
        window::ClientAreaInfo gameInfo = m_windowUtils->getClientInfo();
        if (gameInfo.width > 0 && gameInfo.height > 0) {
            if (gameInfo.width != m_screenWidth || gameInfo.height != m_screenHeight) {
                SetWindowSize(gameInfo.width, gameInfo.height);
                m_screenWidth = gameInfo.width;
                m_screenHeight = gameInfo.height;
                m_w2s.setScreenSize((float)m_screenWidth, (float)m_screenHeight);
            }
            m_windowUtils->syncOverlayPosition(GetWindowHandle());
        }

        BeginDrawing();
        ClearBackground(::Color{0, 0, 0, 0});

        // 即使内存更新失败，也要运行绘制逻辑（准星等）
        updateMemory();
        renderESP();
        renderDebugOverlay();

        EndDrawing();
    }
}

bool GameEngine::updateMemory() {
    // 1. Matrix
    uintptr_t matrixAddress = m_hwBase + 0xE956A0;
    if (!m_reader->readViewMatrix(matrixAddress, m_ctx.viewMatrix.data())) return false;
    m_w2s.setViewMatrix(m_ctx.viewMatrix);

    // 2. Local Player
    uintptr_t playerBase = 0;
    if (!m_reader->read(m_hwBase + 0x7BBD9C, playerBase) || !playerBase) return false;

    // Doc says Y=88, X=8C, Z=90, but CS1.6 is actually X, Y, Z sequentially
    m_reader->read(playerBase + 0x88, m_ctx.localPlayer.position.x);
    m_reader->read(playerBase + 0x8C, m_ctx.localPlayer.position.y);
    m_reader->read(playerBase + 0x90, m_ctx.localPlayer.position.z);

    uintptr_t lpExtra = 0;
    if (m_reader->read(playerBase + 0x7C, lpExtra) && lpExtra != 0) {
        int team = 0;
        m_reader->read(lpExtra + 0x1C8, team);
        m_ctx.localPlayer.team = static_cast<game::Team>(team);
    }

    // 3. Entities
    for (int i = 0; i < game::EntityData::MAX_ENTITIES; ++i) {
        m_ctx.entities.entities[i].isValid = false;
    }

    int validCount = 0;
    for (int i = 1; i <= 32; ++i) {
        // CS1.6 中 cl_entity_t 大小是 0x324 (即 804 字节)。
        // 之前错误地使用了 0x648 作为步长，导致跳过了一半的实体并读到了不连续的数据。
        uintptr_t offset = i * 0x324;
        uintptr_t entityBase = playerBase + offset;
        
        uintptr_t extra = 0;
        if (!m_reader->read(entityBase + 0x7C, extra) || extra == 0) continue;

        int ammo = 0;
        if (!m_reader->read(extra + 0x6A0, ammo)) continue; 

        int targetIdx = validCount % game::EntityData::MAX_ENTITIES;
        game::Entity& entity = m_ctx.entities.entities[targetIdx];

        m_reader->read(entityBase + 0x88, entity.position.x);
        m_reader->read(entityBase + 0x8C, entity.position.y);
        m_reader->read(entityBase + 0x90, entity.position.z);

        uintptr_t h2 = 0;
        int health = 0;
        if (m_reader->read(extra + 4, h2) && h2 != 0) {
            m_reader->read(h2 + 0x160, health);
        }
        entity.health = health;

        int team = 0;
        m_reader->read(extra + 0x1C8, team);
        entity.team = static_cast<game::Team>(team);

        if (entity.health > 0) {
            entity.isValid = true;
            validCount++;
        }
    }
    m_ctx.entities.count = validCount;
    return true;
}

void GameEngine::renderESP() {
    for (int i = 0; i < game::EntityData::MAX_ENTITIES; ++i) {
        auto& entity = m_ctx.entities.entities[i];
        if (!entity.isValid) continue;

        if (entity.team != game::Team::None && entity.team == m_ctx.localPlayer.team) continue;
        
        // 如果距离太近（比如小于1单位），说明这是玩家自己，不要画
        if (m_ctx.localPlayer.position.distanceTo(entity.position) < 1.0f) continue;

        math::Vector3 footWorld = entity.position;
        footWorld.z -= 36.0f;
        math::Vector3 headWorld = entity.position;
        headWorld.z += 36.0f;

        auto foot = m_w2s.calculate(footWorld);
        auto head = m_w2s.calculate(headWorld);

        if (!foot.valid && !head.valid) continue;

        float h = fabsf(foot.y - head.y);
        if (h < 5.0f) continue;
        
        float w = h * 0.7f;
        float boxX = foot.x - w / 2.0f;
        float boxY = (head.y < foot.y) ? head.y : foot.y;
        
        m_renderer->drawESPBox({boxX, boxY, w, h}, render::Color{255, 0, 0, 255}, 1.5f);
        m_renderer->drawHealthBar({boxX, boxY, w, h}, entity.health);
        m_renderer->drawDistance(foot.x, foot.y + 2.0f, m_ctx.localPlayer.position.distanceTo(entity.position) * 0.0254f);
    }
}

void GameEngine::renderDebugOverlay() {
    char buf[128];
    snprintf(buf, sizeof(buf), "FPS: %d | Entities: %d | MyTeam: %d", GetFPS(), m_ctx.entities.count, (int)m_ctx.localPlayer.team);
    m_renderer->drawText(buf, 10, 10, 16, render::Color{255, 255, 0, 255});

    // 准星
    float cx = (float)m_screenWidth / 2.0f;
    float cy = (float)m_screenHeight / 2.0f;
    DrawLine((int)cx - 10, (int)cy, (int)cx + 10, (int)cy, GREEN);
    DrawLine((int)cx, (int)cy - 10, (int)cx, (int)cy + 10, GREEN);
}

void GameEngine::shutdown() {
    if (m_renderer) m_renderer->shutdown();
    ::CloseWindow();
}

} // namespace engine
} // namespace csbox
