#pragma once
#include "Projectile.h"
#include "newmath.h"
#include "CollisionComponent.h"
#include "../Classes/Room.h"
#include "Sprites.h"


namespace Character
{
	class enemy_snowman;
}

namespace Weapon
{

class Snowball:
	private Projectile
{
private:
	GameSpace::vec2 destination, initial, moveDirection;
	Character::enemy_snowman* owner;
public:
	Snowball(Map::Room* newCurrentRoom, GameSpace::vec2 newDestination, GameSpace::vec2 newInitial)
	{
		timeToExplode = 1000;
		this->currentRoom = newCurrentRoom;
		destination = newDestination;
		locf = newInitial;
		moveDirection = GameSpace::vec2::normalize(destination - locf);
		collision.offset = newmath::make_ivec2(22, 22);
		collision.collisionBox = newmath::make_Rect((int)locf.x + 22, (int)locf.y + 22, 20, 20);
		speedf = 0.2f;

		if (abs(moveDirection.x) <= abs(moveDirection.y))
		{
			if (moveDirection.y <= 0)
				sprite.SetFile(Sprites::get().snowball[0], 4, 0);
			else sprite.SetFile(Sprites::get().snowball[2], 4, 0);
		}
		else
		{
			if (moveDirection.x <= 0)
				sprite.SetFile(Sprites::get().snowball[3], 4, 0);
			else
				sprite.SetFile(Sprites::get().snowball[1], 4, 0);
		}
	}
	void Init(Character::enemy_snowman* newOwner);
	void deleteProjectile() override;
	void explode();

	void Move(float deltaTime) override;
};

}
