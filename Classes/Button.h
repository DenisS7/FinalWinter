#pragma once
#include "../surface.h"
#include "../template.h"
#include "newmath.h"

namespace UI
{

class Button
{
private:
	int start = 0, quit = 1, pause = 2;
	bool isPressed = false;
	GameSpace::Sprite sprite{new GameSpace::Surface("assets/UI/play_full.png"), 2};
	GameSpace::Surface* screen;
	newmath::ivec2 size;
	GameSpace::vec2 drawLocf;
public:
	Button(const int type, GameSpace::Surface* screen)
	{
		this->screen = screen;
		if (type == start)
		{
			sprite.SetFile( new GameSpace::Surface("assets/UI/play_full.png"), 2, 0);
			size = newmath::make_ivec2(sprite.GetSurface()->GetWidth() / 2, sprite.GetSurface()->GetHeight() / 2);
			drawLocf.x = (float)screen->GetWidth() / 15;
			drawLocf.y = (float)screen->GetHeight() / 2 - (float)screen->GetHeight() / 10;
		}
		else if (type == quit)
		{
			sprite.SetFile(new GameSpace::Surface("assets/UI/exit_full.png"), 2, 0);
			size = newmath::make_ivec2(sprite.GetSurface()->GetWidth() / 2, sprite.GetSurface()->GetHeight() / 2);
			drawLocf.x = (float)screen->GetWidth() / 15;
			drawLocf.y = (float)screen->GetHeight() / 2 + (float)screen->GetHeight() / 10;
		}
		else if (type == pause)
		{
			sprite.SetFile(new GameSpace::Surface("assets/UI/pause.png"), 2, 0);
			size = newmath::make_ivec2(sprite.GetSurface()->GetWidth() / 2, sprite.GetSurface()->GetHeight() / 2);
			drawLocf.x = (float)screen->GetWidth() / 15;
			drawLocf.y = (float)screen->GetHeight() / 2 + (float)screen->GetHeight() / 10;
		}
	}

	bool isButtonPressed(GameSpace::vec2 mouse);
	bool getPressed() { return isPressed; };
	void pressButton();
	void releaseButton();
	void drawButton();
};

}
