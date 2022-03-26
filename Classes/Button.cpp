#include "Button.h"


namespace UI
{
    bool Button::isButtonPressed(GameSpace::vec2 mouse)
    {
        if (mouse.x >= drawLocf.x && mouse.x <= drawLocf.x + size.x &&
            mouse.y >= drawLocf.y && mouse.y <= drawLocf.y + size.y)
            return true;
        return false;
    }

    void Button::pressButton()
    {
        isPressed = true;
        sprite->SetFrame(1);
    }


    void Button::releaseButton()
    {
        isPressed = false;
        sprite->SetFrame(0);
    }

    void Button::drawButton()
    {
        sprite->Draw(screen, static_cast<int>(drawLocf.x), static_cast<int>(drawLocf.y));
    }
}
