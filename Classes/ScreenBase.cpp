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

bool ScreenBase::getButtonStatus(int buttonType)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->getType() == buttonType)
			return buttons[i]->getPressed();
	}
	return false;
}

int ScreenBase::isButtonPressed(bool down, GameSpace::vec2 mouse)
{
	//std::cout << "Size: " << buttons.size() << std::endl;
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->isButtonPressed(mouse))
		{
			if (!buttons[i]->getPressed() && down)
			{
				buttons[i]->pressButton();
				return -1;
			}
			else if (buttons[i]->getPressed() && !down)
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