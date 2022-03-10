#pragma once
#include "Spritesheet.h"
#include "../surface.h"
#include "CollisionComponent.h"


namespace Map
{
	class Room;
}
namespace Item
{
	
class ItemBase
{
protected:
	CollisionComponent col;
	GameSpace::Surface* screen;
	GameSpace::vec2 locf = 0, drawLocf = 0;
	GameSpace::Sprite* sprite = new GameSpace::Sprite{ new GameSpace::Surface("assets/Map/gifts.png"), 4};
	Map::Room* currentRoom;
	Spritesheet currentSs{"assets/Map/gifts.png", 1, 4, sprite};
	int type;
	const int gift = 0, potion = 1;
	bool isColidable = false;

private:

public:

	ItemBase(Map::Room* newRoom, int newType, GameSpace::Surface* newScreen)
	{
		type = newType;
		currentRoom = newRoom;
		screen = newScreen;
		if (type == gift)
			isColidable = true;
	}

	CollisionComponent getCollision() { return col; };
	int getType() { return type; };

	void deleteItem();
	virtual void init();
	virtual void takeDamage(int damage);
	virtual void draw(float deltaTime);
	virtual void update(float deltaTime);
	virtual void use();
};

}

