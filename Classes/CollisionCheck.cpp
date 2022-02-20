#include "CollisionCheck.h"
#include "newmath.h"
#include <vector>
#include "EnemyBase.h"
#include <iostream>
#include "../surface.h"




int CollisionCheck::isOverlapping(CollisionComponent actorCollision, GameSpace::vec2 actorPosition, Map::Room* currentRoom, int damage, GameSpace::Surface* screen)
{
	int collisionType = 0;
	bool isEnemy = false;

	const int nonCollide = 0;
	const int collide = 1;
	const int portalInactive = 2;
	const int portalActive = 3;
	const int enemy = 4;

	const int radius = 1;

	newmath::ivec2 roomPos;

	roomPos.x = (int) actorPosition.x / currentRoom->tilesize + 1;
	roomPos.y = (int) actorPosition.y / currentRoom->tilesize + 1;

	std::vector <int> enemyTiles;

	newmath::ivec2 startPos;

	startPos.x = newmath::clamp(roomPos.x, radius, currentRoom->size.x - radius - 1);
	startPos.y = newmath::clamp(roomPos.y, radius, currentRoom->size.y - radius - 1);

	for (int y = startPos.y - radius; y <= startPos.y + radius; y++)
	{
		for (int x = startPos.x - radius; x <= startPos.x + radius; x++)
		{
			
			
			const int tilepos = x + y * currentRoom->size.x;
			if (currentRoom->tiles[tilepos].colidable)
			{
				
				CollisionComponent tileCol;
				tileCol.collisionBox = newmath::make_Rect(x * 32, y * 32, 32, 32);
				if (areColliding(actorCollision, tileCol))
					collisionType = currentRoom->tiles[tilepos].type;
			}

			if (!currentRoom->tiles[tilepos].entitiesOnTile.empty())
			{
				//std::cout << "Enemies On Tile" << actorCollision.collisionBox.x << " " << actorCollision.collisionBox.y << std::endl;
				//screen->Box(tilepos % 44 * 32 - (int)currentRoom->locf.x, tilepos / 44 * 32 - (int)currentRoom->locf.y, tilepos % 44 * 32 + 32 - (int)currentRoom->locf.x, tilepos / 44 * 32 - (int)currentRoom->locf.y + 32, 0xff0000);
				
				//std::cout << "Enemies On Tile" << std::endl;
				//std::cout << actorCollision.collisionBox.x << " " << actorCollision.collisionBox.y << std::endl;
				//std::cout << currentRoom->tiles[tilepos].entitiesOnTile[0]->data.col.collisionBox.x << " " << currentRoom->tiles[tilepos].entitiesOnTile[0]->data.col.collisionBox.y << std::endl;

				for (int i = 0; i < currentRoom->tiles[tilepos].entitiesOnTile.size(); i++)
					if (areColliding(actorCollision, currentRoom->tiles[tilepos].entitiesOnTile[i]->data.col))
					{
						//std::cout << "ENEMY COLLISION" << std::endl;
						currentRoom->tiles[tilepos].entitiesOnTile[i]->takeDamage(damage);
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

	roomPos.x = (int)player->locf.x / currentRoom->tilesize + 1;
	roomPos.y = (int)player->locf.y / currentRoom->tilesize + 1;

	std::vector <int> enemyTiles;

	newmath::ivec2 startPos;

	startPos.x = newmath::clamp(roomPos.x, radius, currentRoom->size.x - radius - 1);
	startPos.y = newmath::clamp(roomPos.y, radius, currentRoom->size.y - radius - 1);

	for (int y = startPos.y - radius; y <= startPos.y + radius; y++)
	{
		for (int x = startPos.x - radius; x <= startPos.x + radius; x++)
		{
			const int tilepos = x + y * currentRoom->size.x;
			if (currentRoom->tiles[tilepos].colidable)
			{
				CollisionComponent actor2Col;
				actor2Col.collisionBox = newmath::make_Rect(x * 32, y * 32, 32, 32);

				if (areColliding(player->collisionBox, actor2Col))
					collisionType = currentRoom->tiles[tilepos].type;

				if (collisionType == portalActive)
					isPortal = true;
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
