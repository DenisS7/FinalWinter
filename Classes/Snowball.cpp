#include "Snowball.h"
#include "../surface.h"
#include <iostream>
#include "Room.h"
#include "Player.h"
#include "enemy_snowman.h"
#include "CollisionCheck.h"

namespace Weapon
{
	void Snowball::Init(Character::enemy_snowman* newOwner)
	{

	}

	void Snowball::deleteProjectile()
	{
		owner->removeSnowball(this);
		delete this;
	}

	void Snowball::explode()
	{
		isExploding = true;
		currentSs.freezeFrame(0, false);
		currentSs.setFrameTime(100.0f);
	}

	void Snowball::Move(float deltaTime)
	{
		if (CollisionCheck::isOverlapping(collision, locf, currentRoom, 20, 4, currentRoom->getPlayer()->screen) == 1)
		{
			deleteProjectile();
		}
		else
		{
			timePassed += deltaTime;
			if (timePassed >= timeToExplode)
			{
				timePassed = timeToExplode;
				if (!isExploding)
					explode();
			}

			if (isExploding == true && currentSs.getCurrentFrame() == 3)
			{
				deleteProjectile();
			}
			else
			{
				locf.x += deltaTime * moveDirection.x * speedf;
				locf.y += deltaTime * moveDirection.y * speedf;
				drawLocf = locf - currentRoom->getLocation();
				collision.collisionBox.x = (int)locf.x + collision.offset.x;
				collision.collisionBox.y = (int)locf.y + collision.offset.y;
				currentSs.drawNextSprite(deltaTime, currentRoom->getPlayer()->screen, drawLocf);
			}
		}
	}
}