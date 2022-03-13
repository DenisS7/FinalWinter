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
        *sprite = *Sprites::get().gift[0];
        giftSprite = IRand(4);
        sprite->SetFrame(giftSprite);
        currentSs.freezeFrame(giftSprite, true);
        health = 1;
        potionType = IRand(5);
        col.setCollisionBox(10 + (int)locf.x, 10 + (int)locf.y, 30, 35);
        col.setOffset(3, 4);
    }

    void init() override;
    void open();
    void takeDamage(int damage) override;
    
};

}

