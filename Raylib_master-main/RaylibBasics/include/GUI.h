#pragma once
#include "EventManager.h"
#include "EventTypes.h"



class GUI 
{
public:
	int score = 0;
	int lives = 3;

	void draw();
	GUI();

	void onDamage(const DamageEvent& e);
	void onButtonClicked(const ClickButtonEvent &e);
	void onAddScore(const AddScoreEvent& e);
};