#pragma once
#include "../surface.h"
#include "../template.h"
#include "newmath.h"
#include <iostream>

namespace UI
{

class Button
{
private:
	int start = 0, quit = 1, scores = 2, replay = 3;
	bool isPressed = false;
	int buttonType = -1;
	GameSpace::Sprite sprite{new GameSpace::Surface("assets/UI/play_full.png"), 2};
	GameSpace::Surface* screen;
	newmath::ivec2 size;
	GameSpace::vec2 drawLocf;

public:
	Button(const int type, GameSpace::Surface* screen, GameSpace::vec2 newDrawLocf)
	{
		this->screen = screen;
		buttonType = type;
		if (type == start)
		{
			sprite.SetFile("assets/UI/play_full.png", 2, 0);
			size = newmath::make_ivec2(sprite.GetSurface()->GetWidth() / 2, sprite.GetSurface()->GetHeight());
			if (!newDrawLocf.length())
			{
				drawLocf.x = (float)screen->GetWidth() / 11;
				drawLocf.y = (float)screen->GetHeight() / 2 -  2 * (float)screen->GetHeight() / 10 + (float)screen->GetHeight() / 7 - sprite.GetSurface()->GetHeight();
			}
			else drawLocf = newDrawLocf;
		}
		else if (type == quit)
		{
			sprite.SetFile("assets/UI/exit_full.png", 2, 0);
			size = newmath::make_ivec2(sprite.GetSurface()->GetWidth() / 2, sprite.GetSurface()->GetHeight());
			if (!newDrawLocf.length())
			{
				drawLocf.x = (float)screen->GetWidth() / 11;
				drawLocf.y = (float)screen->GetHeight() / 2 + (float)screen->GetHeight() / 7 - sprite.GetSurface()->GetHeight();
			}
			else drawLocf = newDrawLocf;
		}
		else if (type == replay)
		{
			sprite.SetFile("assets/UI/replay.png", 2, 0);
			size = newmath::make_ivec2(sprite.GetSurface()->GetWidth() / 2, sprite.GetSurface()->GetHeight());
			if (!newDrawLocf.length())
			{
				drawLocf.x = (float)screen->GetWidth() / 2 - (float)sprite.GetWidth() / 2;
				drawLocf.y = 4 * (float)screen->GetHeight() / 7;
			}
			else drawLocf = newDrawLocf;
		}
		else if (type == scores)
		{
			sprite.SetFile("assets/UI/scores.png", 2, 0);
			size = newmath::make_ivec2(sprite.GetSurface()->GetWidth() / 2, sprite.GetSurface()->GetHeight());
			if (!newDrawLocf.length())
			{
				drawLocf.x = (float)screen->GetWidth() / 11;
				drawLocf.y = (float)screen->GetHeight() / 2 + (float)screen->GetHeight() / 5 + (float)screen->GetHeight() / 7 - sprite.GetSurface()->GetHeight();
			}
			else drawLocf = newDrawLocf;
		}
	}

	bool isButtonPressed(GameSpace::vec2 mouse);
	bool getPressed() { return isPressed; };
	GameSpace::Sprite getSprite() { return sprite; };
	GameSpace::vec2 getLocation() { return drawLocf; };
	newmath::ivec2 getSize() { return size; };

	void setDrawLocation(GameSpace::vec2 newDrawLocf) { drawLocf = newDrawLocf; };
	
	void pressButton();
	void releaseButton();
	void drawButton();
	int getType() { return buttonType; };
};

}
