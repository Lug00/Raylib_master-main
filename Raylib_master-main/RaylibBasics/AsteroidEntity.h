#pragma once
#include "Bodies.h"
#include "PhysicsEntity.h"

class AsteroidEntity : public PBox
{
public:
    AsteroidEntity(std::string name, std::string tag, b2BodyId id, Vector2 size, bool isDynamic)
        : PBox(name, tag, id, size, isDynamic) {
    }
};