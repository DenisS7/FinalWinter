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
public:

    Arrow(GameSpace::vec2 newLocf, Map::Room* newRoom, int newDirection, WeaponBase* newCrossbow, char* spritePath, newmath::Rect arrowCol) :
        Projectile(newLocf, newRoom)
    {
        crossbow = newCrossbow;
        direction = newDirection;
        sprite.SetFile(new GameSpace::Surface(spritePath), 1, 0);
        collision.collisionBox = newmath::make_Rect((int)locf.x, (int)locf.y, 0, 0) + arrowCol;
        if (direction % 2 == 0)
        {
            move.x = 0;
            move.y = -direction + 1;
        }
        else
        {
            move.x = direction - 2;
            move.y = 0;
        }
    }
    const int enemy = 4;

       
    void drawProjectile(GameSpace::Surface* screen, float deltaTime) override;
    void Init(WeaponBase* newCrossbow);
    void deleteArrow();
    void UpdatePosition(float deltaTime);
};

}
