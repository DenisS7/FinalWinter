#include "enemy_rager.h"
#include "Player.h"
#include <iostream>
#include "CollisionCheck.h"

namespace Character
{

	void enemy_rager::init()
	{
		EnemyBase::init(2);
		
		EnemyBase::changeActionSprite(0, 0);
		currentState = 0;
		drawLocf = locf - currentRoom->getLocation();
		findPath(getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2)), currentRoom->getPlayer()->getCurrentPos(), currentRoom);
	}

	void enemy_rager::changeActionSprite(int x, int newCurrentRow)
	{
		Sprites::get().rager[x]->SetFrame(directionFacing * data.epaths[x].columns);
		*sprite = *Sprites::get().rager[x];
		EnemyBase::changeActionSprite(x, newCurrentRow);
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
		newmath::ivec2 currentPos = getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2));
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

				drawLocf.x = locf.x - currentRoom->getLocation().x;
				drawLocf.y = locf.y - currentRoom->getLocation().y;
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

					drawLocf.x = locf.x - currentRoom->getLocation().x;
					drawLocf.y = locf.y - currentRoom->getLocation().y;
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
		if (isDead)
		{
			drawLocf = locf - currentRoom->getLocation();
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
			drawLocf = locf - currentRoom->getLocation();
			if (path.size() <= 1 && !isAttacking)
			{
				currentState = 2;
				isAttacking = true;
				attack();
			}
			else if ((isFollowingPlayer || path.size() <= 9) && !isAttacking)
			{
				findPath(getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2)), currentRoom->getPlayer()->getCurrentPos(), currentRoom);
				currentState = 1;
				data.speed += (float)0.000001 * deltaTime;
				triggerFollowPlayer();
				addMovement(deltaTime);
				isFollowingPlayer = true;
			}
			else if (isAttacking)
			{
				if (currentSs.getCurrentFrame() % 12 == 11)
				{
					dealDamage = false;
					currentState = 1;
					changeActionSprite(1, directionFacing);
					isAttacking = false;
					findPath(getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2)), currentRoom->getPlayer()->getCurrentPos(), currentRoom);

				}
				else if (currentSs.getCurrentFrame() % 12 > 7 && !dealDamage)
				{
					CollisionComponent attackCollision = *attackCol;
					attackCollision.collisionBox.x += data.col.collisionBox.x + directionFacing * 50;
					attackCollision.collisionBox.y += data.col.collisionBox.y;
					//screen->Box(attackCollision.collisionBox.x - currentRoom->getLocation().x, attackCollision.collisionBox.y - currentRoom->getLocation().y, attackCollision.collisionBox.x + attackCollision.collisionBox.width - currentRoom->getLocation().x, attackCollision.collisionBox.y + attackCollision.collisionBox.height - currentRoom->getLocation().y, 0xff0000);
					if (CollisionCheck::areColliding(attackCollision, currentRoom->getPlayer()->getCollision()))
					{
						dealDamage = true;
						currentRoom->getPlayer()->takeDamage(data.damagePerAttack);
					}
				}
			}
			else
			{
				findPath(getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2)), currentRoom->getPlayer()->getCurrentPos(), currentRoom);

				drawLocf = locf - currentRoom->getLocation();
			}
		}
		//screen->Box(drawLocf.x, drawLocf.y, drawLocf.x + data.col.collisionBox.width, drawLocf.y + data.col.collisionBox.height, 0xff0000);
	}
}
