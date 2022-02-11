#pragma once
#include "../surface.h"
#include "Spritesheet.h"
#include "Room.h"
#include "../MapManager.h"
#include "SDL.h"
#include "../Classes/newmath.h"
#include "../Classes/WeaponBase.h"
#include "../Classes/CollisionComponent.h"




namespace Character
{
class Surface;
class Sprite;
class Player
{
private:


public:

	newmath::ivec2 loc, drawloc, sign, middleScreen;
	CollisionComponent collisionBox;

	int health;
	const int run = 2, idle = 1, dead = 3, runWithGun = 4;
	const int crossbow = 5, snowball = 6, snowman = 7;

	GameSpace::Sprite sprite{new GameSpace::Surface("assets/Player/player_idle.png"), 24};
	Weapon::WeaponBase weapon;

	struct chMove
	{
		bool direction[4] = { 0 };
		bool down = false, left = false, up = false, right = false;
		bool side[4] = { 0 };
		int speed = 1;
	} move;

	newmath::spriteData sspaths[10];

	int currentState = 2;
	int directionFacing = 0;
	bool isHoldingGun = false;

	Spritesheet currentSs{ "assets/Player/player_idle.png", 4, 6, &sprite};
	

	Map::Room* currentRoom;
	Map::MapManager* mapManager;
	GameSpace::Surface* screen;

	void Init(GameSpace::Surface* newScreen, Map::Room* newRoom, Map::MapManager* newMapManager);
	void checkIdle();
	void checkDirection(int n);
	void updateMapManager(Map::MapManager* newMapManager);
	void updateScreen(GameSpace::Surface* newScreen);
	void updateRoom(Map::Room* newRoom);
	void moveDown(bool down);
	void moveLeft(bool left);
	void moveUp(bool up);
	void moveRight(bool right);
	void changeActionSprite(int x); // 1 - idle, 2 - run, 3 - dead
	void InputDown(int key);
	void InputUp(int key);
	void addMovement(int x, int y);
	void drawPlayer();
	void equipWeapon(int type);
	void Update(float deltaTime);
	
};

}

