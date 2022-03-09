#include "enemy_snowman.h"
#include "Player.h"
#include "Snowball.h"
#include <iostream>

namespace Character
{
	void enemy_snowman::init()
	{
		EnemyBase::init(1);
	
		EnemyBase::changeActionSprite(1, 0);
		currentState = 1;
		currentSs.freezeFrame(0, true);
		drawLocf = locf - currentRoom->getLocation();
	}

	void enemy_snowman::changeActionSprite(int x, int newCurrentRow)
	{
		*sprite = *Sprites::get().snowball[x];
		EnemyBase::changeActionSprite(x, newCurrentRow);
	}

	void enemy_snowman::changeDirection(int newDirection)
	{
		directionFacing = newDirection;
		currentSs.setDirection(newDirection);
	}

	void enemy_snowman::turnToPlayer()
	{
		GameSpace::vec2 dif = currentRoom->getPlayer()->getDrawLocation() - this->drawLocf;

		dif.x += (float)(currentRoom->getPlayer()->getSpriteSize().x - this->sprite->GetWidth()) / 2;
		dif.y += (float)(currentRoom->getPlayer()->getSpriteSize().y - this->sprite->GetHeight()) / 2;

		const GameSpace::vec2 range(100.0f, 100.0f);
	
		int newDirection = 0;
		float divideValuex = 300.0f;
		float divideValuey = 300.0f;

		if (dif.x < -range.x * ((int)abs(dif.y) / divideValuey))
		{
			if (dif.y < -range.y * ((int)abs(dif.x) / divideValuex))
			{
				newDirection = 3; // up - left
			}
			else if (dif.y > range.y * ((int)abs(dif.x) / divideValuex))
			{
				newDirection = 1; // down - left
			}
			else
			{
				newDirection = 2; // left
			}
		}
		else if (dif.x > range.x * ((int)abs(dif.y)  / divideValuey))
		{
			if (dif.y < -range.y * ((int)abs(dif.x)  / divideValuex))
			{
				newDirection = 5; // up - right
			}
			else if (dif.y > range.y * ((int)abs(dif.x)  / divideValuex))
			{
				newDirection = 7; // down - right
			}
			else
			{
				newDirection = 6; // right
			}
		}
		else
		{
			if (dif.y < -range.y * ((int)abs(dif.x) / divideValuex))
			{
				newDirection = 4; // up
			}
			else if (dif.y > range.y * ((int)abs(dif.x) / divideValuex))
			{
				newDirection = 0;// down
			}
			else
			{
				newDirection = 0; // not gonna be used 
			}
		}
		changeDirection(newDirection);
	}

	void enemy_snowman::removeSnowball(Weapon::Snowball* snowballToRemove)
	{
		std::vector<Weapon::Snowball*>::iterator position = std::find(snowballs.begin(), snowballs.end(), snowballToRemove);
		if (position != snowballs.end())
			snowballs.erase(position);
	}

	void enemy_snowman::attack()
	{
		const GameSpace::vec2 snowballLocf(locf.x + snowballPos[directionFacing].x, locf.y + snowballPos[directionFacing].y);
		Weapon::Snowball* newSnowball = new Weapon::Snowball(currentRoom, currentRoom->getPlayer()->getLocation(), snowballLocf, this);
		snowballs.push_back(newSnowball);
	}

	void enemy_snowman::triggerFollowPlayer()
	{
		currentSs.freezeFrame(0, false);
		isFollowingPlayer = true;
		//EnemyBase::changeActionSprite(0, 0);
	}

	void enemy_snowman::update(float deltaTime)
	{
		EnemyBase::update(deltaTime);
		drawLocf = locf - currentRoom->getLocation();
		for (int i = 0; i < snowballs.size(); i++)
			snowballs[i]->Move(deltaTime);
		if (isDead)
		{
			currentSs.freezeFrame(0, false);
			if (currentState == 3 && currentSs.getCurrentFrame() % 6 == 5)
			{
				if (snowballs.size() == 0)
				{
					if (currentSs.getVisibility())
						die();
					else currentRoom->removeEnemy(this);
				}
				else
				{
					if (currentSs.getVisibility())
						currentRoom->hideEnemy(this);
					currentSs.freezeFrame(currentSs.getCurrentFrame(), true);
					currentSs.changeVisiblity(false);
					data.col.collisionBox.x = data.col.collisionBox.y = 0;
					
					//currentRoom->deleteEnemy(this);
				}
			}
			else if (currentState != 3)
			{
				currentState = 3;
				changeActionSprite(3, 0);
				isAttacking = false;
				isFollowingPlayer = false;
			}
		}
		else
		{
			if (!isFollowingPlayer)
			{
				EnemyBase::findPath(getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2)), currentRoom->getPlayer()->getCurrentPos(), currentRoom);
				if (path.size() <= 12)
				{
					currentSs.freezeFrame(0, false);
					isFollowingPlayer = true;
				}
			}
			if (currentState == 1 && currentSs.getCurrentFrame() == 9)
			{
				currentState = 0;
				changeActionSprite(0, 0);
				turnToPlayer();
			}
			if (currentState == 0)
			{
				if (GameSpace::vec2::dist(this->locf, currentRoom->getPlayer()->getLocation()) < 600 && !isAttacking)
				{
					isAttacking = true;
					currentState = 2;
					changeActionSprite(2, directionFacing);
					attack();
				}
				else turnToPlayer();
			}
			if (currentState == 2 && (currentSs.getCurrentFrame() % 7) == 6)
			{
				isAttacking = false;
				currentState = 0;
				changeActionSprite(0, directionFacing);
				turnToPlayer();
			}
		}
	}
}