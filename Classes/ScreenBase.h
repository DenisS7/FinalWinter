#pragma once
#include "../surface.h"
#include "Button.h"
#include <vector>

namespace UI
{
	
class ScreenBase
{
protected:
	const int start = 0, quit = 1, replay = 2, scores = 3, path = 4, back = 5;
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
	
	std::vector <Button*> getButtons() { return buttons; };

	virtual void displayScreen();
	bool getButtonStatus(int buttonType);
	int isButtonPressed(bool down, GameSpace::vec2 mouse);
};

}

