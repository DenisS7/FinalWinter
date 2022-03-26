#pragma once
#include "../Classes/newmath.h"


class CollisionComponent
{
private:
public:
    newmath::Rect collisionBox;
    newmath::ivec2 offset;
    newmath::ivec2 size;

    CollisionComponent()
    {
    };

    CollisionComponent(int x, int y, int height, int width)
    {
        size.x = width;
        size.y = height;
        collisionBox = newmath::make_Rect(x, y, height, width);
        offset.x = width;
        offset.y = height;
    }

    CollisionComponent(newmath::Rect collision)
    {
        size.x = collision.x;
        size.y = collision.y;
        collisionBox = collision;
        offset.x = collision.width;
        offset.y = collision.height;
    }

    void setCollisionBox(int x, int y, int height, int width);
    void setOffset(int x, int y);
    void setSize(int x, int y);
    void extendCollision(int x, int y);
    void moveCollision(int x, int y);
};
