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
    int explosionRange = 40;
    bool exploded = false;
public:
    enemy_metalbox(Map::Room* currentRoom, int entype)
        : EnemyBase(currentRoom, entype)
    {
        
    }

    ~enemy_metalbox()
    {

    }

    void init();
    void changeActionSprite(int x, int newCurrentRow) override;
    void explode();
    void triggerFollowPlayer() override;
    void findApath(newmath::ivec2 start, newmath::ivec2 finish) { EnemyBase::findPath(start, finish, currentRoom); };
    void addMovement(float deltaTime) override;
    void update(float deltaTime) override;
};

}
