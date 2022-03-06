#include "Button.h"
#include <iostream>

namespace UI
{

bool Button::isButtonPressed(GameSpace::vec2 mouse)
{
	if (mouse.x >= drawLocf.x && mouse.x <= drawLocf.x + size.x &&
		mouse.y >= drawLocf.y && mouse.y <= drawLocf.y + size.y)
			return true;
	return false;
}

void Button::pressButton()
{
	isPressed = true;
	sprite.SetFrame(1);
}


void Button::releaseButton()
{
	isPressed = false;
	sprite.SetFrame(0);
}

void Button::drawButton()
{
	sprite.Draw(screen, (int)drawLocf.x, (int)drawLocf.y);
}

}
