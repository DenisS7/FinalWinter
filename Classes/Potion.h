#pragma once
#include "ItemBase.h"


namespace Item
{
class Potion :
    public ItemBase
{
private:
    int type = 0;
    const int healing = 0, speed = 1, firerate = 2, shield = 3, damage = 4;
public:
    Potion(Map::Room* newRoom, int newType, GameSpace::Surface* newScreen, int potionType, GameSpace::vec2 newLocf) :
        ItemBase(newRoom, newType, newScreen)
    {
        locf = newLocf;
        col.setCollisionBox(13 + (int)locf.x, 25 + (int)locf.y, 35, 43);
        col.setOffset(6, 9);
        type = potionType;
        currentSs.setFrameTime(100.0f);
    }

    void init() override;
    void use() override;
};

}

