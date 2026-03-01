#pragma once

#include "Vector3.h"

namespace csbox {
namespace game {

enum class Team : int {
    None = 0,
    Terrorist = 1,
    CounterTerrorist = 2
};

struct Entity {
    int index = 0;
    math::Vector3 position;
    math::Vector3 headPosition;
    int health = 0;
    Team team = Team::None;
    bool isAlive = false;
    bool isValid = false;
};

struct LocalPlayer {
    math::Vector3 position;
    int health = 0;
    Team team = Team::None;
    bool isAlive = false;
};

struct EntityData {
    static constexpr int MAX_ENTITIES = 32;
    Entity entities[MAX_ENTITIES];
    int count = 0;
};

} // namespace game
} // namespace csbox
