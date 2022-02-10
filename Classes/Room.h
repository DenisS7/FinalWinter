#pragma once
#include "../surface.h"
#include "../template.h"
#include "../Classes/newmath.h"
#include <vector>


namespace Character
{
	class Player;
	class EnemyBase;
}

namespace Map 
{



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
		int drawIndex;
		int type;
		int rotate;
		bool colidable;
		std::vector <Character::EnemyBase*> entitiesOnTile;
	};

	std::vector <tile> tiles;
	
	newmath::ivec2 loc, size, offset;
	int roomSize;
	int tilesize = 32;
	int layout[5000] = { 0 };
	int collision[2000] = { 0 };
	int nrdoors = 1;
	int tilesPerRow = 0;
	int nrCollisionTiles = 0;
	int nrPortalTiles = 0;
	int portals[10] = { 0 };
	bool moved = false;
	bool doors[4] = { false };


	int rotatedTiles[50] = { 0 };
	int tileRotation[50] = { 0 };
	int rTilesNr = 0;

	const int Fight = 0;
	const int Rest = 1;
	const int Upgrade = 2;

	const int nonCollide = 0;
	const int collide = 1;
	const int portalInactive = 2;
	const int portalActive = 3;

	Room() 
	{
		//InitiateRoom(0);
		loc.x = loc.y = 0;
		offset.x = offset.y = 0;

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
	void InitiateRoom(int number, const std::vector <int> collisionTiles, const std::vector <int> portalTiles);
	void addToRotatedTiles(int x, int rotation);
	
	void moveMap(int x, int y);
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

