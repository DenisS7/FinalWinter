#include "Score.h"
#include <vector>
#include <iostream>
#include "PrintNumber.h"


void Score::printScore(GameSpace::Surface* screen, int x, int y, int points)
{
	int aux = points, nrr = 0, nr1 = 0;
	if (!aux)
		nrr++;
	while (aux)
	{
		if (aux % 10 == 1)
			nr1++;
		else nrr++;
		aux /= 10;
	}
	x -= scoreUI.GetSurface()->GetPitch() + 10 + nr1 * number1.GetSurface()->GetPitch() + nrr * (numbers.GetSurface()->GetPitch() / numbers.Frames());
	scoreUI.Draw(screen, x, y);
	x += scoreUI.GetSurface()->GetPitch() + 10;
	PrintNumber::printNumber(screen, points, x, y);
	
}
