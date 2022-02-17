#include "enemy_metalbox.h"
#include "Player.h"
#include <iostream>

namespace Character
{
	void enemy_metalbox::Init()
	{
		EnemyBase::Init();
		currentSs.setDirection(0);
		locf.x = drawLocf.x = 250.0f;
		locf.y = drawLocf.y = 250.0f;
		//findPath(tilePos, currentRoom->player->getCurrentPos());
		
	}
	void enemy_metalbox::addMovement(float deltaTime)
	{
		newmath::ivec2 currentPos = getCurrentPos();
		newmath::ivec2 nextPos = *path.begin();
		if (currentPos != nextPos)
		{
			locf.x += (nextPos.x - currentPos.x) * data.speed * deltaTime;
			locf.y += (nextPos.y - currentPos.y) * data.speed * deltaTime;
		
			drawLocf.x = locf.x;
			drawLocf.y = locf.y;
		}
		else
		{
			path.erase(path.begin());
			newmath::ivec2 nextPos = *path.begin();
			locf.x += (nextPos.x - currentPos.x) * data.speed * deltaTime;
			locf.y += (nextPos.y - currentPos.y) * data.speed * deltaTime;
			
			drawLocf.x = locf.x;
			drawLocf.y = locf.y;
		}
	}
	void enemy_metalbox::update(float deltaTime)
	{
		EnemyBase::update(deltaTime);
		currentTimePath += deltaTime;
		if (currentTimePath >= timeUntilPathRefresh)
		{
			findPath(getCurrentPos(), currentRoom->player->getCurrentPos());
			for (int i = 0; i < path.size(); i++)
				std::cout << path[i].x << " " << path[i].y << std::endl;
		}
		addMovement(deltaTime);
	}
}
