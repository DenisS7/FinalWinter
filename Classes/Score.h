#pragma once
#include "../surface.h"


class Score
{
private:
	GameSpace::Sprite scoreUI{ new GameSpace::Surface("assets/Font/font_score.png"), 1 };
	GameSpace::Sprite numbers{ new GameSpace::Surface("assets/Font/font_numbers.png"), 9 };
	GameSpace::Sprite number1{ new GameSpace::Surface("assets/Font/font_1.png"), 1 };
public:
	void pickNumber(int x);
	void printScore(GameSpace::Surface* screen, int x, int y, int points);
};

