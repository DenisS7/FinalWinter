#include "CollisionCheck.h"
#include "newmath.h"
#include <vector>
#include "EnemyBase.h"
#include <iostream>
#include "../surface.h"

int CollisionCheck::isPlayerOverlapping(Character::Player* player, Map::Room* currentRoom, GameSpace::Surface* screen, int xMove, int yMove)
{
	screen->Clear(0);
	bool isPortal = false;
	int portalDirection = -1;
	int collisionType = 0;

	int nonCollide = 0;
	int collide = 1;
	int portalInactive = 2;
	int portalActive = 3;
	int enemies = 4;

	const int radius = 3;

	newmath::ivec2 roomPos;

	roomPos.x = player->loc.x / currentRoom->tilesize + 1;
	roomPos.y = player->loc.y / currentRoom->tilesize + 1;

	std::vector <int> enemyTiles;

	newmath::ivec2 startPos;

	startPos.x = newmath::clamp(roomPos.x, radius, currentRoom->size.x - radius - 1);
	startPos.y = newmath::clamp(roomPos.y, radius, currentRoom->size.y - radius - 1);

	for (int y = startPos.y - radius; y <= startPos.y + radius; y++)
	{
		for (int x = startPos.x - radius; x <= startPos.x + radius; x++)
		{
			//std::cout << roomPos.x << " " << roomPos.y << " " << x << " " << y << std::endl;
			const int tilepos = x + y * currentRoom->size.x;
			if (currentRoom->tiles[tilepos].type == collide)
			{
				CollisionComponent actor2Col;
				actor2Col.collisionBox = newmath::make_Rect(x * 32, y * 32, 32, 32);
				screen->Box(x * 32 - player->currentRoom->loc.x, y * 32 - player->currentRoom->loc.y, x * 32 + 32 - player->currentRoom->loc.x, y * 32 + 32 - player->currentRoom->loc.y, 0xffffff);
				if(checkEnemyCollision(player->collisionBox, actor2Col))
					collisionType = collide, std::cout << "COLLISION ";
			}
			else if (currentRoom->tiles[tilepos].type == portalActive)
			{
				CollisionComponent actor2Col;
				actor2Col.collisionBox = newmath::make_Rect(x * 32, y * 32, 32, 32);
				screen->Box(x * 32 - player->currentRoom->loc.x, y * 32 - player->currentRoom->loc.y, x * 32 + 32 - player->currentRoom->loc.x, y * 32 + 32 - player->currentRoom->loc.y, 0xffffff);
				if (checkEnemyCollision(player->collisionBox, actor2Col))
					collisionType = collide, std::cout << "Portal", isPortal = true;
			}
			//
			screen->Box(startPos.x * 32 - player->currentRoom->loc.x, startPos.y * 32 - player->currentRoom->loc.y, x * 32 - player->currentRoom->loc.x, y * 32 - player->currentRoom->loc.y, 0xff0000);
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
