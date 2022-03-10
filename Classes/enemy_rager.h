#pragma once
#include "EnemyBase.h"
#include "Sprites.h"

namespace Character
{
    class enemy_rager :
        public EnemyBase
    {
    private:
        bool dealDamage = false;
        CollisionComponent* attackCol = new CollisionComponent(0, 4, 82, 50);
    public:
        enemy_rager(Map::Room* currentRoom, int entype)
            : EnemyBase(currentRoom, entype)
        {
            *sprite = *Sprites::get().rager[0];
        }

        ~enemy_rager()
        {
            delete attackCol;
        }

        void init();
        void changeActionSprite(int x, int newCurrentRow) override;
        void attack();
        void changeDirection(int newDirection) override;
        void triggerFollowPlayer() override;
        void addMovement(float deltaTime) override;
        void update(float deltaTime) override;

    };

}
