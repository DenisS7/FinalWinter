#pragma once
#include "ItemBase.h"

namespace Item
{
    
class Gift :
    public ItemBase
{
private:
    const int heal = 0, speed = 1, firerate = 2, shield = 3, damage = 4;
    float health = 30;
    int giftSprite = 0;
    int potionType = 0;
public:
    Gift(Map::Room* newRoom, int newType, GameSpace::Surface* newScreen, GameSpace::vec2 newLocf) :
        ItemBase(newRoom, newType, newScreen)
    {
        locf = newLocf;
        giftSprite = IRand(4);
        sprite->SetFrame(giftSprite);
        currentSs.freezeFrame(giftSprite, true);
        health = 30;
        potionType = IRand(5);
        col.setCollisionBox(3 + (int)locf.x, 4 + (int)locf.y, 50, 56);
        col.setOffset(3, 4);
    }

    void init() override;
    void open();
    void takeDamage(int damage) override;
    
};

}

