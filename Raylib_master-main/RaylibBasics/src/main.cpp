#include "raylib.h"
#include "SceneManager.h"
#include "MenuScene.h"

int main()
{
    InitWindow(1280, 720, "Space Junk Collector");

    SetTargetFPS(120);

    // INICIAMOS EN EL MENU
    SceneManager::instance().changeScene(&MenuScene::instance());

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        SceneManager::instance().update();
        SceneManager::instance().draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}