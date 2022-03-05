#pragma once
#include "../surface.h"
#include "Button.h"
#include <vector>

namespace UI
{
	
class ScreenBase
{
protected:
	const int start = 0, quit = 1, scores = 2, replay = 3;
	std::vector <Button*> buttons;
	GameSpace::Sprite* title;
	
public:
	int screenType = 0;
	ScreenBase(GameSpace::Surface* screen)
	{
		this->screen = screen;
		title = new GameSpace::Sprite{ new GameSpace::Surface("assets/Font/title.png"), 1 };
	}
	GameSpace::Surface* screen;
	
	virtual void displayScreen();
	int isButtonPressed(GameSpace::vec2 mouse);
};

}

