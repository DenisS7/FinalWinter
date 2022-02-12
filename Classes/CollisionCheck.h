#pragma once
#include "CollisionComponent.h"
#include "Room.h"
#include "newmath.h"
#include "Player.h"
#include "EnemyBase.h"
#include "../surface.h"
#include "../template.h"

class CollisionCheck
{
public:

	static int isOverlapping(CollisionComponent actorCollision, GameSpace::vec2 actorPosition, Map::Room* currentRoom, int damage, GameSpace::Surface* screen);
	static int isPlayerOverlapping(Character::Player *player, Map::Room* currentRoom);
	static bool areColliding(CollisionComponent actor1, CollisionComponent actor2);

};

