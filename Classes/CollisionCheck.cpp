#include "CollisionCheck.h"
#include "newmath.h"
#include <vector>
#include "EnemyBase.h"

int CollisionCheck::isPlayerOverlapping(Character::Player* player, Map::Room* currentRoom)
{
	bool areEnemies = false;
	bool isPortal = false;
	int portalDirection = -1;
	int collisionType = 0;

	int nonCollide = 0;
	int collide = 1;
	int portalInactive = 2;
	int portalActive = 3;
	int enemies = 4;

	const int radius = 1;

	newmath::ivec2 roomPos;
	roomPos.x = (player->collisionBox.collisionBox.x + 18) / currentRoom->tilesize;
	roomPos.y = (player->collisionBox.collisionBox.y + 18) / currentRoom->tilesize;

	std::vector <int> enemyTiles;

	int xoffset = 0;
	int yoffset = 0;

	for (int x = roomPos.x - radius; x <= roomPos.x + radius; x++, xoffset++)
	{
		for (int y = roomPos.y - radius; y <= roomPos.y + radius; y++, yoffset++)
		{
			const int tilepos = x + y * currentRoom->size.x;
			if (currentRoom->tiles[tilepos].type == nonCollide)
			{
				if (!currentRoom->tiles[tilepos].entitiesOnTile.empty())
				{
					areEnemies = true; // another function determines the damage the player takes
					enemyTiles.push_back(tilepos);
				}
			}
			else if (currentRoom->tiles[tilepos].type == collide)
				collisionType = collide;
			else if (currentRoom->tiles[tilepos].type == portalActive)
			{
				isPortal = true;
				if (y >= roomPos.y - 1 && y <= roomPos.y + 1)
				{
					if (x < roomPos.x)
						portalDirection = 1;
					else if (x > roomPos.x)
						portalDirection = 3;
				}
				else if (x >= roomPos.x - 1 && x <= roomPos.x + 1)
				{
					if (y < roomPos.y)
						portalDirection = 0;
					else if (y > roomPos.y)
						portalDirection = 2;
				}
			}
		}
	}
	if (areEnemies)
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
	}

	if (portalDirection == player->directionFacing)
		return portalActive;
	return collisionType;
}

bool CollisionCheck::checkEnemyCollision(CollisionComponent actor1, CollisionComponent actor2)
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
