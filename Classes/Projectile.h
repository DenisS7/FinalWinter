#pragma once
#include "newmath.h"
#include "../surface.h"
#include "../template.h"


namespace Weapon 
{

class Projectile
{
private:


public:

	GameSpace::vec2 loc, drawLoc;
	int direction, damage, speed;
	GameSpace::Sprite sprite;
	newmath::spriteData ppaths[6];
	

	void Init();
	void Spawn(newmath::ivec2 newLoc, newmath::ivec2 newDrawLoc, int newDirection);
	void Move(float deltaTime);
	void checkCollision();
};

}
