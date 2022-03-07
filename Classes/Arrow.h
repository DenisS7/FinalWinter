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
    WeaponBase* crossbow;
    GameSpace::vec2 destination, moveDirection;
public:

    Arrow(GameSpace::vec2 newLocf, Map::Room* newRoom, int newDirection, GameSpace::vec2 newDestination, WeaponBase* newCrossbow, char* spritePath, newmath::Rect arrowCol, int newDamage) :
        Projectile(newLocf, newRoom)
    {
        crossbow = newCrossbow;
        direction = newDirection;
        destination = newDestination;
        sprite.SetFile(new GameSpace::Surface(spritePath), 1, 0);
        collision.collisionBox = newmath::make_Rect((int)locf.x, (int)locf.y, 0, 0) + arrowCol;
        moveDirection = GameSpace::vec2::normalize(currentRoom->getLocation() + destination - locf - 32);
        speedf = 0.3f;
        damage = newDamage;
        
    }
    const int enemy = 4;

       
    void drawProjectile(GameSpace::Surface* screen, float deltaTime) override;
    void Init(WeaponBase* newCrossbow);
    void deleteArrow();
    void UpdatePosition(float deltaTime);
};

}
