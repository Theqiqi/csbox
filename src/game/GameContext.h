#pragma once

#include "math/Matrix4x4.h"
#include "math/Vector3.h"
#include "Entity.h"

namespace csbox {
namespace game {

struct GameContext {
    bool isGameRunning = false;

    LocalPlayer localPlayer;
    EntityData entities;

    math::Matrix4x4 viewMatrix;
    math::Vector3 cameraPosition;

    int screenWidth = 0;
    int screenHeight = 0;
};

} // namespace game
} // namespace csbox
