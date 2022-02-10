#include "WeaponBase.h"

namespace Weapon
{

	void WeaponBase::Init(newmath::ivec2 newDrawLoc)
	{
		wpaths[1].path = "assets/Weapons/crossbow_down.png";
		wpaths[2].path = "assets/Weapons/crossbow_left.png";
		wpaths[3].path = "assets/Weapons/crossbow_up.png";
		wpaths[4].path = "assets/Weapons/crossbow_right.png";

		wpaths[5].path = "assets/Weapons/arrow_down.png";
		wpaths[6].path = "assets/Weapons/arrow_left.png";
		wpaths[7].path = "assets/Weapons/arrow_up.png";
		wpaths[8].path = "assets/Weapons/arrow_right.png";

		wpaths[5].frameTime = wpaths[6].frameTime = wpaths[7].frameTime = wpaths[8].frameTime = 30.0f;

		weaponType = 5;

		drawLoc.x = newDrawLoc.x;
		drawLoc.y = newDrawLoc.y;


	}

	void WeaponBase::changeDirection(int direction)
	{
		directionFacing = direction - 1;
		sprite.SetFile(new GameSpace::Surface(wpaths[direction + 1].path), 1, 0);
	}





	void WeaponBase::changeVisibility(bool newVisible)
	{
		visible = newVisible;

	}

	void WeaponBase::shootArrows(int x, int y)
	{
		
	}

	void Update(float deltaTime)
	{

	}

}