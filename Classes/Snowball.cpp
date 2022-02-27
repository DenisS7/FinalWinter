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
		owner = newOwner;
		currentSs.freezeFrame(0, true);
	}

	void Snowball::deleteProjectile()
	{
		owner->removeSnowball(this);
		std::cout << "Removed" << std::endl;
		delete this;
	}

	void Snowball::explode()
	{
		isExploding = true;
		//collision.collisionBox = newmath::make_Rect();	change collision - direction
		currentSs.freezeFrame(0, false);
		currentSs.setFrameTime(80.0f);
	}

	void Snowball::Move(float deltaTime)
	{
		//std::cout << "Collision Type: " << CollisionCheck::isOverlapping(collision, locf, currentRoom, 3, 4, currentRoom->player->screen) << std::endl;
		if (CollisionCheck::isOverlapping(collision, locf, currentRoom, 3, 4, currentRoom->player->screen) == 1)
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

			std::cout << currentSs.getCurrentFrame() << std::endl;

			if (isExploding == true && currentSs.getCurrentFrame() == 3)
			{
				deleteProjectile();
			}
			else
			{
				locf.x += deltaTime * moveDirection.x * speedf;
				locf.y += deltaTime * moveDirection.y * speedf;
				drawLocf = locf - currentRoom->locf;
				collision.collisionBox.x = (int)locf.x + collision.offset.x;
				collision.collisionBox.y = (int)locf.y + collision.offset.y;
				//std::cout << collision.collisionBox.x << " " << drawLocf.y << std::endl;
				//currentRoom->player->screen->Box(drawLocf.x + 20, drawLocf.y + 20, drawLocf.x + 20 + 22, drawLocf.y + 20 + 22, 0xff0000);
				currentSs.drawNextSprite(deltaTime, currentRoom->player->screen, drawLocf);
			}
		}
	}
}