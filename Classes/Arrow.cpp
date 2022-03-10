#include "Arrow.h"
#include "CollisionCheck.h"
#include "../Classes/Room.h"
#include <iostream>

namespace Weapon
{
	Arrow::~Arrow()
	{
		//delete crossbow;
	}

	void Arrow::drawProjectile(GameSpace::Surface* screen, float deltaTime)
	{
		sprite->Draw(screen, (int)drawLocf.x, (int)drawLocf.y);
	}

	void Arrow::Init(WeaponBase* newCrossbow)
	{

	}

	void Arrow::deleteArrow()
	{
		crossbow->deleteArrow(this);
		delete this;
	}



	void Arrow::UpdatePosition(float deltaTime)
	{
		if (!isExploding)
		{
			if (CollisionCheck::isOverlapping(collision, locf, currentRoom, damage, 5, crossbow->player->screen))
			{
				isExploding = true;
				deleteArrow();
			}
			else
			{
				locf.x += speedf * deltaTime * moveDirection.x;
				locf.y += speedf * deltaTime * moveDirection.y;

				drawLocf.x = locf.x - currentRoom->getLocation().x;
				drawLocf.y = locf.y - currentRoom->getLocation().y;

				collision.collisionBox = newmath::make_Rect((int)locf.x, (int)locf.y, 0, 0) + crossbow->arrowCol[direction];
				sprite->Draw(crossbow->player->screen, (int)drawLocf.x, (int)drawLocf.y);
			}
		}
	}


}