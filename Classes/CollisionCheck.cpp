#include "CollisionCheck.h"
#include "newmath.h"
#include <vector>
#include "EnemyBase.h"
#include <iostream>
#include "../surface.h"




int CollisionCheck::isOverlapping(CollisionComponent actorCollision, GameSpace::vec2 actorPosition, Map::Room* currentRoom, int damage, int damageType, GameSpace::Surface* screen)
{
	int collisionType = 0;
	bool isEnemy = false;

	

	const int radius = 1;

	newmath::ivec2 roomPos;

	roomPos.x = (int) actorPosition.x / currentRoom->tilesize + 1;
	roomPos.y = (int) actorPosition.y / currentRoom->tilesize + 1;

	std::vector <Character::EnemyBase*> enemiesHit;

	newmath::ivec2 startPos;

	startPos.x = newmath::clamp(roomPos.x, radius, currentRoom->getSize().x - radius - 1);
	startPos.y = newmath::clamp(roomPos.y, radius, currentRoom->getSize().y - radius - 1);



	if (damageType != player)
	{
		
		if (areColliding(actorCollision, currentRoom->getPlayer()->getCollision()))
		{
			currentRoom->getPlayer()->takeDamage(damage);
			return collide;
		}
	}

	for (int y = startPos.y - radius; y <= startPos.y + radius; y++)
	{
		for (int x = startPos.x - radius; x <= startPos.x + radius; x++)
		{
			const int tilepos = x + y * currentRoom->getSize().x;
			if (currentRoom->getTile(tilepos).colidable)
			{
				CollisionComponent tileCol;
				tileCol.collisionBox = newmath::make_Rect(x * 32, y * 32, 32, 32);
				if (areColliding(actorCollision, tileCol))
					collisionType = currentRoom->getTile(tilepos).type;
			}

			if (!currentRoom->getTile(tilepos).entitiesOnTile.empty() && damageType == 5)
			{
				for (int i = 0; i < currentRoom->getTile(tilepos).entitiesOnTile.size(); i++)
					if (areColliding(actorCollision, currentRoom->getTile(tilepos).entitiesOnTile[i]->getData().col) && !std::count(enemiesHit.begin(), enemiesHit.end(), currentRoom->getTile(tilepos).entitiesOnTile[i]))
					{
						currentRoom->getTile(tilepos).entitiesOnTile[i]->takeDamage(damage);
						enemiesHit.push_back(currentRoom->getTile(tilepos).entitiesOnTile[i]);
						isEnemy = true;
					}
			}
		}
	}
	//screen->Clear(0);
	
	if (isEnemy)
		return enemy;
	else return collisionType;

	return 0;
}

int CollisionCheck::isPlayerOverlapping(Character::Player* player, Map::Room* currentRoom)
{
	bool isPortal = false;
	int collisionType = 0;

	const int nonCollide = 0;
	const int collide = 1;
	const int portalInactive = 2;
	const int portalActive = 3;

	const int radius = 3;

	newmath::ivec2 roomPos;

	roomPos.x = (int)player->getLocation().x / currentRoom->tilesize + 1;
	roomPos.y = (int)player->getLocation().y / currentRoom->tilesize + 1;

	std::vector <int> enemyTiles;

	newmath::ivec2 startPos;
	
	bool isEnemy = false;

	startPos.x = newmath::clamp(roomPos.x, radius, currentRoom->getSize().x - radius - 1);
	startPos.y = newmath::clamp(roomPos.y, radius, currentRoom->getSize().y - radius - 1);

	for (int y = startPos.y - radius; y <= startPos.y + radius; y++)
	{
		for (int x = startPos.x - radius; x <= startPos.x + radius; x++)
		{
			const int tilepos = x + y * currentRoom->getSize().x;
			if (currentRoom->getTile(tilepos).colidable)
			{
				CollisionComponent actor2Col;
				actor2Col.collisionBox = newmath::make_Rect(x * 32, y * 32, 32, 32);

				if (areColliding(player->getCollision(), actor2Col))
					collisionType = currentRoom->getTile(tilepos).type;

				if (collisionType == portalActive)
					isPortal = true;
			}
			if (!currentRoom->getTile(tilepos).entitiesOnTile.empty())
			{
				for (int i = 0; i < currentRoom->getTile(tilepos).entitiesOnTile.size(); i++)
					if (areColliding(player->getCollision(), currentRoom->getTile(tilepos).entitiesOnTile[i]->getData().col))
					{
						//std::cout << "ENEMY COLLISION" << std::endl;
						//currentRoom->tiles[tilepos].entitiesOnTile[i]->takeDamage(damage);
						if (currentRoom->getTile(tilepos).entitiesOnTile[i]->getData().type == 1)
							isEnemy = true;
					}
			}
		}
	}

	/*if (areEnemies)
	{
		int damageTaken = 0;
		for (int i = 0; i < enemyTiles.size(); i++)
		{
			newmath::ivec2 playerCentrePos;
			playerCentrePos.x = player->loc.x + 32;
			playerCentrePos.y = player->loc.y + 32;
			for (int j = 0; j < currentRoom->tiles[enemyTiles[i]].entitiesOnTile.size(); j++)
				if (checkEnemyCollision(player->collisionBox, currentRoom->tiles[enemyTiles[i]].entitiesOnTile[j]->collisionBox))
					damageTaken += currentRoom->tiles[enemyTiles[i]].entitiesOnTile[j]->damageOnCollision;
		}
	}*/

	if (isPortal)
		return portalActive;
	if (isEnemy)
		collisionType = 1;
	return collisionType;
}

bool CollisionCheck::areColliding(CollisionComponent actor1, CollisionComponent actor2)
{
	if (actor1.collisionBox.x < actor2.collisionBox.x + actor2.collisionBox.width &&
		actor1.collisionBox.x + actor1.collisionBox.width > actor2.collisionBox.x &&
		actor1.collisionBox.y < actor2.collisionBox.y + actor2.collisionBox.height &&
		actor1.collisionBox.y + actor1.collisionBox.height > actor2.collisionBox.y)
	{
		return true;
	}
	return false;
}
