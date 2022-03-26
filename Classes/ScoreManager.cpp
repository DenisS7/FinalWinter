#include "ScoreManager.h"


void ScoreManager::readScores()
{
    //when opening game reads scores from file
    int x = 0;
    std::ifstream fin("Scores/scores.txt");
    while (fin >> x && scores.size() < 6)
        scores.push_back(x);
    fin.close();
}

void ScoreManager::checkScore(int newScore)
{
    //maximum number of scores shown is 5
    if (scores.size() < 5)
    {
        scores.push_back(newScore);
        //sorting the scores
        for (int i = 0; i < scores.size(); i++)
            if (newScore >= scores[i])
            {
                for (int j = static_cast<int>(scores.size()) - 1; j > i; j--)
                    scores[j] = scores[j - 1];
                scores[i] = newScore;
                break;
           }
    }    
    else
    {
        //if there's a lower score than the new one add it
        for (int i = 0; i < scores.size(); i++)
            if (newScore >= scores[i])
            {
                while (scores.size() > 5)
                    scores.pop_back();
                for (int j = static_cast<int>(scores.size()) - 1; j > i; j--)
                    scores[j] = scores[j - 1];
                scores[i] = newScore;
                break;
            }
    }
}

void ScoreManager::outputScores()
{
    //before exiting output the scores to the file
    std::ofstream fout("Scores/scores.txt");
    for (int i = 0; i < scores.size(); i++)
        fout << scores[i] << " ";
    fout.close();
}
