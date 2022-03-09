#pragma once
#include "EnemyBase.h"
#include "newmath.h"
#include "Snowball.h"
#include <vector>

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
    std::vector <Weapon::Snowball*> snowballs;
    const newmath::ivec2 snowballPos[8] = {
        newmath::make_ivec2(20, 25), // down
        newmath::make_ivec2(10, 27), // down left
        newmath::make_ivec2(1, 16), // left
        newmath::make_ivec2(5, 13), // up left
        newmath::make_ivec2(21, -19), // up
        newmath::make_ivec2(30, 13), // up right
        newmath::make_ivec2(41, 16), // right
        newmath::make_ivec2(30, 17) // down right
    };
public:
    enemy_snowman(Map::Room* currentRoom, int entype)
        : EnemyBase(currentRoom, entype)
    {

    }

    ~enemy_snowman() 
    {
      
    }

    void init();
    void changeActionSprite(int x, int newCurrentRow) override;
    void changeDirection(int newDirection) override;
    void turnToPlayer();
    void removeSnowball(Weapon::Snowball* snowballToRemove);
    void attack();
    void triggerFollowPlayer() override;
    void melt();
    
    void update(float deltaTime);

};

}
