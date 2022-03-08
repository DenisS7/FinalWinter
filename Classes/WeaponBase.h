#pragma once

#include "../surface.h"
#include "../Classes/Spritesheet.h"
#include "../Classes/newmath.h"
#include "../template.h"
#include "../Classes/Arrow.h"
#include <vector>


namespace Character
{
	class Player;
}

namespace Weapon
{

class WeaponBase
{

private:

	GameSpace::vec2 drawLocf;

	const int crossbow = 5, snowball = 6, snowman = 7;
	int weaponType = 5;
	int speed = 1;
	int damage = 25;

public:

	~WeaponBase()
	{
		for (int i = 0; i < arrows.size(); i++)
			delete arrows[i];
		delete sprite.GetSurface();
	}


	const newmath::Rect arrowCol[4] = {
		newmath::make_Rect(27, 23, 22, 12),
		newmath::make_Rect(18, 31, 12, 22),
		newmath::make_Rect(25, 20, 22, 12),
		newmath::make_Rect(23, 31, 12, 22)
	};
	Character::Player* player;
	bool visible = false;
	std::vector <Arrow*> arrows;
	int directionFacing = 0;
	float reloadTime = 300.0f;
	float reloading = 0.0f;
	bool isShooting = false;
	newmath::spriteData wpaths[10];

	GameSpace::Sprite sprite{ new GameSpace::Surface("assets/Weapons/crossbow_down.png"), 1 };
	
	void setReloadTime(float newReloadTime) { reloadTime = newReloadTime; };
	void setDamage(int newDamage) { damage = newDamage; };
	void Init(GameSpace::vec2 newDrawLocf, Character::Player* newPlayer);
	void reload(float deltaTime);
	void changeDirection(int direction);
	void changeWeapon(int newWeapon);
	void changeVisibility(bool newVisible);
	void shootArrows();
	void stopShooting();
	void deleteArrow(Arrow* endArrow);
	void drawWeapon(float deltaTime);
	void update(float deltaTime);
};

}
