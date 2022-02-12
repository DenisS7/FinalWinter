#include "CollisionComponent.h"

void CollisionComponent::setCollisionBox(const int x, const int y, const int height, const int width)
{
	collisionBox = newmath::make_Rect(x, y, height, width);
}

void CollisionComponent::setOffset(const int x, const int y)
{
	offset.x = x;
	offset.y = y;
}


