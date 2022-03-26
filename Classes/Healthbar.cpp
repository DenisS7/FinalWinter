#include "Healthbar.h"


void Healthbar::drawHealthbar(const int health, GameSpace::Surface* screen)
{
    float drawLocfx = screen->GetWidth() * 0.75f, drawLocfy = screen->GetHeight() * 0.88f;
    background.Draw(screen, static_cast<int>(drawLocfx), static_cast<int>(drawLocfy));
    GameSpace::Pixel* src = bar.GetBuffer() + 14 * bar.GetWidth();
    GameSpace::Pixel* dst = screen->GetBuffer() + static_cast<int>(drawLocfx) + 42 + (static_cast<int>(drawLocfy) + 14) * screen->GetPitch();
    float barSpace = static_cast<float>(health) / 100.0f;
    for (int i = 0; i < bar.GetHeight() - 14; i++, src += bar.GetWidth(), dst += screen->GetPitch())
    {
        for (int j = 0; j < barSpace * bar.GetWidth(); j++)
        {
            if (src[j] != 0)
                dst[j] = src[j];
        }
    }
}
