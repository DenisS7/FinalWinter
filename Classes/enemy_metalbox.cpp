#include "enemy_metalbox.h"
#include "Player.h"
#include "CollisionCheck.h"
#include <iostream>

namespace Character
{
	void enemy_metalbox::init()
	{
		EnemyBase::init(0);
		
		tilePos = EnemyBase::getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2));
	}

	void enemy_metalbox::changeActionSprite(int x, int newCurrentRow)
	{
		Sprites::get().metalgift[x]->SetFrame(directionFacing * data.epaths[x].columns);
		*sprite = *Sprites::get().metalgift[x];
		EnemyBase::changeActionSprite(x, newCurrentRow);
	}

	void enemy_metalbox::explode()
	{
		directionFacing = 0;
		changeActionSprite(2, 0);
	}

	void enemy_metalbox::triggerFollowPlayer()
	{
		if (!isFollowingPlayer)
			changeActionSprite(1, directionFacing);
		isFollowingPlayer = true;
		isAttacking = false;
	}

	void enemy_metalbox::addMovement(float deltaTime)
	{
		newmath::ivec2 currentPos = getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2));
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
					locf.y += float(dir.y * data.speed * deltaTime * div);\
					
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
	}

	void enemy_metalbox::update(float deltaTime)
	{
		
		EnemyBase::update(deltaTime);
	
		if ((path.size() <= 1 || isDead) && !isAttacking)
		{
			isFollowingPlayer = false;
			isAttacking = true;
			explode();
		}
		else if ((isFollowingPlayer || path.size() <= 8) && !isAttacking)
		{
			findPath(getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2)), currentRoom->getPlayer()->getCurrentPos(), currentRoom);
			data.speed += (float)0.000002 * deltaTime;
			triggerFollowPlayer();
			addMovement(deltaTime);
			isFollowingPlayer = true;
		}
		else 
		{
			findPath(getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2)), currentRoom->getPlayer()->getCurrentPos(), currentRoom);
			drawLocf = locf - currentRoom->getLocation();
		}

		if (isAttacking)
		{
			if (currentSs.getCurrentFrame() == 8 && !exploded)
			{
				exploded = true;
				data.col.extendCollision(explosionRange, explosionRange);
				if (CollisionCheck::areColliding(this->data.col, currentRoom->getPlayer()->getCollision()))
					currentRoom->getPlayer()->takeDamage(data.damagePerAttack);
				
			}
			if (currentSs.getCurrentFrame() == 12)
				EnemyBase::die();
		}
		
	}
}
