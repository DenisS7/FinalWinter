#pragma once
#include "../surface.h"
#include "../template.h"
#include "Sprites.h"
#include "CollisionComponent.h"
#include "newmath.h"
#include "Room.h"
#include "Spritesheet.h"

namespace Character
{
	class Player;
}

namespace Weapon
{

class IceExplosion
{
private:
	GameSpace::Sprite* sprite = new GameSpace::Sprite();
	Spritesheet currentSs{1, 12, sprite };
	GameSpace::vec2 locf = 0, drawLocf = 0;
	int damage = 15;
	bool dealtDamage = false;
	int pastFrame = 0;
	CollisionComponent col{ 3, 3, 57, 57 };
	Character::Player* player;
	Map::Room* currentRoom = nullptr;
public:

	IceExplosion(int x, int y, int damageBoost, Character::Player* newPlayer)
	{
		player = newPlayer;
		*sprite = *Sprites::get().attack[0];
		damage += damageBoost;
		drawLocf.x = (float)x - sprite->GetWidth() / 2;
		drawLocf.y = (float)y - sprite->GetHeight() / 2;
		col.setOffset(3, 3);
		col.setCollisionBox((int)x + col.offset.x, (int)y + col.offset.y, 57, 57);
		currentSs.setFrameTime(40);
	}

	~IceExplosion()
	{
		sprite = nullptr;
		delete sprite;
	}

	void init();
	void destroy();
	void update(float deltaTime);
};

}

