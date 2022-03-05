#pragma once
#include "Classes/newmath.h"
#include "Classes/StartScreen.h"
#include "Classes/PauseScreen.h"
#include "Classes/EndScreen.h"
#include "MapManager.h"
#include "Classes/Player.h"


namespace GameSpace {

class Surface;
class Game
{
private:
	Surface* screen;
	UI::StartScreen* startScreen;
	UI::EndScreen* endScreen;
	UI::PauseScreen* pauseScreen;
	UI::ScreenBase* currentScreen;
	

	Character::Player* player = new Character::Player();
	Map::MapManager* manager = new Map::MapManager;

	bool isScreenFocus = true;
	bool isRunning = false;
	bool isPaused = false;
	bool isEndScreen = false;
	bool won = false;

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
	void PressButton(bool down, UI::ScreenBase* currentScreen);
	void KeyUp(int key);
	void KeyDown(int key);

};

}; // namespace Tmpl8