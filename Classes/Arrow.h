#pragma once
#include "Projectile.h"
#include "newmath.h"
#include "CollisionComponent.h"
#include "../Classes/Room.h"

namespace Weapon
{
class WeaponBase;
class Arrow :
    private Projectile
{
private:

public:


    
    const int enemy = 4;

    WeaponBase* crossbow;
    Map::Room* currentRoom;
    CollisionComponent collision;
    
    int direction;

    void Init(WeaponBase* newCrossbow);
    void UpdatePosition(float deltaTime);
};

}
