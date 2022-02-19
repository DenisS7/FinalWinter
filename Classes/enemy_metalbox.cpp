#include "enemy_metalbox.h"
#include "Player.h"
#include <iostream>

namespace Character
{
	void enemy_metalbox::Init()
	{
		EnemyBase::Init();
		currentSs.setDirection(0);
		locf.x = drawLocf.x = 150.0f;
		locf.y = drawLocf.y = 150.0f;
		tilePos = EnemyBase::getCurrentPos();
		findPath(tilePos, currentRoom->player->getCurrentPos());
		
	}

	void enemy_metalbox::explode()
	{
		directionFacing = 0;
		EnemyBase::changeActionSprite(2, 0);
	}

	

	void enemy_metalbox::addMovement(float deltaTime)
	{
		newmath::ivec2 currentPos = getCurrentPos();
		if (path.size())
		{
			newmath::ivec2 nextPos = *path.begin();
			newmath::ivec2 dir(nextPos.x - currentPos.x, nextPos.y - currentPos.y);
			if (currentPos != nextPos)
			{
				float div = 1;
				if (dir.x && dir.y)
					div = 2.0f / 3.0f;

				locf.x += float(dir.x * data.speed * deltaTime * div);
				locf.y += float(dir.y * data.speed * deltaTime * div);
				
				drawLocf.x = locf.x - currentRoom->locf.x;
				drawLocf.y = locf.y - currentRoom->locf.y;
			}
			else
			{
				path.erase(path.begin());
				if (path.size())
				{
					newmath::ivec2 nextPos = *path.begin();
					dir.x = nextPos.x - currentPos.x;
					dir.y = nextPos.y - currentPos.y;
					
					float div = 1;
					if (dir.x && dir.y)
						div = 2.0f / 3.0f;
					locf.x += float(dir.x * data.speed * deltaTime * div);
					locf.y += float(dir.y * data.speed * deltaTime * div);
					
					drawLocf.x = locf.x - currentRoom->locf.x;
					drawLocf.y = locf.y - currentRoom->locf.y;
				}
			}

			if (dir.x)
			{
				move.side[dir.x + 2] = true;
				move.side[(dir.x + 4) % 4] = false;
				
			}
			else move.side[1] = move.side[3] = false;

			if (dir.y)
			{
				move.side[(dir.y + 3) % 4] = true;
				move.side[dir.y + 1] = false;
			}
			else move.side[0] = move.side[2] = false;

			if (dir.x)
				EnemyBase::changeDirection(dir.x + 2); // x = -1 || x = 1; left = 1, right = 3
			if (dir.y)
				EnemyBase::changeDirection((dir.y + 3) % 4); // y = 1 (down) || y = -1 (up); down = 0, up = 2
		}
		//else explode
	}

	void enemy_metalbox::update(float deltaTime)
	{
		std::cout << data.speed << std::endl;
		EnemyBase::update(deltaTime);
		currentTimePath += deltaTime;
		//if (currentTimePath >= timeUntilPathRefresh)
			
		//std::cout << currentRoom->roomNumber << " " << path.size() << std::endl;
		if (path.size() <= 1 && !isExploding)
		{
			isExploding = true;
			explode();
		}
		if ((isFollowingPlayer || path.size() <= 7) && !isExploding)
		{
			if (!isFollowingPlayer)
				EnemyBase::changeActionSprite(1, directionFacing);
			addMovement(deltaTime);
			isFollowingPlayer = true;
		}
		else
		{
			drawLocf = locf - currentRoom->locf;
		}
		findPath(getCurrentPos(), currentRoom->player->getCurrentPos());

		if (currentSs.getCurrentFrame() == 12 && isExploding)
			EnemyBase::die();
		data.speed += 0.000002 * deltaTime;
	}
}
