#include "GUI.h"
#include "Log.h"
#include "raylib.h"
#include "raygui.h"

GUI::GUI()
{
    EventManager::instance().subscribe<AddScoreEvent>(this, &GUI::onAddScore);
    EventManager::instance().subscribe<DamageEvent>(this, &GUI::onDamage);
}

void GUI::onAddScore(const AddScoreEvent& e)
{
    score += e.value;
}

void GUI::onDamage(const DamageEvent& e)
{
    lives -= e.value;
    if (lives <= 0)
    {
        GameOverEvent g;
        EventManager::instance().emit(g);
    }
}

void GUI::draw()
{
    DrawText(TextFormat("Score: %i", score), 20, 20, 30, WHITE);
    DrawText(TextFormat("Lives: %i", lives), 20, 60, 30, RED);
}

void GUI::onButtonClicked(const ClickButtonEvent& e)
{
    //Log::print("Play button clicked: " + e.buttonName);
    score++;
}
