#include "Healthbar.h"


void Healthbar::drawHealthbar(const int health, GameSpace::Surface* screen)
{
	float drawLocfx = screen->GetWidth() * 0.75f, drawLocfy = screen->GetHeight() * 0.88f;
	background.Draw(screen, (int)drawLocfx, (int)drawLocfy);
	GameSpace::Pixel* src = bar.GetBuffer() + 14 * bar.GetWidth();
	GameSpace::Pixel* dst = screen->GetBuffer() + (int)drawLocfx + 42 + ((int)drawLocfy + 14) * screen->GetPitch();
	float barSpace = (float)health / 100.0f;
	for (int i = 0; i < bar.GetHeight() - 14; i++, src += bar.GetWidth(), dst += screen->GetPitch())
	{
		for (int j = 0; j < barSpace * bar.GetWidth(); j++)
		{
			if (src[j] != 0)
				dst[j] = src[j];
		}
	}
}
