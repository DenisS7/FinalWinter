#pragma once
#include "Classes/newmath.h"

namespace GameSpace {

class Surface;
class Game
{
public:

	newmath::ivec2 mouse;

	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y) { mouse.x = x, mouse.y = y; };
	void Input(float deltaTime);
	void KeyUp(int key);
	void KeyDown(int key);
private:
	Surface* screen;
};

}; // namespace Tmpl8