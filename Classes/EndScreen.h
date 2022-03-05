#pragma once
#include "ScreenBase.h"

namespace UI
{

class EndScreen :
    public ScreenBase
{
private:
    GameSpace::Sprite gameOver{ new GameSpace::Surface("assets/Font/game_over.png"), 1 };
    GameSpace::Sprite gameWon{ new GameSpace::Surface("assets/Font/won.png"), 1};
public:
    EndScreen(GameSpace::Surface* screen) :
        ScreenBase(screen)
    {
        screenType = 3;
        buttons.push_back(new Button(replay, screen, 0));
        buttons.push_back(new Button(scores, screen, 0));
        buttons.push_back(new Button(quit, screen, 0));

        GameSpace::vec2 pos((float)screen->GetPitch() / 2 - buttons[0]->getSize().x / 2, (float)screen->GetHeight() / 2 - buttons[0]->getSize().y);
        buttons[0]->setDrawLocation(pos);
        pos = GameSpace::vec2((float)screen->GetPitch() / 2 - buttons[1]->getSize().x / 2, (float)screen->GetHeight() / 2 + (float)screen->GetHeight() / 5 - buttons[1]->getSize().y);
        buttons[1]->setDrawLocation(pos);
        pos = GameSpace::vec2((float)screen->GetPitch() / 2 - buttons[1]->getSize().x / 2, (float)screen->GetHeight() / 2 + (float)2 * screen->GetHeight() / 5 - buttons[2]->getSize().y);
        buttons[2]->setDrawLocation(pos);
    }

    void displayScreen(bool won);
};

}

