#pragma once
#include "../surface.h"
#include "Spritesheet.h"
#include "Room.h"
#include "../MapManager.h"
#include "SDL.h"
#include "../Classes/newmath.h"
#include "../Classes/WeaponBase.h"
#include "../Classes/CollisionComponent.h"
#include "Healthbar.h"
#include "Score.h"
#include "Sprites.h"
#include <fstream>
#include "IceExplosion.h"

namespace Character
{
class Surface;
class Sprite;
class Player
{
private:

	int healthBase = 0, arrowDamageBase = 0;
	float speedBase = 0, firerateBase = 0;
	newmath::spriteData sspaths[5];
	Healthbar healthbar;
	Score score;
	int points = 0;
	newmath::ivec2 middleScreen = newmath::make_ivec2(0, 0);
	GameSpace::vec2 locf = 0, drawLocf = 0, mousePosition = 0;
	CollisionComponent collisionBox;
	bool isDead = false;
	bool won = false;
	int health = 100;
	float arrowFirerate = 0;
	
	newmath::chMove move;
	Weapon::WeaponBase weapon;
	std::vector <Weapon::IceExplosion*> attacks;
	GameSpace::Sprite* sprite = new GameSpace::Sprite(new GameSpace::Surface("assets/Player/player_idle.png"), 24);
	GameSpace::Sprite shieldSprite{ new GameSpace::Surface("assets/Weapons/IceShield.png"), 22 };
	
	int currentState = 0;
	int directionFacing = 0;
	const Uint8* keystate;
	bool isHoldingGun = false;
	int spritesheetsNr = 0;
	Spritesheet currentSs{ 4, 6, sprite };
	Spritesheet shieldSs{ 2, 11, &shieldSprite };

	const int healing = 0, speed = 1, firerate = 2, shield = 3, damage = 4;
	int healAdd = 0, damageAdd = 0;
	float speedAdd = 0, firerateAdd = 0;
	float potionTimers[5] = { 0 };
	int isShieldCreating = 0;
	float explosionTimeElapsed = 0, explosionTimer = 500.0f;
	
	std::vector <Weapon::IceExplosion*> explosions;

public:

	Player()
	{
		//sspaths[1].path = "assets/Player/player_idle.png";

		std::ifstream fin("ReadFiles/Player/player.txt");

		fin >> healthBase >> arrowDamageBase >> speedBase >> firerateBase;
		
		health = healthBase;
		move.speed = speedBase;
		arrowFirerate = firerateBase;

		int x, y, h, w;

		fin >> x >> y >> h >> w;

		collisionBox.setOffset(x, y);
		collisionBox.setCollisionBox(x, y, h, w);

		fin >> spritesheetsNr;

		for (int i = 0; i < spritesheetsNr; i++)
			fin >> sspaths[i].rows >> sspaths[i].columns >> sspaths[i].frameTime;
		
		fin >> healAdd >> speedAdd >> firerateAdd >> damageAdd;

		*sprite = *Sprites::get().player[0];

		shieldSs.freezeFrame(0, true);
		shieldSs.changeVisiblity(false);
		shieldSs.setFrameTime(100.0f);
	}
	
	~Player()
	{
		delete sprite;
		delete currentRoom;
		delete mapManager;
		delete screen;
		delete keystate;
	}


	const int nonCollide = 0;
	const int collide = 1;
	const int portalInactive = 2;
	const int portalActive = 3;

	const int idle = 0, run = 1, dead = 2, runWithGun = 3;
	const int crossbow = 5, snowball = 6, snowman = 7;

	Map::Room* currentRoom;
	Map::MapManager* mapManager;
	GameSpace::Surface* screen;
	
	GameSpace::vec2 getMousePosition() { return mousePosition; };
	GameSpace::vec2 getLocation() { return locf; };
	GameSpace::vec2 getDrawLocation() { return drawLocf; };
	int getDirectionFacing() { return directionFacing; };
	int getCurrentFrame() { return currentSs.getCurrentFrame(); };
	CollisionComponent getCollision() { return collisionBox; };
	bool getDead() { return isDead; };
	bool getWon() { return won; };
	bool getHoldingGun() { return isHoldingGun; };
	bool isPotionUsed(int potion) { if (potionTimers[potion]) return true; return false; }
	newmath::chMove getMove() { return move; };
	newmath::ivec2 getSpriteSize() { return newmath::make_ivec2(sprite->GetWidth(), sprite->GetHeight()); };
	int getHealth() { return health; };
	int getScore() { return points; };

	void restart();
	void init(GameSpace::Surface* newScreen, Map::Room* newRoom, Map::MapManager* newMapManager, const Uint8* newKeystate);
	void checkIdle();
	newmath::ivec2 Player::getCurrentPos();
	void speedBoost();
	void damageBoost();
	void firerateBoost();
	void createShield();
	void checkPotions(float deltaTime);
	void die();
	void modifyPoints(int newPoints);
	
	void takeDamage(int damage);
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
	void shootProjectile(int type, int mousex, int mousey);
	void deleteExplosion(Weapon::IceExplosion* attack);
	void iceExplosion(int x, int y);
	void drawUI();
	void drawPausePlayer(float deltaTime);
	void update(float deltaTime);
	
};

}

