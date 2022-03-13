#pragma once
#include "../surface.h"
#include "../template.h"
#include "../Classes/newmath.h"
#include "../Classes/CollisionComponent.h"
#include "../Classes/ItemBase.h"
#include "../Classes/Gift.h"
#include "../Classes/Potion.h"
#include "../Classes/Campfire.h"
#include "../Classes/Sprites.h"
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

	struct tile
	{
		int drawIndex = 0;
		int type = 0;
		int rotate = 0;
		bool colidable = 0;
		std::vector <Character::EnemyBase*> enemiesOnTile;
	};

	struct decorationTile
	{
		int drawIndex = 0;

	};

	bool reachedEnd;
	int roomNumber = -1;
	int enemies = 0;
	int level = 0;
	int type = 0;
	GameSpace::Surface* tilemap;
	GameSpace::Surface* screen;
	std::vector <tile> decorations;
	int roomSize = 0;
	GameSpace::vec2 locf;
	newmath::ivec2 size, offset, moveDir;
	std::vector <Character::EnemyBase*> enemiesInRoom;
	std::vector <Item::ItemBase*> itemsInRoom;
	Character::Player* player;
	bool isRoomOpen = false;
	int tilesPerRow = 1;

public:
	int nrdoors = 0;

	std::vector <tile> tiles;
	Map::MapManager* manager;

	const int tilesize = 32;
	bool doors[4] = { false };

	const int Fight = 0;
	const int Rest = 1;
	const int Upgrade = 2;

	const int nonCollide = 0;
	const int collide = 1;
	const int portalInactive = 2;
	const int portalActive = 3;
	
	const int tree = 0;
	const int rock = 1;
	const int bush = 2;

	const int gift = 0;
	const int potion = 1;
	const int campfire = 2;

	float speed = 0.3f;

	

	Room() 
	{
		locf.x = locf.y = 0;
		offset.x = offset.y = 0;
		speed = 0.3f;
		enemies = 0;
		//*tilemap = *Sprites::get().tilemap;
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

	std::vector <Character::EnemyBase*> getEnemies() { return enemiesInRoom; };
	bool getIsRoomOpen() { return isRoomOpen; };
	int getRoomNumber() { return roomNumber; };
	newmath::ivec2 getSize() { return size; };
	tile getTile(int tileNr) { return tiles[tileNr]; };
	std::vector <tile> getTileMap() { return tiles; };
	std::vector <Item::ItemBase*> getItems() { return itemsInRoom; };
	void setTileMap(const newmath::ivec2 newSize, const std::vector <tile> newTileMap) { size = newSize; roomSize = size.x * size.y; tiles = newTileMap; };
	GameSpace::vec2 getLocation() { return locf; };
	Character::Player* getPlayer() { return player; };

	void addItem(int type, GameSpace::vec2 locf);
	void removeItem(Item::ItemBase* item);
	void setLocation(const GameSpace::vec2 newLocf) { locf = newLocf; };
	void spawnGifts();
	void readRoomLayout(const std::vector <int> collisionTiles, const std::vector <int> portalTiles);
	void restart();
	void spawnDecorations(int nr, int type);
	void createDecorations();
	void initiateRoom(const int number, MapManager* newManager, GameSpace::Surface* newScreen);
	void inititateEnemies();
	void removeEnemyFromTile(const Character::EnemyBase* enemy, int tileNr);
	void addEnemyToTile(Character::EnemyBase* enemy, int tileNr);
	void enemyOnTiles(Character::EnemyBase* enemy);
	void openPortals();
	void hideEnemy(Character::EnemyBase* enemy);
	void removeEnemy(Character::EnemyBase* enemy);
	void deleteEnemy(Character::EnemyBase* enemy);
	void changeDir();
	void moveMap(int x, int y, float deltaTime);
	void changeDoorLayout(bool isOpen);
	void calculateDoors(int startDoor, bool CanClose);
	void resetDoors();
	int doorNumber();
	void getMap();
	int checkCollision(int x, int y);
	void drawRotatedTile(int tx, int ty, int dx, int dy, int rotate);
	void drawTile(int tx, int ty, int dx, int dy);
	void drawSpriteTile(int tx, int ty, int dx, int dy);
	void drawMap();
	void updateEnemies();
	void updateTiles();
	void drawEnemies(float deltaTime);
	void drawItems(float deltaTime);
	void updateMap(float deltaTime);
};

};

