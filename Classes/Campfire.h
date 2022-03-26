#pragma once
#include "ItemBase.h"

namespace Item
{
    class Campfire :
        public ItemBase
    {
    private:
        CollisionComponent healBox;
        bool isOn = false;
        int healAmount = 10;
        float timer = 0, healRefresh = 500;
    public:
        Campfire(Map::Room* newRoom, int newType, GameSpace::Surface* newScreen, GameSpace::vec2 newLocf) :
            ItemBase(newRoom, newType, newScreen)
        {
            locf = newLocf;
            *sprite = *Sprites::get().campfire[0];
            locf.x -= static_cast<float>(sprite->GetWidth()) / 2;
            locf.y -= static_cast<float>(sprite->GetHeight()) / 2;
            currentSs.changeSpritesheet(1, 1, 0, sprite);
            currentSs.freezeFrame(0, true);
            healBox.setCollisionBox(static_cast<int>(locf.x) - 100, static_cast<int>(locf.y) - 68, 232, 232);
            col.setCollisionBox(static_cast<int>(locf.x) + 10, static_cast<int>(locf.y) + 46, 14, 9);
        }

        int getHealAmount() { return healAmount; };
        CollisionComponent getHealBox() { return healBox; };

        void init() override;
        void turnOn();
        bool heal();
        void update(float deltaTime) override;
    };
}
