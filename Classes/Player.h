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

	int points = 0;

public:

	const int nonCollide = 0;
	const int collide = 1;
	const int portalInactive = 2;
	const int portalActive = 3;

	newmath::ivec2 middleScreen;

	GameSpace::vec2 locf, drawLocf;

	CollisionComponent collisionBox;

	float health;
	const int run = 2, idle = 1, dead = 3, runWithGun = 4;
	const int crossbow = 5, snowball = 6, snowman = 7;

	GameSpace::Sprite sprite{new GameSpace::Surface("assets/Player/player_idle.png"), 24};
	Weapon::WeaponBase weapon;

	
	
	newmath::chMove move;

	newmath::spriteData sspaths[10];

	int currentState = 2;
	int directionFacing = 0;
	bool isHoldingGun = false;
	bool isHoldingProjectile = false;

	Spritesheet currentSs{ "assets/Player/player_idle.png", 4, 6, &sprite};
	
	const Uint8* keystate;
	Map::Room* currentRoom;
	Map::MapManager* mapManager;
	GameSpace::Surface* screen;

	void init(GameSpace::Surface* newScreen, Map::Room* newRoom, Map::MapManager* newMapManager, const Uint8* newKeystate);
	void checkIdle();
	newmath::ivec2 Player::getCurrentPos();
	void die();
	void modifyPoints(int newPoints);
	int getPoints() { return points; };
	void takeDamage(float damage);
	void checkDirection(int n);
	void updateMapManager(Map::MapManager* newMapManager);
	void updateScreen(GameSpace::Surface* newScreen);
	void updateRoom(Map::Room* newRoom);
	void updateKeystate(const Uint8* keystate);
	void input(float deltaTime);
	void mouseLoc(int x, int y);
	void moveDown(bool down, float deltaTime);
	void moveLeft(bool left, float deltaTime);
	void moveUp(bool up, float deltaTime);
	void moveRight(bool right, float deltaTime);
	void changeActionSprite(int x); // 1 - idle, 2 - run, 3 - dead
	void addMovement(int x, int y, float deltaTime);
	void equipWeapon(int type);
	void shootProjectile(int type);
	void update(float deltaTime);
	
};

}

