#pragma once
#include "EnemyBase.h"

namespace Map
{
    class Room;
}

namespace Character
{

class enemy_metalbox :
    public EnemyBase
{
private: 

public:
    enemy_metalbox(Map::Room* currentRoom, int entype)
        : EnemyBase(currentRoom, entype)
    {
        
    }

    void init();
    void explode();
    void triggerFollowPlayer() override;
    void findApath(newmath::ivec2 start, newmath::ivec2 finish) { EnemyBase::findPath(start, finish); };
    void addMovement(float deltaTime) override;
    void update(float deltaTime) override;
};

}
