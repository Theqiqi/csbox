#pragma once

#include <cstdint>

namespace csbox {
namespace memory {

struct AddressOffsets {
    // 人物对象基址（需先读取 hw.dll + 0x7BBD9C）
    static constexpr uintptr_t OFFSET_PLAYER_BASE = 0x7BBD9C;

    // 本地玩家/敌人 坐标偏移
    static constexpr uintptr_t OFFSET_POS_Y = 0x88;
    static constexpr uintptr_t OFFSET_POS_X = 0x8C;
    static constexpr uintptr_t OFFSET_POS_Z = 0x90;

    // 实体列表偏移
    static constexpr uintptr_t OFFSET_ENTITY_LIST = 0x324;
    static constexpr uintptr_t OFFSET_ENTITY_STRIDE = 0x648;

    // 血量（多级: +0x7C -> +0x4 -> +0x160）
    static constexpr uintptr_t OFFSET_HEALTH_PTR = 0x7C;
    static constexpr uintptr_t OFFSET_HEALTH_OFFSET = 0x4;
    static constexpr uintptr_t OFFSET_HEALTH = 0x160;

    // 阵营（多级: +0x7C -> +0x1C8）
    static constexpr uintptr_t OFFSET_TEAM_PTR = 0x7C;
    static constexpr uintptr_t OFFSET_TEAM = 0x1C8;

    // 视图矩阵（直接地址）
    static constexpr uintptr_t OFFSET_VIEW_MATRIX = 0xE956A0;
};

} // namespace memory
} // namespace csbox
