#include "enemy_rager.h"
#include "Player.h"
#include <iostream>

namespace Character
{

	void enemy_rager::init()
	{
		data.points = 20;
		EnemyBase::init(2);
		currentSs.setDirection(0);
		EnemyBase::changeActionSprite(0, 0);
		currentState = 0;
		drawLocf = locf - currentRoom->locf;
		findPath(getCurrentPos(newmath::make_ivec2(sprite.GetWidth() / 2, sprite.GetHeight() / 2)), currentRoom->player->getCurrentPos());
	}

	void enemy_rager::attack()
	{
		changeActionSprite(2, directionFacing);
	}

	void enemy_rager::changeDirection(int newDirection)
	{
		currentSs.setDirection(newDirection);
		directionFacing = newDirection;
	}

	void enemy_rager::triggerFollowPlayer()
	{
		if (!isFollowingPlayer)
			changeActionSprite(1, directionFacing);
		isFollowingPlayer = true;
	}

	void enemy_rager::addMovement(float deltaTime)
	{
		newmath::ivec2 currentPos = getCurrentPos(newmath::make_ivec2(sprite.GetWidth() / 2, sprite.GetHeight() / 2));
		if (path.size())
		{
			const newmath::ivec2 nextPos = *path.begin();
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
					locf.y += float(dir.y * data.speed * deltaTime * div); \

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

			if (dir.x == -1)
				changeDirection(0); // x = -1 || x = 1; left = 1, right = 3
			else if (dir.x == 1)
				changeDirection(1);
		}
	}

	void enemy_rager::update(float deltaTime)
	{
		EnemyBase::update(deltaTime);
		//std::cout << currentState << std::endl;
		if (isDead)
		{
			if (currentState != 3)
			{
				changeActionSprite(3, directionFacing);
				currentState = 3;
				currentSs.setFrame(1 + directionFacing * data.epaths->columns);
			}
			else if (currentSs.getCurrentFrame() % 8 == 7)
				die();
		}
		else
		{
			if (path.size() <= 1 && !isExploding)
			{
				std::cout << "ATTACK \n";
				currentState = 2;
				isExploding = true;
				attack();
			}
			else if ((isFollowingPlayer || path.size() <= 7) && !isExploding)
			{
				std::cout << "FOLLOW \n";
				currentState = 1;
				data.speed += (float)0.000001 * deltaTime;
				triggerFollowPlayer();
				addMovement(deltaTime);
				isFollowingPlayer = true;
			}
			else if (isExploding && currentSs.getCurrentFrame() % 12 == 11)
			{
				std::cout << "END ATTACK \n";
				currentState = 1;
				changeActionSprite(1, directionFacing);
				isExploding = false;
			}
			else
			{
				drawLocf = locf - currentRoom->locf;
			}
			findPath(getCurrentPos(newmath::make_ivec2(sprite.GetWidth() / 2, sprite.GetHeight() / 2)), currentRoom->player->getCurrentPos());
		}
	}
}
