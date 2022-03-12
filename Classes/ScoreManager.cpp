#include "ScoreManager.h"
#include <iostream>

void ScoreManager::readScores()
{
	int x;
	std::ifstream fin("Scores/scores.txt");
	while (fin >> x && scores.size() < 6)
		scores.push_back(x);
	fin.close();
}

void ScoreManager::checkScore(int newScore)
{
	if (scores.size() < 6)
	{
		if (!scores.size() || scores.back() >= newScore)
		{
			scores.push_back(newScore);
		}
	}
	else
	{
		for (int i = 0; i < scores.size(); i++)
			if (newScore >= scores[i])
			{
				while (scores.size() > 5)
					scores.pop_back();
				for (int j = scores.size() - 1; j > i; j--)
					scores[j] = scores[j - 1];
				scores[i] = newScore;
				break;
			}
	}
}

void ScoreManager::outputScores()
{
	std::ofstream fout("Scores/scores.txt");
	for (int i = 0; i < scores.size(); i++)
		fout << scores[i] << " ";
	fout.close();
}
