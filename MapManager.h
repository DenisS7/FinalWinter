#pragma once
#include "../Classes/Room.h"
#include "../template.h"
#include "../Classes/newmath.h"
#include <vector>
#include "../Classes/CollisionComponent.h"
#include <iostream>


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
	
	int length = -1;
	
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
	bool goodMap = false;

	const char* enemyPath[5] = {
	"ReadFiles/Enemies/metalbox.txt",
	"ReadFiles/Enemies/snowman.txt",
	"ReadFiles/Enemies/rager.txt",
	"ReadFiles/Enemies/reindeer.txt"
	};

	

	int graph[100][100] = { 0 };
	int generatedOrder[100] = { 0 };
	int parentRoom[100] = { 0 };
	int actualRooms = 0;

	const int typesOfEnemies = 3;
	newmath::ivec2 start, finish, roomAm;
	struct typeEn
	{
		int type = 0;
		int health = 100;
		int damagePerAttack = 0;
		int damageOnCol = 0;
		float speed = 0.2f;
		int points = 0;
		int range = 0;
		CollisionComponent col;
		int spritesheetsNr = 0;
		newmath::spriteData epaths[9];
	} enemyTypes[5];
	int nrColTiles, nrPortalTiles;

public:

	MapManager()
	{
		start = finish = roomAm = newmath::make_ivec2(0, 0);
		nrColTiles = nrPortalTiles = 0;
	}
	Character::Player* player;

	char* potionPath[6] = {
	"assets/Items/heal_potion.png",
	"assets/Items/speed_potion.png",
	"assets/Items/firerate_potion.png",
	"assets/Items/shield_potion.png",
	"assets/Items/damage_potion.png"
	};
	
	
	const int closedDoor[2] = { 40, 67 };
	const int openDoor[2] = { 164, 191 };
	const int finalDoor[2] = { 93, 120 };
	

	
	std::vector <int> collisionTiles;
	std::vector <int> portalTiles;

	GameSpace::Surface* screen;

	Room rooms[50];

	newmath::ivec2 getStart() { return start; };
	int getLength() { return length; };
	int getFinish() { return finish.x + finish.y * roomAm.x; };
	newmath::ivec2 getRoomAm() { return roomAm; };
	typeEn getEnemyType(int type) { return enemyTypes[type]; };
	bool isLastRoom(int roomNumber) { return graph[roomNumber][finish.x + roomAm.x * finish.y]; };


	void restart();

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

