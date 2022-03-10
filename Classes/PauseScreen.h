#pragma once
#include "ScreenBase.h"

namespace UI
{

class PauseScreen :
    public ScreenBase
{
private:
    GameSpace::Sprite pause{ new GameSpace::Surface("assets/Font/paused.png"), 1 };
public:
    PauseScreen(GameSpace::Surface* screen) :
        ScreenBase(screen)
    {
        buttons.push_back(new Button(replay, screen, 0));
        buttons.push_back(new Button(path, screen, 0));
        buttons.push_back(new Button(quit, screen, 0));

        screenType = 2;
        GameSpace::vec2 pos((float)screen->GetPitch() / 2 - buttons[1]->getSize().x / 2, 3 * (float)screen->GetHeight() / 5);
        buttons[1]->setDrawLocation(pos);      

        pos = GameSpace::vec2((float)screen->GetPitch() / 2 - buttons[1]->getSize().x / 2, 4 * (float)screen->GetHeight() / 5);
        buttons[2]->setDrawLocation(pos);
    }

    void displayScreen() override;

};

}

