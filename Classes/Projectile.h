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

	newmath::ivec2 move;
	GameSpace::vec2 locf, drawLocf, initialPosf;
	float speedf = 0.4f;
	int direction, damage, speed;
	GameSpace::Sprite sprite{new GameSpace::Surface("assets/Weapons/arrow_down.png"), 1};
	newmath::spriteData ppaths[6];
	

	Projectile()
	{

	}

	~Projectile()
	{

	}

	void Init();
	void Spawn(newmath::ivec2 newLoc, newmath::ivec2 newDrawLoc, int newDirection);
	void Move(float deltaTime);
	void checkCollision();
};

}
