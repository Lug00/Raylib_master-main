#pragma once
#include <string>
#include "Entity.h"

struct ClickButtonEvent {
    std::string buttonName = "my button";
};

struct CollisionEvent {
    Entity* a;
    Entity* b;
    float force;
};

struct AddScoreEvent
{
    int value = 1;
};

struct GameOverEvent
{
};

struct DamageEvent
{
    int value = 1;
};