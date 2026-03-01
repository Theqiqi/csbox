#include <gtest/gtest.h>
#include "render/Renderer.h"

using namespace csbox::render;

TEST(RenderConfigTest, DefaultValues) {
    RenderConfig config;
    
    EXPECT_EQ(config.lineThickness, 1.5f);
    EXPECT_TRUE(config.showHealth);
    EXPECT_TRUE(config.showDistance);
}

TEST(ESPBoxTest, DefaultValues) {
    ESPBox box;
    
    EXPECT_FLOAT_EQ(box.x, 0.0f);
    EXPECT_FLOAT_EQ(box.y, 0.0f);
    EXPECT_FLOAT_EQ(box.width, 0.0f);
    EXPECT_FLOAT_EQ(box.height, 0.0f);
}

TEST(ESPBoxTest, Initialization) {
    ESPBox box{10.0f, 20.0f, 50.0f, 100.0f};
    
    EXPECT_FLOAT_EQ(box.x, 10.0f);
    EXPECT_FLOAT_EQ(box.y, 20.0f);
    EXPECT_FLOAT_EQ(box.width, 50.0f);
    EXPECT_FLOAT_EQ(box.height, 100.0f);
}
