#pragma once
#include "Projectile.h"
#include "newmath.h"
#include "CollisionComponent.h"
#include "../Classes/Room.h"

namespace Weapon
{
class WeaponBase;
class Arrow :
    protected Projectile
{
private:

public:

    const int enemy = 4;

    WeaponBase* crossbow;    
    void drawProjectile(GameSpace::Surface* screen, float deltaTime) override;
    void Init(WeaponBase* newCrossbow);
    void deleteArrow();
    void UpdatePosition(float deltaTime);
};

}
