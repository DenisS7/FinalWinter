#include "ScreenBase.h"
#include <iostream>
#include "FreeImage.h"

namespace UI
{
void ScreenBase::displayScreen()
{
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->drawButton();
}

int ScreenBase::isButtonPressed(GameSpace::vec2 mouse)
{

	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->isButtonPressed(mouse))
		{
			if (!buttons[i]->getPressed())
			{
				buttons[i]->pressButton();
				return -1;
			}
			else
			{
				buttons[i]->releaseButton();
				return buttons[i]->getType();
			}
		}
		else if (buttons[i]->getPressed())
		{
			buttons[i]->releaseButton();
			return -1;
		}
	}
	return -1;
}

}