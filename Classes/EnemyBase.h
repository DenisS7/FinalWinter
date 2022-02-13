#pragma once
#include "../Classes/Spritesheet.h"
#include "../surface.h"
#include "../Classes/newmath.h"
#include "../template.h"
#include "../Classes/CollisionComponent.h"
#include "../Classes/Room.h"
#include "../surface.h"


namespace Map
{
	class Room;
}

namespace Character
{

class EnemyBase
{
private:

public:

	EnemyBase(Map::Room* newRoom)
	{
		currentRoom = newRoom;
	}

	struct typeEn
	{
		int type = 0;
		float health = 100;
		float damagePerAttack = 0;
		float damageOnCol = 0;
		float speed = 0.2;
		CollisionComponent col;
		int spritesheetsNr = 0;
		newmath::spriteData epaths[9];
	} data;

	int type;
	GameSpace::Sprite sprite{ new GameSpace::Surface("assets/Enemies/metalgift/metalgift_idle.png"), 1 };
	Map::Room* currentRoom;
	GameSpace::vec2 loc, drawLoc;

	void Init(int newType);
	void takeDamage(int damage);
	void die();
};

}

