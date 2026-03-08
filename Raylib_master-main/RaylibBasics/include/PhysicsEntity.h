#pragma once
#include "Entity.h"
#include "box2d/box2d.h"

class PhysicsEntity;

struct Collision {
    PhysicsEntity* self;
    PhysicsEntity* other;
    float force;
	bool collected = false; // Para evitar procesar la misma colisión varias veces
};

class PhysicsEntity : public Entity {
public:

    b2BodyId body;
    Color color;

public:

    PhysicsEntity(std::string n, std::string t, b2BodyId id, bool isDynamic)
        : Entity(n, t), body(id)
    {
        color = isDynamic ? RED : GREEN;
        updatePhysics();
    }

    virtual ~PhysicsEntity() override
    {
        if (b2Body_IsValid(body))
        {
            b2DestroyBody(body);
            body = b2_nullBodyId;
        }
    }

    // --- UPDATE GENERAL ---
    void update() override
    {
        updatePhysics();
    }

    // --- SINCRONIZAR BOX2D → ENTITY ---
    void updatePhysics()
    {
        if (!b2Body_IsValid(body)) return;

        b2Vec2 b2p = b2Body_GetPosition(body);
        pos = { b2p.x, b2p.y };

        b2Rot b2r = b2Body_GetRotation(body);
        angle = b2Rot_GetAngle(b2r) * RAD2DEG;
    }

    // --- CAMBIAR TIPO DE CUERPO ---
    void setType(b2BodyType type)
    {
        if (!b2Body_IsValid(body)) return;

        b2Body_SetType(body, type);
        b2Body_SetAwake(body, true);
        b2Body_ApplyMassFromShapes(body);
    }

    // --- TELETRANSPORTE ---
    void setBodyPosition(Vector2 newPos)
    {
        if (!b2Body_IsValid(body)) return;

        b2Body_SetTransform(body, { newPos.x, newPos.y }, b2Rot_identity);
        b2Body_SetAwake(body, true);

        pos = newPos;
    }

    // --- VELOCIDAD ---
    void setVelocity(Vector2 vel)
    {
        if (!b2Body_IsValid(body)) return;

        b2Body_SetLinearVelocity(body, { vel.x, vel.y });
    }

    // --- IMPULSO ---
    void applyImpulse(Vector2 impulse)
    {
        if (!b2Body_IsValid(body)) return;

        b2Body_ApplyLinearImpulseToCenter(body, { impulse.x, impulse.y }, true);
    }

    // --- DESPERTAR CUERPO ---
    void setAwake(bool awake)
    {
        if (!b2Body_IsValid(body)) return;

        b2Body_SetAwake(body, awake);
    }

    // --- CALLBACK DE COLISIÓN ---
    virtual void onCollisionEnter(const Collision& collision) {}

};