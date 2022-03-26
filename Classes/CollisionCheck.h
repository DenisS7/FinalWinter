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
private:
    static const int nonCollide = 0;
    static const int collide = 1;
    static const int portalInactive = 2;
    static const int portalActive = 3;
    static const int enemy = 4;
    static const int player = 5;

public:
    static int isOverlapping(CollisionComponent actorCollision, GameSpace::vec2 actorPosition, Map::Room* currentRoom,
                             int damage, int damageType, GameSpace::Surface* screen);
    static int isPlayerOverlapping(Character::Player* player, Map::Room* currentRoom);
    static void campfireHeal(Character::Player* player, Map::Room* currentRoom);
    static bool areColliding(CollisionComponent actor1, CollisionComponent actor2);
};
