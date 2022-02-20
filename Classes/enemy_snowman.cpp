#include "enemy_snowman.h"
#include "Player.h"
#include <iostream>

namespace Character
{
	void enemy_snowman::init()
	{
		EnemyBase::Init();
		currentSs.setDirection(0);
		EnemyBase::changeActionSprite(1, 0);
		currentSs.freezeFrame(0, true);
		currentState = 1;
	}

	void enemy_snowman::changeDirection(int newDirection)
	{
		directionFacing = newDirection;
		currentSs.setDirection(newDirection);
		std::cout << "Snowman Direction Changed" << std::endl;
	}

	void enemy_snowman::turnToPlayer()
	{
		const GameSpace::vec2 dif = currentRoom->player->locf + currentRoom->player->sprite.GetHeight() / 2 + currentRoom->player->sprite.GetWidth() / 2 - this->locf - this->sprite.GetHeight() / 2 - this->sprite.GetWidth() / 2;
		
		const GameSpace::vec2 range(150.0f, 150.0f);
	
		int newDirection = 0;

		if (dif.x < this->locf.x - range.x * (abs(dif.y) / 500.0f))
		{
			if (dif.y < this->locf.y - range.y * (abs(dif.x) / 500.0f))
			{
				newDirection = 1;
			}
			else if (dif.y > this->locf.y - range.y * (abs(dif.x) / 500.0f))
			{
				newDirection = 3;
			}
			else
			{
				newDirection = 2;
			}
		}
		else if (dif.x > this->locf.x + range.x * (abs(dif.y) / 500.0f))
		{
			if (dif.y < this->locf.y - range.y * (abs(dif.x) / 500.0f))
			{
				newDirection = 7;
			}
			else if (dif.y > this->locf.y - range.y * (abs(dif.x) / 500.0f))
			{
				newDirection = 5;
			}
			else
			{
				newDirection = 6;
			}
		}
		else
		{
			if (dif.y < this->locf.y - range.y * (abs(dif.x) / 500.0f))
			{
				newDirection = 0;
			}
			else if (dif.y > this->locf.y - range.y * (abs(dif.x) / 500.0f))
			{
				newDirection = 4;
			}
			else
			{
				newDirection = 0;
			}
		}
		newDirection;
		currentSs.freezeFrame(directionFacing, true);
		changeDirection(newDirection);
	}

	void enemy_snowman::triggerFollowPlayer()
	{
		isFollowingPlayer = true;
		EnemyBase::changeActionSprite(0, 0);
	}

	void enemy_snowman::update(float deltaTime)
	{
		//EnemyBase::update(deltaTime);
		if (!isFollowingPlayer)
		{
			EnemyBase::findPath(getCurrentPos(newmath::make_ivec2(sprite.GetWidth() / 2, sprite.GetHeight() / 2)), currentRoom->player->getCurrentPos());
			if (path.size() <= 9)
			{
				isFollowingPlayer = true;
				currentSs.freezeFrame(0, false);
			}
		}
		if (currentState == 1 && currentSs.getCurrentFrame() == 9)
		{
			currentState = 2;
			changeActionSprite(1, 0);
			turnToPlayer();
		}
	}
}