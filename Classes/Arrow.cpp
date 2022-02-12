#include "Arrow.h"
#include "CollisionCheck.h"
#include "../Classes/Room.h"

namespace Weapon
{
	void Arrow::Init(WeaponBase* newCrossbow)
	{
		crossbow = newCrossbow;
		this->loc = crossbow->player->loc;
		this->drawLoc = crossbow->player->drawloc;
		direction = crossbow->player->directionFacing;
		sprite.SetFile(new GameSpace::Surface(crossbow->wpaths[direction + 5].path), 1, 0);
		
		collision.collisionBox = newmath::make_Rect(loc.x, loc.y, 0, 0) + crossbow->arrowCol[direction];
		
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

	void Arrow::UpdatePosition()
	{
		if (CollisionCheck::isOverlapping(collision, loc, currentRoom, 4, crossbow->player->screen))
		{
			crossbow->deleteArrow(this);
			delete this;
		}
		else
		{
			loc.x += move.x;
			loc.y += move.y;
			drawLoc.x = loc.x - currentRoom->loc.x;
			drawLoc.y = loc.y - currentRoom->loc.y;
			crossbow->player->screen->Box(collision.collisionBox.x, collision.collisionBox.y, collision.collisionBox.x + collision.collisionBox.width, collision.collisionBox.y + collision.collisionBox.height, 0xff0000);
			sprite.Draw(crossbow->player->screen, drawLoc.x, drawLoc.y);
		}
	}
}