#include "Healthbar.h"


void Healthbar::drawHealthbar(int health, GameSpace::Surface* screen)
{
	background.Draw(screen, 600, 450);
	GameSpace::Pixel* src = bar.GetBuffer() + 14 * bar.GetWidth();
	GameSpace::Pixel* dst = screen->GetBuffer() + 642 + 464 * screen->GetPitch();
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
