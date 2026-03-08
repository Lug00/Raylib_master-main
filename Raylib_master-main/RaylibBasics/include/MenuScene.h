#pragma once
#include "Scene.h"
#include "EventManager.h"
#include <string>
#include "EventTypes.h"
#include "GUI.h"
#include <memory>
 


class MenuScene : public Scene
{
private:
    MenuScene() {}
public:
	
    static MenuScene& instance();
    
    Rectangle startButton = { 500,500,200,60 };
    std::vector<Vector2> stars;

    void load() override;
    void unload() override;

    void update() override;
    void draw() override;


private:
   GUI gui;
   std::shared_ptr<Texture2D> tex;
   std::shared_ptr<Music> bgMusic;
   std::shared_ptr<Font> font;
};