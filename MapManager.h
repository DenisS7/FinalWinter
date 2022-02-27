#pragma once
#include "../Classes/Room.h"
#include "../template.h"
#include "../Classes/newmath.h"
#include <vector>
#include "../Classes/CollisionComponent.h"


namespace Character
{
	class Player;
	class EnemyBase;
}

namespace Map
{

class MapManager
{
private:
	
	int length;
	
	int nrRooms = 49;
	
	bool exists[100] = { false };
	int p[100];
	int path[100];
	

	int isFirstRoom = 0;
	int nextRooms[50][4] = { 0 };
	int newRooms = 0;

	int goBack = 0;
	int currentGen = 0;

	int aux[100] = { 0 };
	

	bool goingBack = false;

public:
	Character::Player* player;
	int graph[100][100] = { -1 };
	int actualRooms = 0;
	int generatedOrder[100] = { 0 };
	int parentRoom[100] = { 0 };
	const int closedDoor[2] = { 40, 67 };
	const int openDoor[2] = { 164, 191 };

	newmath::ivec2 start, finish, roomAm;

	int nrColTiles, nrPortalTiles;
	std::vector <int> collisionTiles;
	std::vector <int> portalTiles;



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
	} enemyTypes[5];

	const char* enemyPath[5] = {
	"Classes/Enemies/metalbox.txt",
	"Classes/Enemies/snowman.txt",
	"Classes/Enemies/reindeer.txt"
	};

	const int typesOfEnemies = 2;

	GameSpace::Surface* screen;

	Room rooms[100];
	
	void setScreen(GameSpace::Surface* newScreen) { screen = newScreen; };
	void initiate();
	void setPlayer(Character::Player* newPlayer);
	void addToNextRooms(int x, int y, int startingDoor, bool canClose);
	bool canCreateNewRoom(int x, int y);
	
	void initiateEnemiesInRooms();
	void calcNewRoom(int i, int x, int y, bool canClose, bool& generated);
	void calculateRoute(int room);
	void generateFirstRoom();
	void generate(int x, int y, int direction, bool CanClose, int kn);
	void generateNextRooms();
	
	Room* switchRoom(int x, int y);
	void setLength(int n) { length = n; };
	
};

}

