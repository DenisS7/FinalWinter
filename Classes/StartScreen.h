#pragma once
#include "../surface.h"
#include "Button.h"
#include <vector>

class StartScreen
{
private:
	const int start = 0, quit = 1, pause = 2;
public:

	StartScreen(GameSpace::Surface* screen)
	{
		this->screen = screen;
		startButton = new UI::Button(start, screen);
		quitButton = new UI::Button(quit, screen);
		buttons.push_back(startButton);
		buttons.push_back(quitButton);
		thumbnail = new GameSpace::Sprite{ new GameSpace::Surface("assets/Thumbnail/thumbnailUP.png", 800, 450), 1 };
	}
	GameSpace::Surface* screen;
	GameSpace::Sprite* thumbnail;
	UI::Button* startButton;
	UI::Button* quitButton;
	
	std::vector <UI::Button*> buttons;
	void displayScreen();
	int isButtonPressed(GameSpace::vec2 mouse);
	void releaseButton();
};

