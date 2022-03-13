#pragma once
#include "ScreenBase.h"
#include "PrintNumber.h"
#include "ScoreManager.h"

namespace UI
{

class ScoreScreen :
    public ScreenBase
{
private:
    GameSpace::Sprite topScores{ new GameSpace::Surface("assets/Font/top_scores.png"), 1 };
    ScoreManager* scoreManager;
public:
    ScoreScreen(GameSpace::Surface* screen, ScoreManager* newScoreManager) :
        ScreenBase(screen)
    {
        buttons.push_back(new Button(back, screen, 0));
        scoreManager = newScoreManager;
        screenType = 4;
    }
    void displayScreen() override;
};

}