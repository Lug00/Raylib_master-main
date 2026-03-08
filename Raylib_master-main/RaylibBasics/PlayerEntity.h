#pragma once
#include "Bodies.h"
#include "PhysicsEntity.h"
#include "EventManager.h"
#include "EventTypes.h"

class PlayerEntity : public PCircle
{
public:
    PlayerEntity(std::string name, std::string tag, b2BodyId id, float radius, bool isDynamic)
        : PCircle(name, tag, id, radius, isDynamic) {
        //printf("Colision con %s\n", c.other->tag.c_str());
    }

    void onCollisionEnter(const Collision& collision) 
    {
        if (collision.other->tag == "Junk")
        {
            collision.other->destroy();

            AddScoreEvent e;
            EventManager::instance().emit(e);
        }

        if (collision.other->tag == "Asteroid")
        {
            GameOverEvent e;
            EventManager::instance().emit(e);
        }
    }
};