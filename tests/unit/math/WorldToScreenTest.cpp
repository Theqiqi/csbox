#include <gtest/gtest.h>
#include "WorldToScreen.h"

using namespace csbox::math;

TEST(WorldToScreenTest, SetScreenSize) {
    WorldToScreen w2s;
    w2s.setScreenSize(1920, 1080);
    
    w2s.setViewMatrix(Matrix4x4::identity());
    w2s.setCameraPosition(Vector3(0, 0, 0));
    
    ScreenPoint result = w2s.calculate(Vector3(0, 0, 50));
    
    EXPECT_TRUE(result.valid);
}

TEST(WorldToScreenTest, BehindCamera) {
    WorldToScreen w2s;
    w2s.setScreenSize(1920, 1080);
    w2s.setViewMatrix(Matrix4x4::identity());
    w2s.setCameraPosition(Vector3(0, 0, 0));
    
    ScreenPoint result = w2s.calculate(Vector3(0, 0, -10));
    
    EXPECT_FALSE(result.valid);
}

TEST(WorldToScreenTest, CalculateFoot) {
    WorldToScreen w2s;
    w2s.setScreenSize(1920, 1080);
    w2s.setViewMatrix(Matrix4x4::identity());
    w2s.setCameraPosition(Vector3(0, 0, 0));
    
    Vector3 footPos(0, 0, 50);
    ScreenPoint result = w2s.calculateFoot(footPos);
    
    EXPECT_TRUE(result.valid);
}

TEST(WorldToScreenTest, CalculateHead) {
    WorldToScreen w2s;
    w2s.setScreenSize(1920, 1080);
    w2s.setViewMatrix(Matrix4x4::identity());
    w2s.setCameraPosition(Vector3(0, 0, 0));
    
    Vector3 footPos(0, 0, 0);
    ScreenPoint headResult = w2s.calculateHead(footPos, 60.0f);
    
    EXPECT_TRUE(headResult.valid);
}
