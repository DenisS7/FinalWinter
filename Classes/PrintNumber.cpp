#include "PrintNumber.h"
#include "Sprites.h"

void PrintNumber::printNumber(GameSpace::Surface* screen, int number, int x, int y)
{
    std::vector<int> nr;
    int nr1 = 0, nrr = 0;

    if (!number)
        nr.push_back(0), nrr++;
    while (number)
    {
        if (number % 10 == 1)
            nr1++;
        else nrr++;
        nr.push_back(number % 10);
        number /= 10;
    }

    while (nr.size())
    {
        if (nr.back() == 1)
        {
            Sprites::get().number[0]->Draw(screen, x, y);
            x += Sprites::get().number[0]->GetSurface()->GetPitch();
        }
        else
        {
            if (nr.back() == 0)
                Sprites::get().number[1]->SetFrame(0);
            else Sprites::get().number[1]->SetFrame(nr.back() - 1);
            Sprites::get().number[1]->Draw(screen, x, y);
            x += (Sprites::get().number[1]->GetSurface()->GetPitch()) / Sprites::get().number[1]->Frames();
        }
        nr.pop_back();
    }
}
