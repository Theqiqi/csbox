#include <gtest/gtest.h>
#include "game/GameContext.h"

using namespace csbox::game;

TEST(GameContextTest, DefaultConstructor) {
    GameContext ctx;
    
    EXPECT_FALSE(ctx.isGameRunning);
    EXPECT_EQ(ctx.screenWidth, 0);
    EXPECT_EQ(ctx.screenHeight, 0);
    EXPECT_EQ(ctx.entities.count, 0);
}

TEST(GameContextTest, Initialize) {
    GameContext ctx;
    
    ctx.isGameRunning = true;
    ctx.screenWidth = 1920;
    ctx.screenHeight = 1080;
    
    EXPECT_TRUE(ctx.isGameRunning);
    EXPECT_EQ(ctx.screenWidth, 1920);
    EXPECT_EQ(ctx.screenHeight, 1080);
}
