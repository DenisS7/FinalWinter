#pragma once
#include <fstream>
#include <vector>

class ScoreManager
{
private:
	std::vector <int> scores;
public:
	
	std::vector <int> getScores() { return scores; };
	//int getNrScores() { return nrScores; };

	void readScores();
	void checkScore(int newScore);
	void outputScores();
};

