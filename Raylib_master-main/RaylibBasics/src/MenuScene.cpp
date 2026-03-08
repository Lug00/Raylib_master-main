#include "MenuScene.h"
#include "PlayScene.h"
#include "SceneManager.h"
#include "raylib.h"

MenuScene& MenuScene::instance()
{
    static MenuScene instance;
    return instance;

    Rectangle startButton = { 540, 420, 200, 60 };

}

void MenuScene::load() 
{
    for (int i = 0; i < 120; i++)
    {
        stars.push_back({
            (float)GetRandomValue(0,GetScreenWidth()),
            (float)GetRandomValue(0,GetScreenHeight())
            });
    }
}
void MenuScene::unload() {}

void MenuScene::update()
{
    Vector2 mouse = GetMousePosition();


    if (CheckCollisionPointRec(mouse, startButton) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        SceneManager::instance().changeScene(&PlayScene::instance());
    }
}

void MenuScene::draw()
{
    DrawText("SPACE JUNK", 380, 100, 80, SKYBLUE);
    DrawText("COLLECTOR", 500, 170, 60, WHITE);

    DrawText("RECOLECTA LA BASURA", 420, 250, 30, GREEN);
    DrawText("EVITA LA BASURA TOXICA", 390, 290, 30, RED);

    DrawText("WASD PARA MOVERTE", 430, 340, 20, GRAY);


    DrawRectangleRec(startButton, DARKGREEN);
    DrawText("INICIAR", startButton.x + 40, startButton.y + 20, 25, WHITE);

    Vector2 mouse = GetMousePosition();

    Color btnColor = DARKGREEN;

    if (CheckCollisionPointRec(mouse, startButton))
    {
        btnColor = GREEN;
    }

    DrawRectangleRec(startButton, btnColor);
    DrawText("INICIAR", startButton.x + 40, startButton.y + 20, 30, WHITE);

    if (CheckCollisionPointRec(mouse, startButton) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        SceneManager::instance().changeScene(&PlayScene::instance());
    }

    for (auto& s : stars)
    {
        DrawCircleV(s, 2, WHITE);
    }
}