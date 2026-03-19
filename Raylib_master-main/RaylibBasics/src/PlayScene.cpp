#include "PlayScene.h"
#include "SceneManager.h"
#include "raylib.h"
#include "../PlayerEntity.h"
#include "math.h"

PlayScene& PlayScene::instance()
{
    static PlayScene instance;
    return instance;
}

void PlayScene::load()
{
    if (isLoaded) return;

    physics.reset();
    eventManager.subscribe<GameOverEvent>(this, &PlayScene::onGameOver);

    // ===== PLAYER =====
    playerDef.pos = { 0,0 };
    playerDef.radius = 1.0f;
    playerDef.isDynamic = true;
    playerDef.enableCollisions = true;
    playerDef.name = "Player";
    playerDef.tag = "Player";


    player = physics.makePlayer(playerDef);
    addEntity(player);

    // ===== JUNK =====
    junkDef.radius = 0.6f;
    junkDef.isDynamic = true;
    junkDef.name = "Junk";
    junkDef.tag = "Junk";
    junkDef.enableCollisions = true;



    // ===== ASTEROID =====
    asteroidDef.size = { 1.5f,1.5f };
    asteroidDef.isDynamic = true;
    asteroidDef.name = "Asteroid";
    asteroidDef.tag = "Asteroid";
    asteroidDef.enableCollisions = true;

    // ===== WALLS =====
    wallDef.isDynamic = false;
    wallDef.enableCollisions = false;

    // piso
    wallDef.size = { 50,1 };
    wallDef.pos = { 0,10 };
    addEntity(physics.makeBox(wallDef));

    // techo
    wallDef.pos = { 0,-10 };
    addEntity(physics.makeBox(wallDef));

    // izquierda
    wallDef.size = { 1,20 };
    wallDef.pos = { -20,0 };
    addEntity(physics.makeBox(wallDef));

    // derecha
    wallDef.pos = { 20,0 };
    addEntity(physics.makeBox(wallDef));

    score = 0;
    spawnTimer = 0;
    gameOver = false;

    isLoaded = true;
}

void PlayScene::unload()
{
}

void PlayScene::update()
{
    if (gameOver) return;

    handlePlayerMovement();

    // ===== SPAWN TIMER =====
    spawnTimer += GetFrameTime();

    if (spawnTimer > spawnRate)
    {
        spawnJunk();

        if (GetRandomValue(0, 3) == 0)
            spawnAsteroid();

        spawnTimer = 0;
    }

    // ===== CAMERA FOLLOW PLAYER =====
    cam.target = player->pos;
}

void PlayScene::draw()
{
    // Dibujos en coordenadas de pantalla (UI / texto / overlays).
    // Las entidades ya fueron dibujadas por Scene::drawScene() dentro de la cámara.
    gui.draw();

    DrawText(TextFormat("Score: %i", score), 20, 20, 30, WHITE);


    if (gameOver)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.7f));

        DrawText("GAME OVER", 400, 200, 60, RED);

        Rectangle button = { 400,300,200,60 };

        DrawRectangleRec(button, DARKGRAY);
        DrawText("RESTART", 430, 320, 20, WHITE);

        Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, button) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            SceneManager::instance().changeScene(&PlayScene::instance());
        }
    }
}

void PlayScene::handlePlayerMovement()
{
    if (!player) return;
    if (!b2Body_IsValid(player->body)) return;

    Vector2 vel = { 0,0 };

    float speed = 20.0f;

    if (IsKeyDown(KEY_W)) vel.y -= speed;
    if (IsKeyDown(KEY_S)) vel.y += speed;
    if (IsKeyDown(KEY_A)) vel.x -= speed;
    if (IsKeyDown(KEY_D)) vel.x += speed;

    b2Vec2 velocity = { vel.x, vel.y };

    b2Body_SetLinearVelocity(player->body, velocity);
}

void PlayScene::spawnJunk()
{
    BodyData data = junkDef;

    // Evitar warnings por conversión int -> float
    data.pos.x = static_cast<float>(GetRandomValue(-18, 18));
    data.pos.y = static_cast<float>(GetRandomValue(-8, 8));

    addEntity(physics.makeCircle(data));
}

void PlayScene::spawnAsteroid()
{
    BodyData data = asteroidDef;

    // Evitar warnings por conversión int -> float
    data.pos.x = static_cast<float>(GetRandomValue(-18, 18));
    data.pos.y = static_cast<float>(GetRandomValue(-8, 8));

    addEntity(physics.makeBox(data));
}

void PlayScene::onGameOver(const GameOverEvent& e)
{
    gameOver = true;
}

//void PlayScene::onDamage(const DamageEvent& e)
//{
//    lives--;
//
//    if (lives <= 0)
//    {
//        GameOverEvent e;
//        EventManager::instance().emit(e);
//    }
//}