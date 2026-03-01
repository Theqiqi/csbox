#include <gtest/gtest.h>
#include "Matrix4x4.h"

using namespace csbox::math;

TEST(Matrix4x4Test, DefaultConstructor) {
    Matrix4x4 m;
    for (int i = 0; i < 16; ++i) {
        EXPECT_FLOAT_EQ(m.data()[i], 0.0f);
    }
}

TEST(Matrix4x4Test, Identity) {
    Matrix4x4 m = Matrix4x4::identity();
    
    EXPECT_FLOAT_EQ(m(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(m(1, 1), 1.0f);
    EXPECT_FLOAT_EQ(m(2, 2), 1.0f);
    EXPECT_FLOAT_EQ(m(3, 3), 1.0f);
    
    EXPECT_FLOAT_EQ(m(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(m(1, 2), 0.0f);
    EXPECT_FLOAT_EQ(m(2, 0), 0.0f);
}

TEST(Matrix4x4Test, Transform) {
    Matrix4x4 m = Matrix4x4::identity();
    Vector3 v(1.0f, 2.0f, 3.0f);
    Vector3 result = m.transform(v);
    
    EXPECT_FLOAT_EQ(result.x, 1.0f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);
}

TEST(Matrix4x4Test, TransformWithTranslation) {
    float data[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        5, 6, 7, 1
    };
    Matrix4x4 m(data);
    
    Vector3 v(1.0f, 2.0f, 3.0f);
    Vector3 result = m.transform(v);
    
    EXPECT_FLOAT_EQ(result.x, 6.0f);
    EXPECT_FLOAT_EQ(result.y, 8.0f);
    EXPECT_FLOAT_EQ(result.z, 10.0f);
}

TEST(Matrix4x4Test, ArrayConstructor) {
    float data[16];
    for (int i = 0; i < 16; ++i) {
        data[i] = static_cast<float>(i);
    }
    
    Matrix4x4 m(data);
    
    for (int i = 0; i < 16; ++i) {
        EXPECT_FLOAT_EQ(m.data()[i], static_cast<float>(i));
    }
}
