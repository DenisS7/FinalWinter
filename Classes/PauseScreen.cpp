#include "PauseScreen.h"

namespace UI
{
	
void PauseScreen::displayScreen()
{
	//setButtonLocation();
	//buttons[1]->setDrawLocation(GameSpace::vec2(screen->GetPitch() / 2, 100));
	pause.Draw(screen, screen->GetPitch() / 2 - pause.GetSurface()->GetPitch() / 2, screen->GetHeight() / 5);
	ScreenBase::displayScreen();
}

}
