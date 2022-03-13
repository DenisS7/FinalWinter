#pragma once
#include "Classes/newmath.h"
#include "Classes/StartScreen.h"
#include "Classes/PauseScreen.h"
#include "Classes/EndScreen.h"
#include "Classes/ScoreScreen.h"
#include "MapManager.h"
#include "Classes/Player.h"
#include "Classes/ScoreManager.h"


namespace GameSpace {

class Surface;
class Game
{
private:

	const int startButton = 0, quitButton = 1, replayButton = 2, scoresButton = 3, pathButton = 4, backButton = 5;
	Surface* screen;
	UI::StartScreen* startScreen;
	UI::EndScreen* endScreen;
	UI::PauseScreen* pauseScreen;
	UI::ScoreScreen* scoreScreen;
	UI::ScreenBase* currentScreen;

	ScoreManager scoreManager;
	
	Sprite cursor{ new Surface("assets/UI/cursor.png"), 1 };
	Character::Player* player = new Character::Player();
	Map::MapManager* manager = new Map::MapManager;

	const int start = 0, play = 1, pause = 2, end = 3, score = 4;

	bool isPathOnScreen = false;
	bool isScreenFocus = true;
	bool isRunning = false;
	bool isPaused = false;
	bool isEndScreen = false;
	bool isScoreScreen = false;
	bool won = false;
	bool isMouseDown = false;
	bool outputScore = false;
	int currentScreenType = 0;

	newmath::ivec2 mouse;

public:
	

	void Restart();
	void Pause();
	void SetTarget( Surface* surface ) 
	{ 
		screen = surface; 
		startScreen = new UI::StartScreen(screen);
		endScreen = new UI::EndScreen(screen);
		pauseScreen = new UI::PauseScreen(screen);
		scoreScreen = new UI::ScoreScreen(screen, &scoreManager);
		currentScreen = startScreen;
	}
	void Init();
	void StartGame();
	void StopGame();
	void Shutdown();
	void DrawScreen(float deltaTime);
	void Tick( float deltaTime );
	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y) { mouse.x = x, mouse.y = y; };
	void Input(float deltaTime);
	void PressButton(bool down);
	void KeyUp(int key);
	void KeyDown(int key);

};

}; // namespace Tmpl8