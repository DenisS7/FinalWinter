#pragma once
#include "../surface.h"
#include "Sprites.h"

class Score
{
private:
	GameSpace::Sprite scoreUI{ new GameSpace::Surface("assets/Font/font_score.png"), 1 };
public:
	void printScore(GameSpace::Surface* screen, int x, int y, int points);
};

