#pragma once
#include "Projectile.h"
#include "newmath.h"
#include "CollisionComponent.h"
#include "../Classes/Room.h"


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
	Snowball(Map::Room* newCurrentRoom, GameSpace::vec2 newDestination, GameSpace::vec2 newInitial, Character::enemy_snowman* newOwner) :
		Projectile (newInitial, newCurrentRoom)
	{
		owner = newOwner;
		timeToExplode = 1000;
		destination = newDestination;
		moveDirection = GameSpace::vec2::normalize(destination - locf);
		collision.offset = newmath::make_ivec2(22, 22);
		collision.collisionBox = newmath::make_Rect((int)locf.x + 22, (int)locf.y + 22, 20, 20);
		speedf = 0.2f;
		currentSs.freezeFrame(0, true);

		if (abs(moveDirection.x) <= abs(moveDirection.y))
		{
			if (moveDirection.y <= 0)
				sprite.SetFile(new GameSpace::Surface("assets/Weapons/snowball_attack-blue_down.png"), 4, 0);
			else sprite.SetFile(new GameSpace::Surface("assets/Weapons/snowball_attack-blue_up.png"), 4, 0);
		}
		else
		{
			if (moveDirection.x <= 0)
				sprite.SetFile(new GameSpace::Surface("assets/Weapons/snowball_attack-blue_right.png"), 4, 0);
			else
				sprite.SetFile(new GameSpace::Surface("assets/Weapons/snowball_attack-blue_left.png"), 4, 0);
		}
	}
	void Init(Character::enemy_snowman* newOwner);
	void deleteProjectile() override;
	void explode();

	void Move(float deltaTime) override;
};

}
