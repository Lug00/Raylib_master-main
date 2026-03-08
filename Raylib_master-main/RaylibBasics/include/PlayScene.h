#pragma once
#include "Scene.h"
#include "GUI.h"
#include "EventManager.h"

class PlayScene : public Scene
{
public:
    static PlayScene& instance();

    void load() override;
    void unload() override;
    void update() override;
    void draw() override;

    EventManager eventManager;

	GUI gui;

private:
    PlayScene() {} // Singleton

    // ===== ENTIDADES =====
    std::shared_ptr<PCircle> player;

    // ===== DEFINICIONES FÍSICAS =====
    BodyData playerDef;
    BodyData junkDef;
    BodyData asteroidDef;
    BodyData wallDef;

    // ===== SPAWN SYSTEM =====
    float spawnTimer = 0.0f;
    float spawnRate = 2.0f;

    // ===== GAME STATE =====
    int score = 0;
	int lives = 3;
    bool gameOver = false;
    //eventManager.subscribe<DamageEvent>(this, &PlayScene::onDamage);

    // ===== FUNCIONES INTERNAS =====
    void spawnJunk();
    void spawnAsteroid();
    void handlePlayerMovement();
    void onGameOver(const GameOverEvent& e);
};