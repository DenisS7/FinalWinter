#pragma once
#include "CollisionComponent.h"
#include "Room.h"
#include "newmath.h"
#include "Player.h"
#include "EnemyBase.h"
#include "../surface.h"

class CollisionCheck
{
public:
	static int isOverlapping(CollisionComponent actor, int actorType, newmath::ivec2 actorPosition, int direction);
	static int isPlayerOverlapping(Character::Player *player, Map::Room* currentRoom, GameSpace::Surface* screen, int xMove, int yMove);
	static bool checkEnemyCollision(CollisionComponent actor1, CollisionComponent actor2);
};

