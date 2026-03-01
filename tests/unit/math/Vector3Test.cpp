#include <gtest/gtest.h>
#include "Vector3.h"

using namespace csbox::math;

TEST(Vector3Test, DefaultConstructor) {
    Vector3 v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(Vector3Test, ParameterizedConstructor) {
    Vector3 v(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(Vector3Test, Addition) {
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2(4.0f, 5.0f, 6.0f);
    Vector3 result = v1 + v2;
    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 7.0f);
    EXPECT_FLOAT_EQ(result.z, 9.0f);
}

TEST(Vector3Test, Subtraction) {
    Vector3 v1(4.0f, 5.0f, 6.0f);
    Vector3 v2(1.0f, 2.0f, 3.0f);
    Vector3 result = v1 - v2;
    EXPECT_FLOAT_EQ(result.x, 3.0f);
    EXPECT_FLOAT_EQ(result.y, 3.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);
}

TEST(Vector3Test, ScalarMultiplication) {
    Vector3 v(1.0f, 2.0f, 3.0f);
    Vector3 result = v * 2.0f;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
}

TEST(Vector3Test, Length) {
    Vector3 v(3.0f, 4.0f, 0.0f);
    EXPECT_FLOAT_EQ(v.length(), 5.0f);
}

TEST(Vector3Test, DistanceTo) {
    Vector3 v1(0.0f, 0.0f, 0.0f);
    Vector3 v2(3.0f, 4.0f, 0.0f);
    EXPECT_FLOAT_EQ(v1.distanceTo(v2), 5.0f);
}

TEST(Vector3Test, Normalized) {
    Vector3 v(3.0f, 4.0f, 0.0f);
    Vector3 normalized = v.normalized();
    EXPECT_FLOAT_EQ(normalized.length(), 1.0f);
}
