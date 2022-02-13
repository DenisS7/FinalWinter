#include "WeaponBase.h"
#include <algorithm>
#include "Player.h"
#include <iostream>
#include "../template.h"

namespace Weapon
{

	void WeaponBase::Init(GameSpace::vec2 newDrawLocf, Character::Player* newPlayer)
	{
		player = newPlayer;
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

		drawLocf.x = newDrawLocf.x;
		drawLocf.y = newDrawLocf.y;
		
		arrowCol[0] = newmath::make_Rect(27, 23, 22, 12);
		arrowCol[1] = newmath::make_Rect(18, 31, 12, 22);
		arrowCol[2] = newmath::make_Rect(25, 20, 22, 12);
		arrowCol[3] = newmath::make_Rect(23, 31, 12, 22);
		
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

	void WeaponBase::shootArrows()
	{
		Arrow* newArrow = new Arrow;
		newArrow->Init(this);
		arrows.push_back(newArrow);
		//std::cout << "SHOOT ARROW " << arrows.size() << " " << &newArrow << std::endl;
	}

	void WeaponBase::deleteArrow(Arrow* endArrow)
	{	
		/* https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position */
		
		std::vector<Arrow*>::iterator position = std::find(arrows.begin(), arrows.end(), endArrow);
		if (position != arrows.end())
			arrows.erase(position);

	}

	void WeaponBase::Update(float deltaTime)
	{
		sprite.Draw(player->screen, (int) player->drawLocf.x, (int)player->drawLocf.y);
	}

}