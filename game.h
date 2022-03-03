#pragma once
#include "Classes/newmath.h"
#include "Classes/StartScreen.h"

namespace GameSpace {

class Surface;
class Game
{
public:
	bool isRunning = false;
	newmath::ivec2 mouse;

	void Restart();
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void StartGame();
	void StopGame();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y) { mouse.x = x, mouse.y = y; };
	void Input(float deltaTime);
	void PressButton(bool down);
	void KeyUp(int key);
	void KeyDown(int key);
private:
	Surface* screen;
};

}; // namespace Tmpl8