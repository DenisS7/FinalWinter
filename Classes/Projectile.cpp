#include "Projectile.h"
#include "../Classes/newmath.h"

namespace Weapon
{
	void Projectile::drawProjectile(GameSpace::Surface* screen,float deltaTime)
	{
		currentSs.drawNextSprite(deltaTime, screen, drawLocf);
	}

	void Projectile::Init()
	{

	}

	void Projectile::Spawn(newmath::ivec2 newLoc, newmath::ivec2 newDrawLoc, int newDirection)
	{
		direction = newDirection;
		Init();
	}

	void Projectile::deleteProjectile()
	{
	}

	void Projectile::Move(float deltaTime)
	{

	}

	
}