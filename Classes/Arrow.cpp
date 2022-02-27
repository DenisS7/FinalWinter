#include "Arrow.h"
#include "CollisionCheck.h"
#include "../Classes/Room.h"
#include <iostream>

namespace Weapon
{
	void Arrow::Init(WeaponBase* newCrossbow)
	{
		crossbow = newCrossbow;
		this->currentRoom = crossbow->player->currentRoom;

		locf.x = crossbow->player->locf.x;
		locf.y = crossbow->player->locf.y;

		initialPosf = currentRoom->locf;

		drawLocf = locf - currentRoom->locf;

		direction = crossbow->player->directionFacing;

		GameSpace::Surface* arrow = new GameSpace::Surface("assets/Weapons/arrow_down.png");
		
		arrow = Sprites::get().arrow[direction];

		sprite.SetFile(arrow, 1, 0);
		
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

				//std::cout << currentRoom->moveDir.x * currentRoom->player->move.speed * deltaTime << " " << currentRoom->moveDir.y * currentRoom->player->move.speed * deltaTime << std::endl;

				//std::cout << drawLocf.x << " " << drawLocf.y << std::endl;

				drawLocf.x = locf.x - currentRoom->locf.x;
				drawLocf.y = locf.y - currentRoom->locf.y;

				collision.collisionBox = newmath::make_Rect((int)locf.x, (int)locf.y, 0, 0) + crossbow->arrowCol[direction];

				//std::cout << locf.x << " " << (int)locf.x << std::endl;
				sprite.Draw(crossbow->player->screen, (int)drawLocf.x, (int)drawLocf.y);
				//crossbow->player->screen->Box(collision.collisionBox.x - currentRoom->locf.x, collision.collisionBox.y - currentRoom->locf.y, collision.collisionBox.x + collision.collisionBox.width - currentRoom->locf.x, collision.collisionBox.y + collision.collisionBox.height - currentRoom->locf.y, 0xff0000);
				//drawLocf.x -= move.x * (abs(currentRoom->locf.x - initialPosf.x));
				//drawLocf.y -= move.y * (abs(currentRoom->locf.y - initialPosf.y));
			}
		}
	}


}