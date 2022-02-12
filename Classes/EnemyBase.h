#pragma once
#include "../Classes/Spritesheet.h"
#include "../surface.h"
#include "../Classes/newmath.h"
#include "../template.h"
#include "../Classes/CollisionComponent.h"

namespace Character
{

class EnemyBase
{
private:

	newmath::spriteData epaths[10];
	GameSpace::Surface sprite;
	Spritesheet sheet;

public:

	int enemyType; //1 - snowman    2 - metalgift    3 - deer
	int damageOnCollision = 1;
	newmath::ivec2 centre;
	newmath::ivec2 loc, drawLoc;
	CollisionComponent collisionBox;

	void takeDamage(int damage);
};

}

