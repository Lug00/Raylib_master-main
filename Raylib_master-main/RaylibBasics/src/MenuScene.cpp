#include "MenuScene.h"
#include "PlayScene.h"
#include "SceneManager.h"
#include "raylib.h"

MenuScene& MenuScene::instance()
{
    static MenuScene instance;
    return instance;
}

void MenuScene::load() {}
void MenuScene::unload() {}

void MenuScene::update()
{
    //Vector2 mouse = GetMousePosition();
    //
    //Rectangle startBtn = { 400,350,200,60 };
    //
    //if (CheckCollisionPointRec(mouse, startBtn) &&
    //    IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    //{
    //    SceneManager::instance().changeScene(&PlayScene::instance());
    //}
}

void MenuScene::draw()
{
    DrawText("SPACE JUNK COLLECTOR", 350, 120, 50, WHITE);

    DrawText("RECOLECTA LA BASURA", 420, 250, 30, GREEN);
    DrawText("EVITA LA BASURA TOXICA", 390, 290, 30, RED);

    DrawText("WASD PARA MOVERTE", 430, 340, 20, GRAY);

    Rectangle startButton = { 540, 420, 200, 60 };

    DrawRectangleRec(startButton, DARKGREEN);
    DrawText("INICIAR", 600, 440, 25, WHITE);

    Vector2 mouse = GetMousePosition();

    if (CheckCollisionPointRec(mouse, startButton) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        SceneManager::instance().changeScene(&PlayScene::instance());
    }
}