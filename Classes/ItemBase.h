#pragma once
#include "Spritesheet.h"
#include "../surface.h"
#include "Sprites.h"
#include "CollisionComponent.h"


namespace Map
{
    class Room;
}

namespace Item
{
    class ItemBase
    {
    protected:
        CollisionComponent col;
        GameSpace::Surface* screen;
        GameSpace::vec2 locf = 0, drawLocf = 0;
        GameSpace::Sprite* sprite = new GameSpace::Sprite();
        Map::Room* currentRoom;
        Spritesheet currentSs{1, 4, sprite};
        int type;
        const int gift = 0, potion = 1, campfire = 2;
        bool isColidable = false;

    private:
    public:
        ItemBase(Map::Room* newRoom, int newType, GameSpace::Surface* newScreen)
        {
            type = newType;
            *sprite = *Sprites::get().potion[type];
            currentRoom = newRoom;
            screen = newScreen;
            if (type == gift)
                isColidable = true;
        }

        ~ItemBase()
        {
            sprite = nullptr;
            delete sprite;
        }

        CollisionComponent getCollision() { return col; };
        int getType() { return type; };

        void deleteItem();
        virtual void init();
        virtual void takeDamage(int damage);
        virtual void draw(float deltaTime);
        virtual void update(float deltaTime);
        virtual void use();
    };
}
