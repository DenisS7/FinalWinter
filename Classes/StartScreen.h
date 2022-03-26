#pragma once
#include "ScreenBase.h"
#include "../surface.h"

namespace UI
{
    class StartScreen :
        public ScreenBase
    {
    private:
        GameSpace::Sprite thumbnail{new GameSpace::Surface("assets/Thumbnail/thumbnail-800.png"), 1};
    public:
        StartScreen(GameSpace::Surface* screen)
            : ScreenBase(screen)
        {
            screenType = 1;
            buttons.push_back(new Button(start, screen, 0));
            buttons.push_back(new Button(scores, screen, 0));
            buttons.push_back(new Button(quit, screen, 0));
        }

        void displayScreen() override;
    };
}
