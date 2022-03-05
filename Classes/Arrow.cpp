#include "Arrow.h"
#include "CollisionCheck.h"
#include "../Classes/Room.h"
#include <iostream>

namespace Weapon
{
	void Arrow::drawProjectile(GameSpace::Surface* screen, float deltaTime)
	{
		sprite.Draw(screen, (int)drawLocf.x, (int)drawLocf.y);
	}

	void Arrow::Init(WeaponBase* newCrossbow)
	{
		crossbow = newCrossbow;
		this->currentRoom = crossbow->player->currentRoom;

		locf.x = crossbow->player->locf.x;
		locf.y = crossbow->player->locf.y;

		initialPosf = currentRoom->locf;

		drawLocf = locf - currentRoom->locf;

		direction = crossbow->player->directionFacing;

		sprite.SetFile(new GameSpace::Surface(crossbow->wpaths[direction + 5].path), 1, 0);
		
		collision.collisionBox = newmath::make_Rect((int)locf.x, (int)locf.y, 0, 0) + crossbow->arrowCol[direction];
		
		
		if (direction % 2 == 0)
		{
			move.x = 0;
			move.y = - direction + 1;
		}
		else
		{
			move.x = direction - 2;
			move.y = 0;
		}
	}

	void Arrow::deleteArrow()
	{
		//std::cout << time << std::endl;
		crossbow->deleteArrow(this);
		delete this;
	}



	void Arrow::UpdatePosition(float deltaTime)
	{
		if (!isExploding)
		{
			if (CollisionCheck::isOverlapping(collision, locf, currentRoom, 35, 5, crossbow->player->screen))
			{
				isExploding = true;
				deleteArrow();
			}
			else
			{
				locf.x += speedf * deltaTime * move.x;
				locf.y += speedf * deltaTime * move.y;

				drawLocf.x = locf.x - currentRoom->locf.x;
				drawLocf.y = locf.y - currentRoom->locf.y;

				collision.collisionBox = newmath::make_Rect((int)locf.x, (int)locf.y, 0, 0) + crossbow->arrowCol[direction];
				sprite.Draw(crossbow->player->screen, (int)drawLocf.x, (int)drawLocf.y);
			}
		}
	}


}