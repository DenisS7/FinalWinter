#pragma once
#include "EnemyBase.h"

namespace Character
{
    class enemy_rager :
        public EnemyBase
    {
    private:

    public:
        enemy_rager(Map::Room* currentRoom, int entype)
            : EnemyBase(currentRoom, entype)
        {

        }

        void init();
        void attack();
        void changeDirection(int newDirection) override;
        void triggerFollowPlayer() override;
        void addMovement(float deltaTime) override;
        void update(float deltaTime) override;

    };

}
