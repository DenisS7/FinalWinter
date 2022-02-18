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

	EnemyBase(Map::Room* newRoom, int entype)
	{
		currentRoom = newRoom;
		data.type = entype;
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

	float timeUntilPathRefresh = 1000.0f;
	float currentTimePath = 0.0f;

	std::vector <newmath::ivec2> path;
	std::vector <Atile> nextTiles;
	std::vector <Atile> passedTiles;
	Map::Room* currentRoom;
	newmath::ivec2 finish;

	int type;
	GameSpace::Sprite sprite{ new GameSpace::Surface("assets/Enemies/metalgift/metalgift_idle.png"), 1 };
	Spritesheet currentSs{ "assets/Enemies/metalgift/metalgift_idle.png", 1, 1, &sprite };
	GameSpace::vec2 locf, drawLocf;
	newmath::chMove move;
	newmath::ivec2 tilePos;

	virtual void Init();
	newmath::ivec2 getCurrentPos();
	void resetAPath();
	int getClosestTile();
	int getIndex(const std::vector <Atile>& v, newmath::ivec2 pos);
	bool isTileValid(const newmath::ivec2& tilePos);
	void getAdjTile(const Atile& tile, const newmath::ivec2& nextTile);
	void getNeighbours(const Atile& tile);
	std::vector <newmath::ivec2> findPath(newmath::ivec2 start, newmath::ivec2 finish);
	void changeDirection(int newDirection);
	void takeDamage(int damage);
	void die();
	void followPlayer();
	virtual void addMovement(float deltaTime);
	virtual void update(float deltaTime);
};

}

