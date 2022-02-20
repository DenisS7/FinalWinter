#pragma once
#include "EnemyBase.h"

namespace Map
{
    class Room;
}

namespace Character
{

class enemy_snowman :
    public EnemyBase
{
private:

public:
    enemy_snowman(Map::Room* currentRoom, int entype)
        : EnemyBase(currentRoom, entype)
    {

    }

    void init();
    void changeDirection(int newDirection) override;
    void turnToPlayer();
    void triggerFollowPlayer() override;
    void melt();
    void attack();
    
    void update(float deltaTime);

};

}
