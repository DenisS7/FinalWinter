#pragma once
#include "EnemyBase.h"


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

        }

        ~enemy_rager()
        {
            delete attackCol;
        }

        void init();
        void attack();
        void changeDirection(int newDirection) override;
        void triggerFollowPlayer() override;
        void addMovement(float deltaTime) override;
        void update(float deltaTime) override;

    };

}
