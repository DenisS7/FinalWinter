#include "CollisionComponent.h"

void CollisionComponent::setCollisionBox(const int x, const int y, const int height, const int width)
{
	newmath::setRect(collisionBox, x, y, height, width);
}


