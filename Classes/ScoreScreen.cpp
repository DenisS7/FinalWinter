#include "ScoreScreen.h"

namespace UI
{
    void ScoreScreen::displayScreen()
    {
        screen->Clear(0xccffff);
        topScores.Draw(screen, screen->GetPitch() / 2 - topScores.GetSurface()->GetPitch() / 2, screen->GetHeight() / 40);
        int dotOffset = Sprites::get().number[2]->GetWidth() + 30;
        int xoffset = Sprites::get().number[0]->GetWidth() + dotOffset;

        for (int i = 0; i < 5; i++)
        {
            bool isScore = false;
            int score = 0;
            if (i < scoreManager->getScores().size())
            {
                isScore = true;
                score = scoreManager->getScores()[i];
            }
            PrintNumber::printNumber(screen, i + 1, screen->GetPitch() / 2 - xoffset, (i + 1) * screen->GetHeight() / 10 + topScores.GetHeight() + screen->GetHeight() / 40);
            Sprites::get().number[2]->Draw(screen, screen->GetPitch() / 2 - dotOffset, (i + 1) * screen->GetHeight() / 10 + topScores.GetHeight() + screen->GetHeight() / 40 + Sprites::get().number[0]->GetHeight() - Sprites::get().number[2]->GetHeight());
            if (isScore)
                PrintNumber::printNumber(screen, score, screen->GetPitch() / 2 + dotOffset - 45, (i + 1) * screen->GetHeight() / 10 + topScores.GetHeight() + screen->GetHeight() / 40);
            xoffset = Sprites::get().number[1]->GetWidth() + dotOffset;
        }
        ScreenBase::displayScreen();
    }
}
