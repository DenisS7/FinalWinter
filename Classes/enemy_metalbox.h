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

    void Init();
    void findApath(newmath::ivec2 start, newmath::ivec2 finish) { EnemyBase::findPath(start, finish); };
    void followPlayer();
    void addMovement(float deltaTime);
    void update(float deltaTime) override;
};

}
