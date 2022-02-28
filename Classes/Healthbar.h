#pragma once
#include "../surface.h"

class Healthbar
{
private:
	GameSpace::Sprite background{ new GameSpace::Surface("assets/Healthbar/healthbar_background.png"), 1 };
	GameSpace::Sprite bar{ new GameSpace::Surface("assets/Healthbar/healthbar_bar.png"), 1 };
public:

	void drawHealthbar(const int health, GameSpace::Surface* screen);
};

