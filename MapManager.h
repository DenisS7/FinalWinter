#pragma once
#include "../Classes/Room.h"
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

	newmath::ivec2 start, finish, roomAm;

	int nrColTiles, nrPortalTiles;
	std::vector <int> collisionTiles;
	std::vector <int> portalTiles;



	Room rooms[100];
	void Initiate();
	void addToNextRooms(int x, int y, int startingDoor, bool canClose);
	bool CanCreateNewRoom(int x, int y);
	void setPlayer(Character::Player* newPlayer) { player = newPlayer; };
	void calcNewRoom(int i, int x, int y, bool canClose, bool& generated);
	void CalculateRoute(int room);
	void GenerateFirstRoom();
	void Generate(int x, int y, int direction, bool CanClose, int kn);
	void GenerateNextRooms();
	
	Room* SwitchRoom(int x, int y);
	void SetLength(int n) { length = n; };
	
};

}

