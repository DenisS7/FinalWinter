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
		//std::cout << "Snowman Direction Changed" << std::endl;
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
		
		//std::cout << "DIF: " << dif.x << " " << dif.y << std::endl;
		//std::cout << "Compared to: " << range.x + range.x * ((int)(dif.y) / divideValuey) << " " << range.y + range.y * ((int)(dif.x) / divideValuex) << std::endl;
		

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

	void enemy_snowman::triggerFollowPlayer()
	{
		currentSs.freezeFrame(0, false);
		isFollowingPlayer = true;
		//EnemyBase::changeActionSprite(0, 0);
	}

	void enemy_snowman::update(float deltaTime)
	{
		//std::cout << "Snowman " << data.type << " " << drawLocf.x << " " << drawLocf.y << std::endl;
		EnemyBase::update(deltaTime);
		drawLocf = locf - currentRoom->locf;
		if (isDead)
		{
			currentSs.freezeFrame(0, false);
			if (currentState == 3 && currentSs.getCurrentFrame() % 6 == 5)
				die();
			else if (currentState != 3)
			{
				currentState = 3;
				changeActionSprite(3, 0);
				isExploding = false;
				isFollowingPlayer = false;
			}
		}
		else
		{
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
			{
				if (GameSpace::vec2::dist(this->locf, currentRoom->player->locf) < 300 && !isExploding)
				{
					isExploding = true;
					currentState = 2;
					changeActionSprite(2, directionFacing);
				}
				else turnToPlayer();
			}
			if (currentState == 2)
				std::cout << currentSs.getCurrentFrame() << std::endl;
			if (currentState == 2 && (currentSs.getCurrentFrame() % 7) == 6)
			{
				//std::cout << "Stop: " << currentSs.getCurrentFrame() << std::endl;
				isExploding = false;
				currentState = 0;
				changeActionSprite(0, directionFacing);
				turnToPlayer();
			}
		}
	}
}