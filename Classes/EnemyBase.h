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
protected:
	struct typeEn
	{
		int type = 0;
		float health = 100;
		float damagePerAttack = 0;
		float damageOnCol = 0;
		float speed = 0.2f;
		int points = 0;
		CollisionComponent col;
		int spritesheetsNr = 0;
		newmath::spriteData epaths[9];
	} data;

	struct Atile
	{
		bool visited = false;

		newmath::ivec2 position;
		int g = INT_MAX;
		int h = INT_MAX;
		int f = INT_MAX;
		Atile()
		{
			f = INT_MAX;
			g = INT_MAX;
			h = INT_MAX;
		}
		Atile(newmath::ivec2 newPosition, int ng)
		{
			position = newPosition;
			g = ng;
		}
	};

	Atile parents[1200];
	bool visited[1200] = { false };

	GameSpace::Surface* screen;
	const float timeUntilPathRefresh = 1000.0f;
	float currentTimePath = 0.0f;

	bool isFollowingPlayer = false;
	bool isAttacking = false;
	bool isDead = false;
	
	std::vector <newmath::ivec2> path;
	std::vector <Atile> nextTiles;
	std::vector <Atile> passedTiles;

private:

public:

	EnemyBase(Map::Room* newRoom, int entype)
	{
		currentRoom = newRoom;
		data.type = entype;
		finish = newmath::make_ivec2(0, 0);
		
		locf = drawLocf = 0;
	}

	~EnemyBase()
	{
		
	}

	
	newmath::ivec2 initOcupTile{ -1, -1 }, finOcupTile{ -1, -1 };
	Map::Room* currentRoom;
	newmath::ivec2 finish;

	int type = -1;
	int currentState = 0;
	int directionFacing = 0;

	GameSpace::Sprite sprite{ new GameSpace::Surface("assets/Enemies/metalgift/metalgift_idle.png"), 1 };
	Spritesheet currentSs{ "assets/Enemies/metalgift/metalgift_idle.png", 1, 1, &sprite };
	GameSpace::vec2 locf = 0, drawLocf = 0;
	newmath::chMove move;
	newmath::ivec2 tilePos;

	typeEn getData() { return data; };

	newmath::ivec2 getCurrentPos(newmath::ivec2 posToGet);
	virtual void init(int type);
	void changeActionSprite(int x, int newCurrentRow);
	virtual void triggerFollowPlayer();
	void changeDrawLoc();
	void resetAPath();
	int getClosestTile();
	int getIndex(const std::vector <Atile>& v, newmath::ivec2 pos);
	bool isTileValid(const newmath::ivec2& tilePos);
	void getAdjTile(const Atile& tile, const newmath::ivec2& nextTile);
	void getNeighbours(const Atile& tile);
	std::vector <newmath::ivec2> findPath(newmath::ivec2 start, newmath::ivec2 finish);
	virtual void changeDirection(int newDirection);
	void takeDamage(int damage);
	void die();
	void followPlayer();
	void drawEnemy(float deltaTime);
	virtual void addMovement(float deltaTime);
	virtual void update(float deltaTime);
};

}

