#include "enemy_snowman.h"
#include "Player.h"
#include <iostream>

namespace Character
{
	void enemy_snowman::init()
	{
		EnemyBase::init(1);
		currentSs.setDirection(0);
		EnemyBase::changeActionSprite(1, 0);
		currentState = 1;
		currentSs.freezeFrame(0, true);
		drawLocf = locf - currentRoom->locf;
		if (currentRoom->roomNumber == 39)
			std::cout << "Snowman " << drawLocf.x << " " << drawLocf.y << std::endl;
	}

	void enemy_snowman::changeDirection(int newDirection)
	{
		directionFacing = newDirection;
		currentSs.setDirection(newDirection);
		std::cout << "Snowman Direction Changed" << std::endl;
	}

	void enemy_snowman::turnToPlayer()
	{
		GameSpace::vec2 dif = currentRoom->player->drawLocf  - this->drawLocf;

		dif.x += (currentRoom->player->sprite.GetWidth() - this->sprite.GetWidth()) / 2;
		dif.y += (currentRoom->player->sprite.GetHeight() - this->sprite.GetHeight()) / 2;

		const GameSpace::vec2 range(100.0f, 100.0f);
	
		int newDirection = 0;
		float divideValuex = 300.0f;
		float divideValuey = 300.0f;

		//std::cout << currentRoom->player->drawLocf.x << " " << currentRoom->player->drawLocf.y << std::endl;
		//std::cout << this->drawLocf.x << " " << this->changeDrawLoc.y << std::endl;
		
		std::cout << "DIF: " << dif.x << " " << dif.y << std::endl;
		std::cout << "Compared to: " << range.x + range.x * ((int)(dif.y) / divideValuey) << " " << range.y + range.y * ((int)(dif.x) / divideValuex) << std::endl;
		

		if (dif.x < -range.x * ((int)abs(dif.y) / divideValuey))
		{
			if (dif.y < -range.y * ((int)abs(dif.x) / divideValuex))
			{
				newDirection = 5;
			}
			else if (dif.y > range.y * ((int)abs(dif.x) / divideValuex))
			{
				newDirection = 3;
			}
			else
			{
				newDirection = 4;
			}
		}
		else if (dif.x > range.x * ((int)abs(dif.y)  / divideValuey))
		{
			if (dif.y < -range.y * ((int)abs(dif.x)  / divideValuex))
			{
				newDirection = 7;
			}
			else if (dif.y > range.y * ((int)abs(dif.x)  / divideValuex))
			{
				newDirection = 1;
			}
			else
			{
				newDirection = 0;
			}
		}
		else
		{
			if (dif.y < -range.y * ((int)abs(dif.x) / divideValuex))
			{
				newDirection = 6;
			}
			else if (dif.y > range.y * ((int)abs(dif.x) / divideValuex))
			{
				newDirection = 2;
			}
			else
			{
				newDirection = 6;
			}
		}
		newDirection;
		std::cout << newDirection << std::endl;
		//currentSs.freezeFrame(directionFacing, true);
		changeDirection(newDirection);
	}

	void enemy_snowman::triggerFollowPlayer()
	{
		isFollowingPlayer = true;
		EnemyBase::changeActionSprite(0, 0);
	}

	void enemy_snowman::update(float deltaTime)
	{
		//std::cout << "Snowman " << data.type << " " << drawLocf.x << " " << drawLocf.y << std::endl;
		EnemyBase::update(deltaTime);
		drawLocf = locf - currentRoom->locf;
		if (!isFollowingPlayer)
		{
			EnemyBase::findPath(getCurrentPos(newmath::make_ivec2(sprite.GetWidth() / 2, sprite.GetHeight() / 2)), currentRoom->player->getCurrentPos());
			if (path.size() <= 9)
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
			turnToPlayer();
	}
}