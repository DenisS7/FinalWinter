#include "MapManager.h"
#include "Classes/Room.h"
#include "Classes/EnemyBase.h"
#include "Classes/Player.h"
#include <iostream>
#include <fstream>

namespace Map
{
	int k[10] = { 0 };

	void MapManager::restart()
	{
		for (int i = 0; i < roomAm.x * roomAm.y; i++)
		{
			rooms[i].restart();
			generatedOrder[i] = 0;
			parentRoom[i] = 0;
			for (int j = 0; j < roomAm.x * roomAm.y; j++)
				graph[i][j] = 0;
			exists[i] = false;
			aux[i] = 0;
			p[i] = 0;
			path[i] = 0;
			nextRooms[i][0] = nextRooms[i][1] = nextRooms[i][2] = nextRooms[i][3] = 0;
		}
		actualRooms = 0;
		length = 0;
		goBack = 0;
		currentGen = 0;
		goingBack = false;
		newRooms = 0;

		start.x = IRand(roomAm.x);
		start.y = IRand(roomAm.y);

		finish.x = IRand(roomAm.x);
		finish.y = IRand(roomAm.y);

		int dist = newmath::manhattanDist(start, finish);


		if (dist <= 1)
		{
			int ax = newmath::getSign(start.x - finish.x);
			int ay = newmath::getSign(start.y - finish.y);

			start.x += ax * (abs(dist - 1));
			start.y += ay * (abs(dist - 1));

			finish.x -= ax * (abs(dist - 1));
			finish.y -= ay * (abs(dist - 1));

			start.x = newmath::clamp(start.x, 0, roomAm.x - 1);
			start.y = newmath::clamp(start.y, 0, roomAm.y - 1);
			finish.x = newmath::clamp(finish.x, 0, roomAm.x - 1);
			finish.y = newmath::clamp(finish.y, 0, roomAm.y - 1);
		}


		if (start.y == 6)
			start.y = 5;

		rooms[0].readRoomLayout(collisionTiles, portalTiles);
		rooms[0].initiateRoom(0, this, screen);
		for (int i = 0; i < 49; i++)
		{
			rooms[i].setTileMap(rooms[0].getSize(), rooms[0].getTileMap());
			rooms[i].initiateRoom(i, this, screen);
		}
		generateFirstRoom();
		initiateEnemiesInRooms();
	}

	void MapManager::initiate()
	{
		
		std::ifstream fin("ReadFiles/RoomLayout/Collisions.txt");
		fin >> nrColTiles;
		for (int i = 0; i < nrColTiles; i++)
		{
			int x;
			fin >> x;
			collisionTiles.push_back(x);
		}
		fin.close();

		std::ifstream pin("ReadFiles/RoomLayout/Portals.txt");
		pin >> nrPortalTiles;
		for (int i = 0; i < nrPortalTiles; i++)
		{
			int x;
			pin >> x;
			portalTiles.push_back(x);
		}
		pin.close();

		for (int i = 0; i < typesOfEnemies; i++)
		{
			std::ifstream ein(enemyPath[i]);
			ein >> enemyTypes[i].type >> enemyTypes[i].health;
			ein >> enemyTypes[i].damagePerAttack >> enemyTypes[i].damageOnCol >> enemyTypes[i].speed >> enemyTypes[i].points;
			int x, y, h, w;
			ein >> x >> y >> h >> w;
			enemyTypes[i].col.collisionBox = newmath::make_Rect(x, y, h, w);
			ein >> enemyTypes[i].spritesheetsNr;
			for (int j = 0; j < enemyTypes[i].spritesheetsNr; j++)
			{
				ein >> enemyTypes[i].epaths[j].rows;
				ein >> enemyTypes[i].epaths[j].columns;
				ein >> enemyTypes[i].epaths[j].frameTime;
			}
		}

		enemyTypes[0].epaths[0].path = "assets/Enemies/metalgift/metalgift_idle.png";
		enemyTypes[0].epaths[1].path = "assets/Enemies/metalgift/metalgift_run.png";
		enemyTypes[0].epaths[2].path = "assets/Enemies/metalgift/metalgift_explosion.png";

		enemyTypes[1].epaths[0].path = "assets/Enemies/snowman/snowman_turn.png";
		enemyTypes[1].epaths[1].path = "assets/Enemies/snowman/snowman_spawn.png";
		enemyTypes[1].epaths[2].path = "assets/Enemies/snowman/snowman_attack.png";
		enemyTypes[1].epaths[3].path = "assets/Enemies/snowman/snowman_death.png";

		enemyTypes[2].epaths[0].path = "assets/Enemies/rager/rager_idle.png";
		enemyTypes[2].epaths[1].path = "assets/Enemies/rager/rager_move.png";
		enemyTypes[2].epaths[2].path = "assets/Enemies/rager/rager_attack.png";
		enemyTypes[2].epaths[3].path = "assets/Enemies/rager/rager_death.png";


		roomAm.x = 7;
		roomAm.y = 7;

		start.x = IRand(roomAm.x);
		start.y = IRand(roomAm.y);

		finish.x = IRand(roomAm.x);
		finish.y = IRand(roomAm.y);

		

		int dist = newmath::manhattanDist(start, finish);

		if (dist <= 1)
		{
			int ax = newmath::getSign(start.x - finish.x);
			int ay = newmath::getSign(start.y - finish.y);

			start.x += ax * (abs(dist - 1));
			start.y += ay * (abs(dist - 1));

			finish.x -= ax * (abs(dist - 1));
			finish.y -= ay * (abs(dist - 1));

			start.x = newmath::clamp(start.x, 0, roomAm.x - 1);
			start.y = newmath::clamp(start.y, 0, roomAm.y - 1);
			finish.x = newmath::clamp(finish.x, 0, roomAm.x - 1);
			finish.y = newmath::clamp(finish.y, 0, roomAm.y - 1);
		}

		if (start.y == 6)
			start.y = 5;

		rooms[0].readRoomLayout(collisionTiles, portalTiles);
		rooms[0].initiateRoom(0, this, screen);
		for (int i = 0; i < 49; i++)
		{
			rooms[i].setTileMap(rooms[0].getSize(), rooms[0].getTileMap());
			rooms[i].initiateRoom(i, this, screen);
		}
			
	}

	void MapManager::setPlayer(Character::Player* newPlayer)
	{
		player = newPlayer;
	}

	void MapManager::addToNextRooms(int x, int y, int startingDoor, bool canClose)
	{
		nextRooms[newRooms][0] = x;
		nextRooms[newRooms][1] = y;
		nextRooms[newRooms][2] = startingDoor;
		nextRooms[newRooms][3] = canClose;
		exists[x + y * 7] = true;
		newRooms++;
	}

	bool MapManager::canCreateNewRoom(int x, int y)
	{
		if (exists[x + y * roomAm.x]) //the room was already generated
		{
			return false;
		}
		if (x < 0 || x >= roomAm.x || y < 0 || y >= roomAm.y) // not in map bounds
		{
			return false;
		}
		return true;
	}

	void MapManager::initiateEnemiesInRooms()
	{
		std::cout << newRooms << std::endl;
		for (int i = 0; i < roomAm.x * roomAm.y; i++)
			if (i != start.x + start.y * roomAm.x)
				rooms[i].inititateEnemies();
		rooms[start.x + start.y * roomAm.x].openPortals();
	}

	void MapManager::calcNewRoom(int i, int x, int y, bool canClose, bool& generated)
	{
		if (i % 2 == 0)
		{
			if (canCreateNewRoom(x, y - i + 1))
			{
				k[newRooms] = x + y * roomAm.x;

				graph[x + y * roomAm.x][x + (y - i + 1) * roomAm.x] = graph[x + (y - i + 1) * roomAm.x][x + y * roomAm.x] = 1;
				
				parentRoom[x + (y - i + 1) * roomAm.x] = x + y * roomAm.x;
				addToNextRooms(x, y - i + 1, (i + 2) % 4, false);
				generated = true;
			}
			
		}
		else if (i % 2 == 1)
		{
			if (canCreateNewRoom(x + i - 2, y))
			{
				k[newRooms] = x + y * roomAm.x;

				graph[x + y * roomAm.x][x + i - 2 + y * roomAm.x] = graph[x + i - 2 + y * roomAm.x][x + y * roomAm.x] = 1;

				parentRoom[x + i - 2 + y * roomAm.x] = x + y * roomAm.x;
				addToNextRooms(x + i - 2, y, (i + 2) % 4, false);
				generated = true;
			}
		}
	}


	void MapManager::calculateRoute(int room)
	{
		int lf, rt;
		int x = room % roomAm.x;
		int y = room / roomAm.x;
		
		int t[100] = { 0 };
		int q[100] = { 0 };
		t[room] = -1;
		lf = rt = 1;
		q[1] = room;
		
		int dist = 0;

		while (lf <= rt)
		{
			int k = q[lf];
			for (int i = 0; i < roomAm.x * roomAm.y; i++)
			{
				
				if (t[i] == 0 && graph[k][i] == 1)
				{
					t[i] = k + 1;
					q[++rt] = i;
				}
			}

			lf++;
		} 
		int j = finish.x + finish.y * roomAm.x;
		
		while (j != room && dist < roomAm.x * roomAm.y)
		{
			j = t[j] - 1;
			dist++;
		}
	}

	void MapManager::generateFirstRoom()
	{
		exists[start.x + start.y * roomAm.x] = true;
		rooms[start.x + start.y * roomAm.x].calculateDoors(2, true, -1);
		bool possible[4] = { true, true, true, true };
		for (int i = 0; i < 4; i++)
		{
			bool generated = false;
			if (rooms[start.x + start.y * roomAm.x].doors[i])
			{
				calcNewRoom(i, start.x, start.y, false, generated);
				if (!generated)
				{
					rooms[start.x + start.y * roomAm.x].nrdoors--;
					rooms[start.x + start.y * roomAm.x].doors[i] = false;
					possible[i] = false;
					for (int j = 0; j < 4; j++)
					{
						if (!rooms[start.x + start.y * roomAm.x].doors[i] && possible[j])
							calcNewRoom(j, start.x, start.y, false, generated);
						if (generated)
						{
							rooms[start.x + start.y * roomAm.x].nrdoors++;
							rooms[start.x + start.y * roomAm.x].doors[j] = true;
							break;
						}
						else possible[j] = false;
					}
				}
			}
			
		}

		rooms[start.x + start.y * roomAm.x].changeDoorLayout(false);
		
		generatedOrder[0] = start.x + start.y * roomAm.x;

		generateNextRooms();
	}

	void MapManager::generate(int x, int y, int StartDirection, bool CanClose, int kn)
	{
		exists[x + y * roomAm.x] = true;

		rooms[x + y * roomAm.x].calculateDoors(StartDirection, CanClose, kn);
		bool possible[4] = { true, true, true, true };
		for (int i = 0; i < 4; i++)
		{
			bool generated = false;
			if (rooms[x + y * roomAm.x].doors[i] && i != StartDirection)
			{
				calcNewRoom(i, x, y, CanClose, generated);
				if (!generated)
				{
					rooms[x + y * roomAm.x].doors[i] = false;
					possible[i] = false;
					if (!k || !CanClose)
					{
						for (int j = 0; j < 4; j++)
						{
							if (!rooms[start.x + start.y * roomAm.x].doors[i] && possible[j])
								calcNewRoom(j, x, y, CanClose, generated);
							if (generated)
							{
								rooms[x + y * roomAm.x].doors[j] = true;
								break;
							}
							else possible[j] = false;
						}
					}
				}
			}
		}
		rooms[x + y * roomAm.x].changeDoorLayout(false);
		actualRooms++;
		generatedOrder[actualRooms] = x + y * roomAm.x;
	}

	void MapManager::generateNextRooms()
	{		
		aux[goBack] = newRooms;
		
		for (int i = currentGen; i < aux[goBack]; i++)
		{
			generate(nextRooms[i][0], nextRooms[i][1], nextRooms[i][2], nextRooms[i][3], k[i]);
		}
		

		if (newRooms != aux[goBack])
		{
			goingBack = false;
			currentGen = aux[goBack];
			goBack++;
			generateNextRooms();
		}
		
		else if (!exists[finish.x + finish.y * roomAm.x])
		{
			goingBack = true;
			if (goBack > 7)
				restart();
			else if (goBack > 1)
			{
				for (int i = aux[goBack - 2]; i < newRooms; i++)
				{
					exists[nextRooms[i][0] + nextRooms[i][1] * roomAm.x] = false;
					rooms[nextRooms[i][0] + nextRooms[i][1] * roomAm.x].resetDoors();
					//rooms[nextRooms[i][0] + nextRooms[i][1] * roomAm.x].changeDoorsToWalls();
					actualRooms--;
				}
				goBack--;
				currentGen = aux[goBack - 1];
				newRooms = aux[goBack];
				generateNextRooms();
			}
			else if (goBack == 1)
			{
				for (int i = 0; i < newRooms; i++)
				{
					exists[nextRooms[i][0] + nextRooms[i][1] * roomAm.x] = false;
					rooms[nextRooms[i][0] + nextRooms[i][1] * roomAm.x].resetDoors();
					//rooms[nextRooms[i][0] + nextRooms[i][1] * roomAm.x].changeDoorsToWalls();
					actualRooms--;
				}
				goBack--;
				currentGen = 0;
				newRooms = aux[goBack];
				generateNextRooms();
			}
			else
			{
				restart();
			}
			
		}

	}

	Room* MapManager::switchRoom(int x, int y)
	{
		
		calculateRoute(x + y * roomAm.x);
		return &rooms[x + y * roomAm.x];
	}

}