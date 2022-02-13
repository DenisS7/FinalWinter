#pragma once
#include "../surface.h"
#include "../template.h"
#include "../Classes/newmath.h"
#include "../Classes/CollisionComponent.h"
#include <vector>


namespace Character
{
	class Player;
	class EnemyBase;
}

namespace Map 
{

class MapManager;
class Room
{
	
private:
	
	bool reachedEnd;
	int enemies;
	
	

public:
	
	GameSpace::Surface tilemap{ "assets/Map/all_map.png" };
	int roomNumber;
	int level;
	int type;

	struct tile
	{
		int drawIndex = 0;
		int type = 0;
		int rotate = 0;
		bool colidable = 0;
		std::vector <Character::EnemyBase*> entitiesOnTile;
	};



	std::vector <tile> tiles;
	std::vector <Character::EnemyBase*> enemiesInRoom;
	
	newmath::ivec2 size, offset;
	GameSpace::vec2 locf;

	Map::MapManager* manager;

	int roomSize;
	int tilesize = 32;

	int nrdoors = 1;
	int tilesPerRow = 0;

	bool moved = false;
	bool doors[4] = { false };


	const int Fight = 0;
	const int Rest = 1;
	const int Upgrade = 2;

	const int nonCollide = 0;
	const int collide = 1;
	const int portalInactive = 2;
	const int portalActive = 3;

	float speed;

	Room() 
	{
		//InitiateRoom(0);
		locf.x = locf.y = 0;
		offset.x = offset.y = 0;
		speed = 0.2f;
		reachedEnd = false;
		enemies = 0;
	}

	tile makeTile(int drawIndex, int type, int rotation, bool colidable) 
	{
		tile newTile;
		newTile.drawIndex = drawIndex;
		newTile.type = type;
		newTile.rotate = rotation;
		newTile.colidable = colidable;
		return newTile;
	}
	void InitiateRoom(int number, const std::vector <int> collisionTiles, const std::vector <int> portalTiles, MapManager* newManager);
	
	void moveMap(int x, int y, float deltaTime);
	void ChangeDoorLayout();
	void CalculateDoors(int startDoor, bool CanClose, int beforeRoom);
	void ResetDoors();
	int DoorNumber();
	void GetMap();
	bool ReachedEnd();
	int CheckCollision(int x, int y);
	void DrawRotatedTile(int tx, int ty, GameSpace::Surface* GameScreen, int dx, int dy, int rotate);
	void DrawTile(int tx, int ty, GameSpace::Surface* GameScreen, int dx, int dy);
	void DrawSpriteTile(int tx, int ty, GameSpace::Surface* GameScreen, int dx, int dy);
	void DrawMap(GameSpace::Surface* GameScreen);
	void UpdateMap(int x, int y);
};

};

