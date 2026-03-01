#include <gtest/gtest.h>
#include "game/Entity.h"

using namespace csbox::game;

TEST(EntityTest, DefaultConstructor) {
    Entity e;
    EXPECT_EQ(e.index, 0);
    EXPECT_EQ(e.health, 0);
    EXPECT_EQ(e.team, Team::None);
    EXPECT_FALSE(e.isAlive);
    EXPECT_FALSE(e.isValid);
}

TEST(EntityTest, TeamEnum) {
    EXPECT_EQ(static_cast<int>(Team::None), 0);
    EXPECT_EQ(static_cast<int>(Team::Terrorist), 1);
    EXPECT_EQ(static_cast<int>(Team::CounterTerrorist), 2);
}

TEST(EntityTest, EntityDataMaxCount) {
    EntityData data;
    EXPECT_EQ(data.count, 0);
    EXPECT_EQ(EntityData::MAX_ENTITIES, 32);
}

TEST(LocalPlayerTest, DefaultConstructor) {
    LocalPlayer lp;
    EXPECT_EQ(lp.health, 0);
    EXPECT_EQ(lp.team, Team::None);
    EXPECT_FALSE(lp.isAlive);
}
