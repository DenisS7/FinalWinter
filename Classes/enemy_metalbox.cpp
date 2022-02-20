#include "enemy_metalbox.h"
#include "Player.h"
#include <iostream>

namespace Character
{
	void enemy_metalbox::Init()
	{
		EnemyBase::Init();
		currentSs.setDirection(0);
		//locf.x = drawLocf.x = 150.0f;
		//locf.y = drawLocf.y = 150.0f;
		tilePos = EnemyBase::getCurrentPos(newmath::make_ivec2(sprite.GetWidth() / 2, sprite.GetHeight() / 2));
		findPath(tilePos, currentRoom->player->getCurrentPos());
	}

	void enemy_metalbox::explode()
	{
		//std::cout << "EXPLODE" << std::endl;
		directionFacing = 0;
		EnemyBase::changeActionSprite(2, 0);
	}

	void enemy_metalbox::triggerFollowPlayer()
	{
		if (!isFollowingPlayer)
			EnemyBase::changeActionSprite(1, directionFacing);
		isFollowingPlayer = true;
	}

	void enemy_metalbox::addMovement(float deltaTime)
	{
		newmath::ivec2 currentPos = getCurrentPos(newmath::make_ivec2(sprite.GetWidth() / 2, sprite.GetHeight() / 2));
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
				
				data.col.collisionBox.x = (int)locf.x + data.col.offset.x;
				data.col.collisionBox.y = (int)locf.y + data.col.offset.y;

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
					locf.y += float(dir.y * data.speed * deltaTime * div);\
					
					data.col.collisionBox.x = (int)locf.x + data.col.offset.x;
					data.col.collisionBox.y = (int)locf.y + data.col.offset.y;
					
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
		
		EnemyBase::update(deltaTime);

		//screen->Box(data.col.collisionBox.x - currentRoom->locf.x, data.col.collisionBox.y - currentRoom->locf.y, data.col.collisionBox.x + data.col.collisionBox.width - currentRoom->locf.x, data.col.collisionBox.y + data.col.collisionBox.height - currentRoom->locf.y, 0xff0000);

		//for (int x = initOcupTile.x; x <= finOcupTile.x && x <= currentRoom->size.x; x++)
			//for (int y = initOcupTile.y; y <= finOcupTile.y && y <= currentRoom->size.y; y++)
				//screen->Box(x * 32 - currentRoom->locf.x, y * 32 - currentRoom->locf.y, x * 32 - currentRoom->locf.x + 32, y * 32 - currentRoom->locf.y + 32, 0x00ff00);


		currentTimePath += deltaTime;
		//if (currentTimePath >= timeUntilPathRefresh)
			
		//std::cout << currentRoom->roomNumber << " " << path.size() << std::endl;
		if ((path.size() <= 1 || isDead) && !isExploding)
		{
			isFollowingPlayer = false;
			isExploding = true;
			explode();
		}
		else if ((isFollowingPlayer || path.size() <= 7) && !isExploding)
		{
			data.speed += (float)0.000002 * deltaTime;
			triggerFollowPlayer();
			addMovement(deltaTime);
			isFollowingPlayer = true;
		}
		else
		{
			drawLocf = locf - currentRoom->locf;
		}
		findPath(getCurrentPos(newmath::make_ivec2(sprite.GetWidth() / 2, sprite.GetHeight() / 2)), currentRoom->player->getCurrentPos());
		
		//std::cout << currentSs.getCurrentFrame() << std::endl;

		if (isExploding && currentSs.getCurrentFrame() == 12)
			EnemyBase::die();
		
	}
}
