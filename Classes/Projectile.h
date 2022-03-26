#pragma once
#include "newmath.h"
#include "../surface.h"
#include "../template.h"
#include "Room.h"
#include "Spritesheet.h"
#include "Sprites.h"
#include "CollisionComponent.h"

namespace Weapon
{
    class Projectile
    {
    protected:
        CollisionComponent collision;
        Map::Room* currentRoom;
        newmath::ivec2 move;
        GameSpace::vec2 locf, drawLocf, initialPosf;
        float speedf = 0.25f;
        int direction, damage, speed;
        GameSpace::Sprite* sprite = new GameSpace::Sprite{};

        Spritesheet currentSs{1, 4, sprite};

        bool isExploding = false;
        float timeToExplode = 3000.0f;
        float timePassed = 0.0f;

        newmath::spriteData ppaths[6];
    private:
    public:
        Projectile(GameSpace::vec2 newLocf, Map::Room* newRoom)
        {
            locf = newLocf;
            currentRoom = newRoom;
            drawLocf = newLocf - newRoom->getLocation();
        }

        virtual ~Projectile()
        {
            sprite = nullptr;
            delete sprite;
        }

        virtual void drawProjectile(GameSpace::Surface* screen, float deltaTime);
        virtual void Init();
        virtual void Spawn(newmath::ivec2 newLoc, newmath::ivec2 newDrawLoc, int newDirection);
        virtual void deleteProjectile();
        virtual void Move(float deltaTime);
        void checkCollision();
    };
}
