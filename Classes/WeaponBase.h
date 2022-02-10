#pragma once

#include "../surface.h"
#include "../Classes/Spritesheet.h"
#include "../Classes/newmath.h"
#include "../template.h"

namespace Weapon
{

class WeaponBase
{

private:

	newmath::ivec2 drawLoc;

	const int crossbow = 5, snowball = 6, snowman = 7;
	int weaponType = 5;
	int speed = 1;



	newmath::spriteData wpaths[10];

public:
	bool visible = false;

	int directionFacing = 0;
	

	GameSpace::vec2 arrows[100];

	GameSpace::Sprite sprite{ new GameSpace::Surface("assets/Weapons/crossbow_down.png"), 1 };
	

	void Init(newmath::ivec2 newDrawLoc);
	void changeDirection(int direction);
	void changeWeapon(int newWeapon);
	void changeVisibility(bool newVisible);
	void shootArrows(int x, int y);
	void Update(float deltaTime);
	
};

}
