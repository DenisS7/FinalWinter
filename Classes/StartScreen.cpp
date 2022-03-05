#include "StartScreen.h"

namespace UI
{
	void StartScreen::displayScreen()
	{
		thumbnail.Draw(screen, 0, 0);
		title->Draw(screen, screen->GetWidth() / 50, screen->GetHeight() / 45);
		ScreenBase::displayScreen();
	}
}
