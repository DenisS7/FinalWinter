#pragma once
#include "../Classes/newmath.h"
#include "../Classes/Room.h"

class CollisionComponent
{
private:

public:
	const int tile = 0, coltile = 1, player = 2, enemy = 3, weapon = 4;
	newmath::Rect collisionBox;
	newmath::ivec2 offset;
	
	void setCollisionBox(const int x, const int y, const int height, const int width);
	void setOffset(const int x, const int y);
};