#pragma once
#include "../Classes/newmath.h"

class CollisionComponent
{
private:

public:
	const int tile = 0, coltile = 1, player = 2, enemy = 3, weapon = 4;
	newmath::Rect collisionBox;

	void setCollisionBox(const int x, const int y, const int height, const int width);
	int isOverlaping(CollisionComponent actor);
	void setOveralappedTiles();
};
