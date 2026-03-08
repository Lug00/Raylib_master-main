#include "SceneManager.h"

SceneManager& SceneManager::instance()
{
    static SceneManager sm;
    return sm;
}

void SceneManager::changeScene(Scene* newScene)
{
    if (currentScene)
    {
        currentScene->unload();
        currentScene->clear();
    }

    currentScene = newScene;

    if (currentScene)
        currentScene->load();
}

void SceneManager::update()
{
    if (currentScene)
        currentScene->updateScene();
}

void SceneManager::draw()
{
    if (currentScene)
        currentScene->drawScene();
}