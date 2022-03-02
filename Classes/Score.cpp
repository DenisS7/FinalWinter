#include "Score.h"
#include <vector>
#include <iostream>


void Score::printScore(GameSpace::Surface* screen, int x, int y, int points)
{
	std::vector <int> nr;
	int nr1 = 0, nrr = 0;
	if (!points)
		nr.push_back(0), nrr++;
	while (points)
	{
		if (points % 10 == 1)
			nr1++;
		else nrr++;
		nr.push_back(points % 10);
		points /= 10;
	}
	std::cout << x << " " << number1.GetSurface()->GetPitch() <<  " " << nrr << "\n";
	x -= scoreUI.GetSurface()->GetPitch() + 10 + nr1 * number1.GetSurface()->GetPitch() + nrr * (numbers.GetSurface()->GetPitch() / numbers.Frames());
	std::cout << x << "\n";
	scoreUI.Draw(screen, x, y);
	x += scoreUI.GetSurface()->GetPitch() + 10;
	std::cout << x << "\n";
	while (nr.size())
	{
		if (nr.back() == 1)
		{
			number1.Draw(screen, x, y);
			x += number1.GetSurface()->GetPitch();
		}
		else
		{
			if ( nr.back() == 0)
				numbers.SetFrame(0);
			else numbers.SetFrame(nr.back() - 1);
			numbers.Draw(screen, x, y);
			x += (numbers.GetSurface()->GetPitch()) / numbers.Frames();
		}
		std::cout << "WHILE " << x << std::endl;
		nr.pop_back();
	}
}
