#include "EndScreen.h"

namespace UI
{
    void EndScreen::displayScreen(bool won)
    {
        if (won)
            gameWon.Draw(screen, screen->GetPitch() / 2 - gameWon.GetSurface()->GetPitch() / 2, screen->GetHeight() / 10);
        else
            gameOver.Draw(screen, screen->GetPitch() / 2 - gameOver.GetSurface()->GetPitch() / 2, screen->GetHeight() / 10);
        ScreenBase::displayScreen();
    }
}
