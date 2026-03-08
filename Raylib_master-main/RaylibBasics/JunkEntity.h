#pragma once
#include "Bodies.h"
#include "PhysicsEntity.h"

class JunkEntity : public PCircle
{
public:
    JunkEntity(std::string name, std::string tag, b2BodyId id, float radius, bool isDynamic)
        : PCircle(name, tag, id, radius, isDynamic) {
    }
};