#pragma once
#include "../Classes/newmath.h"


class CollisionComponent
{
private:

public:
	newmath::Rect collisionBox;
	newmath::ivec2 offset;
	
	CollisionComponent() {};
	CollisionComponent(int x, int y, int height, int width)
	{
		collisionBox = newmath::make_Rect(x, y, height, width);
		offset.x = width;
		offset.y = height;
	}
	CollisionComponent(newmath::Rect collision)
	{
		collisionBox = collision;
		offset.x = collision.width;
		offset.y = collision.height;
	}

	void setCollisionBox(const int x, const int y, const int height, const int width);
	void setOffset(const int x, const int y);
	void extendCollision(const int x, const int y);
	void moveCollision(const int x, const int y);
};