#include "PauseScreen.h"

namespace UI
{
    void PauseScreen::displayScreen()
    {
        pause.Draw(screen, screen->GetPitch() / 2 - pause.GetSurface()->GetPitch() / 2, screen->GetHeight() / 5);
        ScreenBase::displayScreen();
    }
}
