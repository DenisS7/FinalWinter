#include "Projectile.h"
#include "../Classes/newmath.h"

namespace Weapon
{

	void Projectile::Init()
	{
	}

	void Projectile::Spawn(newmath::ivec2 newLoc, newmath::ivec2 newDrawLoc, int newDirection)
	{
		
		
		direction = newDirection;

		Init();
	}

	void Projectile::Move(float deltaTime)
	{

	}

	
}