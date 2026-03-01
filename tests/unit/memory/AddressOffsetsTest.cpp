#include <gtest/gtest.h>
#include "memory/AddressOffsets.h"

using namespace csbox::memory;

TEST(AddressOffsetsTest, PlayerBase) {
    EXPECT_EQ(AddressOffsets::OFFSET_PLAYER_BASE, 0x7BBD9C);
}

TEST(AddressOffsetsTest, PositionOffsets) {
    EXPECT_EQ(AddressOffsets::OFFSET_POS_X, 0x8C);
    EXPECT_EQ(AddressOffsets::OFFSET_POS_Y, 0x88);
    EXPECT_EQ(AddressOffsets::OFFSET_POS_Z, 0x90);
}

TEST(AddressOffsetsTest, EntityListOffsets) {
    EXPECT_EQ(AddressOffsets::OFFSET_ENTITY_LIST, 0x324);
    EXPECT_EQ(AddressOffsets::OFFSET_ENTITY_STRIDE, 0x648);
}

TEST(AddressOffsetsTest, HealthOffsets) {
    EXPECT_EQ(AddressOffsets::OFFSET_HEALTH_PTR, 0x7C);
    EXPECT_EQ(AddressOffsets::OFFSET_HEALTH_OFFSET, 0x4);
    EXPECT_EQ(AddressOffsets::OFFSET_HEALTH, 0x160);
}

TEST(AddressOffsetsTest, TeamOffsets) {
    EXPECT_EQ(AddressOffsets::OFFSET_TEAM_PTR, 0x7C);
    EXPECT_EQ(AddressOffsets::OFFSET_TEAM, 0x1C8);
}

TEST(AddressOffsetsTest, ViewMatrixOffset) {
    EXPECT_EQ(AddressOffsets::OFFSET_VIEW_MATRIX, 0xE956A0);
}
