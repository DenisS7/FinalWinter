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

void CollisionComponent::extendCollision(const int x, const int y)
{
	collisionBox.x -= x;
	collisionBox.y -= y;
	collisionBox.height += 2 * x;
	collisionBox.width += 2 * y;
}

void CollisionComponent::moveCollision(const int x, const int y)
{
	collisionBox.x += x;
	collisionBox.y += y;
}


