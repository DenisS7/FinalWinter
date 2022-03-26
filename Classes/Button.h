#pragma once
#include "../surface.h"
#include "../template.h"
#include "newmath.h"
#include "Sprites.h"


namespace UI
{
    class Button
    {
    private:
        const int start = 0, quit = 1, replay = 2, scores = 3, path = 4, back = 5;
        bool isPressed = false;
        int buttonType = -1;
        GameSpace::Sprite* sprite = new GameSpace::Sprite();
        GameSpace::Surface* screen;
        newmath::ivec2 size;
        GameSpace::vec2 drawLocf;

    public:
        Button(const int type, GameSpace::Surface* screen, GameSpace::vec2 newDrawLocf)
        {
            this->screen = screen;
            buttonType = type;
            if (type == start)
            {
                *sprite = *Sprites::get().button[start];
                size = newmath::make_ivec2(sprite->GetSurface()->GetWidth() / 2, sprite->GetSurface()->GetHeight());
                if (!newDrawLocf.length())
                {
                    drawLocf.x = static_cast<float>(screen->GetWidth()) / 11;
                    drawLocf.y = static_cast<float>(screen->GetHeight()) / 2 - 2 * static_cast<float>(screen->
                            GetHeight()) / 10 + static_cast<float>(screen->GetHeight()) / 7 - sprite->GetSurface()->
                        GetHeight();
                }
                else drawLocf = newDrawLocf;
            }
            else if (type == quit)
            {
                *sprite = *Sprites::get().button[quit];
                size = newmath::make_ivec2(sprite->GetSurface()->GetWidth() / 2, sprite->GetSurface()->GetHeight());
                if (!newDrawLocf.length())
                {
                    drawLocf.x = static_cast<float>(screen->GetWidth()) / 11;
                    drawLocf.y = static_cast<float>(screen->GetHeight()) / 2 + static_cast<float>(screen->GetHeight()) /
                        5 + static_cast<float>(screen->GetHeight()) / 7 - sprite->GetSurface()->GetHeight();
                }
                else drawLocf = newDrawLocf;
            }
            else if (type == replay)
            {
                *sprite = *Sprites::get().button[replay];
                size = newmath::make_ivec2(sprite->GetSurface()->GetWidth() / 2, sprite->GetSurface()->GetHeight());
                if (!newDrawLocf.length())
                {
                    drawLocf.x = static_cast<float>(screen->GetWidth()) / 2 - static_cast<float>(sprite->GetWidth()) /
                        2;
                    drawLocf.y = 2 * static_cast<float>(screen->GetHeight()) / 5;
                }
                else drawLocf = newDrawLocf;
            }
            else if (type == scores)
            {
                *sprite = *Sprites::get().button[scores];
                size = newmath::make_ivec2(sprite->GetSurface()->GetWidth() / 2, sprite->GetSurface()->GetHeight());
                if (!newDrawLocf.length())
                {
                    drawLocf.x = static_cast<float>(screen->GetWidth()) / 11;
                    drawLocf.y = static_cast<float>(screen->GetHeight()) / 2 + static_cast<float>(screen->GetHeight()) /
                        7 - sprite->GetSurface()->GetHeight();
                }
                else drawLocf = newDrawLocf;
            }
            else if (type == path)
            {
                *sprite = *Sprites::get().button[path];
                size = newmath::make_ivec2(sprite->GetSurface()->GetWidth() / 2, sprite->GetSurface()->GetHeight());
                if (!newDrawLocf.length())
                {
                    drawLocf.x = static_cast<float>(screen->GetWidth()) / 11;
                    drawLocf.y = static_cast<float>(screen->GetHeight()) / 2 + static_cast<float>(screen->GetHeight()) /
                        5 + static_cast<float>(screen->GetHeight()) / 7 - sprite->GetSurface()->GetHeight();
                }
                else drawLocf = newDrawLocf;
            }
            else if (type == back)
            {
                *sprite = *Sprites::get().button[back];
                size = newmath::make_ivec2(sprite->GetSurface()->GetWidth() / 2, sprite->GetSurface()->GetHeight());
                if (!newDrawLocf.length())
                {
                    drawLocf.x = static_cast<float>(screen->GetWidth()) / 40;
                    drawLocf.y = static_cast<float>(screen->GetHeight()) / 40;
                }
                else drawLocf = newDrawLocf;
            }
        }

        bool isButtonPressed(GameSpace::vec2 mouse);
        bool getPressed() { return isPressed; };
        GameSpace::Sprite* getSprite() { return sprite; };
        GameSpace::vec2 getLocation() { return drawLocf; };
        newmath::ivec2 getSize() { return size; };

        void setDrawLocation(GameSpace::vec2 newDrawLocf) { drawLocf = newDrawLocf; };

        void pressButton();
        void releaseButton();
        void drawButton();
        int getType() { return buttonType; };
    };
}
