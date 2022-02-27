#pragma once
#include "newmath.h"
#include "../surface.h"
#include "../template.h"
#include "Room.h"
#include "Spritesheet.h"
#include "CollisionComponent.h"

namespace Weapon 
{

class Projectile
{
private:


public:

	CollisionComponent collision;
	Map::Room* currentRoom;
	newmath::ivec2 move;
	GameSpace::vec2 locf, drawLocf, initialPosf;
	float speedf = 0.4f;
	int direction, damage, speed;
	GameSpace::Sprite sprite{ new GameSpace::Surface("assets/Weapons/arrow_down.png"), 1 };
	
	Spritesheet currentSs{ "assets/Weapons/snowball_attack-blue_down.png", 1, 4, &sprite };

	bool isExploding = false;
	float timeToExplode = 3000.0f;
	float timePassed = 0.0f;

	newmath::spriteData ppaths[6];
	

	Projectile()
	{

	}

	~Projectile()
	{
		
	}

	virtual void Init();
	virtual void Spawn(newmath::ivec2 newLoc, newmath::ivec2 newDrawLoc, int newDirection);
	virtual void deleteProjectile();
	virtual void Move(float deltaTime);
	void checkCollision();
};

}
