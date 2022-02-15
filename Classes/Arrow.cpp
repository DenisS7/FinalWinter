#include "Arrow.h"
#include "CollisionCheck.h"
#include "../Classes/Room.h"
#include <iostream>

namespace Weapon
{
	void Arrow::Init(WeaponBase* newCrossbow)
	{
		crossbow = newCrossbow;

		locf.x = crossbow->player->locf.x;
		locf.y = crossbow->player->locf.y;

		drawLocf.x = crossbow->player->drawLocf.x;
		drawLocf.y = crossbow->player->drawLocf.y;

		direction = crossbow->player->directionFacing;
		sprite.SetFile(new GameSpace::Surface(crossbow->wpaths[direction + 5].path), 1, 0);
		
		collision.collisionBox = newmath::make_Rect((int)locf.x, (int)locf.y, 0, 0) + crossbow->arrowCol[direction];
		
		this->currentRoom = crossbow->player->currentRoom;
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
		crossbow->deleteArrow(this);
		delete this;
	}

	void Arrow::UpdatePosition(float deltaTime)
	{
		if (CollisionCheck::isOverlapping(collision, locf, currentRoom, 4, crossbow->player->screen))
		{
			deleteArrow();
		}
		else
		{

			locf.x += speedf * deltaTime * move.x;
			locf.y += speedf * deltaTime * move.y;

			drawLocf.x = locf.x - currentRoom->locf.x + speedf * deltaTime * move.x;
			drawLocf.y = locf.y - currentRoom->locf.y + speedf * deltaTime * move.y;

			collision.collisionBox = newmath::make_Rect((int)locf.x, (int)locf.y, 0, 0) + crossbow->arrowCol[direction];

			//std::cout << locf.x << " " << (int)locf.x << std::endl;
			crossbow->player->screen->Box(collision.collisionBox.x, collision.collisionBox.y, collision.collisionBox.x + collision.collisionBox.width, collision.collisionBox.y + collision.collisionBox.height, 0xff0000);
			sprite.Draw(crossbow->player->screen, (int)drawLocf.x, (int)drawLocf.y);
		}
	}


}