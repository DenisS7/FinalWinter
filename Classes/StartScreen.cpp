#include "StartScreen.h"
#include <iostream>
#include "FreeImage.h"


void StartScreen::displayScreen()
{
	//std::cout << thumbnail->GetSurface()->GetHeight() << std::endl;
	thumbnail->Draw(screen, 0, 0);
	startButton->drawButton();
	quitButton->drawButton();
}

int StartScreen::isButtonPressed(GameSpace::vec2 mouse)
{
	
	for (int i = 0; i < buttons.size(); i++)
	{
		std::cout << i << "\n";
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
				return i;
			}
		}
		else if (buttons[i]->getPressed())
		{
			buttons[i]->releaseButton();
			return false - 1;
		}
	}
	return -1;
}
