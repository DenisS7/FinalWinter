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


		if (dist <= 2)
		{
			int ax = newmath::getSign(start.x - finish.x);
			int ay = newmath::getSign(start.y - finish.y);

			start.x += ax * (abs(dist - 2));
			start.y += ay * (abs(dist - 2));

			finish.x -= ax * (abs(dist - 2));
			finish.y -= ay * (abs(dist - 2));

			start.x = newmath::clamp(start.x, 0, roomAm.x - 2);
			start.y = newmath::clamp(start.y, 0, roomAm.y - 2);
			
			finish.x = newmath::clamp(finish.x, 0, roomAm.x - 2);
			finish.y = newmath::clamp(finish.y, 0, roomAm.y - 2);

		}


		if (start.y == 6)
		{
			start.y = 5, finish.y--;
			finish.y = newmath::clamp(finish.y, 0, roomAm.y - 2);
		}
		std::cout << std::endl << start.x + start.y * roomAm.x + 1 << std::endl;


		rooms[0].readRoomLayout(collisionTiles, portalTiles);
		rooms[0].initiateRoom(0, this, screen);
		for (int i = 0; i < 49; i++)
		{
			rooms[i].setTileMap(rooms[0].getSize(), rooms[0].getTileMap());
			rooms[i].initiateRoom(i, this, screen);
		}

		generateFirstRoom();
		if (goodMap)
		{
			initiateEnemiesInRooms();
			//std::cout << start.x + start.y * roomAm.x << "\n \n \n";
			for (int i = 0; i < 49; i++)
			{
				std::cout << i + 1 << " " << rooms[i].nrdoors << " " << rooms[i].doors[0] << " " << rooms[i].doors[1] << " " << rooms[i].doors[2] << " " << rooms[i].doors[3] << std::endl;
			}
		}
		else restart();
	}

	void MapManager::initiate()
	{

		roomAm.x = 7;
		roomAm.y = 7;

		start.x = IRand(roomAm.x);
		start.y = IRand(roomAm.y);

		finish.x = IRand(roomAm.x);
		finish.y = IRand(roomAm.y);

		int dist = newmath::manhattanDist(start, finish);

		if (dist <= 2)
		{
			int ax = newmath::getSign(start.x - finish.x);
			int ay = newmath::getSign(start.y - finish.y);

			start.x += ax * (abs(dist - 2));
			start.y += ay * (abs(dist - 2));

			finish.x -= ax * (abs(dist - 2));
			finish.y -= ay * (abs(dist - 2));

			start.x = newmath::clamp(start.x, 0, roomAm.x - 2);
			start.y = newmath::clamp(start.y, 0, roomAm.y - 2);
			finish.x = newmath::clamp(finish.x, 0, roomAm.x - 2);
			finish.y = newmath::clamp(finish.y, 0, roomAm.y - 2);
		}

		if (start.y == 6)
			start.y = 5;

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
			ein >> enemyTypes[i].damagePerAttack >> enemyTypes[i].damageOnCol >> enemyTypes[i].speed >> enemyTypes[i].points >> enemyTypes[i].range;
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
		rooms[0].readRoomLayout(collisionTiles, portalTiles);
		rooms[0].initiateRoom(0, this, screen);

		for (int i = 0; i < 49; i++)
		{
			rooms[i].setTileMap(rooms[0].getSize(), rooms[0].getTileMap());
			rooms[i].initiateRoom(i, this, screen);
		}

		generateFirstRoom();

		if (goodMap)
		{
			initiateEnemiesInRooms();
			std::cout << start.x + start.y * roomAm.x << "\n \n \n";
			for (int i = 0; i < 49; i++)
			{
				std::cout << i + 1 << " " << exists[i] << " " << rooms[i].nrdoors << " " << rooms[i].doors[0] << " " << rooms[i].doors[1] << " " << rooms[i].doors[2] << " " << rooms[i].doors[3] << std::endl;
			}
		}
		else restart();
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
		exists[x + y * roomAm.x] = true;
		newRooms++;
	}

	bool MapManager::canCreateNewRoom(int x, int y)
	{
		if (x < 0 || x >= roomAm.x || y < 0 || y >= roomAm.y) // not in map bounds
		{
			return false;
		}
		return true;
	}

	void MapManager::initiateEnemiesInRooms()
	{
		for (int i = 0; i < roomAm.x * roomAm.y; i++)
			if (i != start.x + start.y * roomAm.x)
				rooms[i].inititateEnemies();
		rooms[start.x + start.y * roomAm.x].openPortals();
	}

	void MapManager::calcNewRoom(int i, int x, int y, bool canClose, bool& generated, bool& usedExistingRoom)
	{
		const int useExistingChance = 2, generatedChance = 2;
		if (i % 2 == 0)
		{
			if (canCreateNewRoom(x, y - i + 1))
			{
				if (exists[x + (y - i + 1) * roomAm.x]) //the room was already generated
				{
					if (!IRand(useExistingChance) && !graph[x + y * roomAm.x][x + (y - i + 1) * roomAm.x])
					{
						rooms[x + (y - i + 1) * roomAm.x].nrdoors++;
						rooms[x + (y - i + 1) * roomAm.x].doors[(i + 2) % 4] = true;
						rooms[x + (y - i + 1) * roomAm.x].changeDoorLayout(false);
						if (!IRand(generatedChance))
							generated = true;
						graph[x + y * roomAm.x][x + (y - i + 1) * roomAm.x] = graph[x + (y - i + 1) * roomAm.x][x + y * roomAm.x] = 1;
						usedExistingRoom = true;
					}
				}
				else
				{
					k[newRooms] = x + y * roomAm.x;

					graph[x + y * roomAm.x][x + (y - i + 1) * roomAm.x] = graph[x + (y - i + 1) * roomAm.x][x + y * roomAm.x] = 1;

					parentRoom[x + (y - i + 1) * roomAm.x] = x + y * roomAm.x;
					addToNextRooms(x, y - i + 1, (i + 2) % 4, false);
					generated = true;
					usedExistingRoom = false;
				}
			}
			
		}
		else if (i % 2 == 1)
		{
			if (canCreateNewRoom(x + i - 2, y))
			{
				if (exists[x + i - 2 + y * roomAm.x]) //the room was already generated
				{
					if (!IRand(useExistingChance) && !graph[x + y * roomAm.x][x + i - 2 + y * roomAm.x])
					{
						rooms[x + i - 2 + y * roomAm.x].nrdoors++;
						rooms[x + i - 2 + y * roomAm.x].doors[(i + 2) % 4] = true;
						rooms[x + i - 2 + y * roomAm.x].changeDoorLayout(false);
						if(!IRand(generatedChance))
							generated = true;
						graph[x + y * roomAm.x][x + i - 2 + y * roomAm.x] = graph[x + i - 2 + y * roomAm.x][x + y * roomAm.x] = 1;
						usedExistingRoom = true;
					}
				}
				else
				{
					k[newRooms] = x + y * roomAm.x;

					graph[x + y * roomAm.x][x + i - 2 + y * roomAm.x] = graph[x + i - 2 + y * roomAm.x][x + y * roomAm.x] = 1;

					parentRoom[x + i - 2 + y * roomAm.x] = x + y * roomAm.x;
					addToNextRooms(x + i - 2, y, (i + 2) % 4, false);
					generated = true;
					usedExistingRoom = false;
				}
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

		length = dist;
	}

	void MapManager::generateFirstRoom()
	{
		exists[start.x + start.y * roomAm.x] = true;
		rooms[start.x + start.y * roomAm.x].calculateDoors(2, true, -1);
		bool possible[4] = { true, true, true, true };
		for (int i = 0; i < 4; i++)
		{
			bool generated = false;
			bool usedExistingRoom = false; // will always be false for first room since no other rooms were generated yet
			if (rooms[start.x + start.y * roomAm.x].doors[i])
			{
				calcNewRoom(i, start.x, start.y, false, generated, usedExistingRoom);
				if (!generated)
				{
					rooms[start.x + start.y * roomAm.x].nrdoors--;
					rooms[start.x + start.y * roomAm.x].doors[i] = false;
					possible[i] = false;
					for (int j = 0; j < 4; j++)
					{
						if (!rooms[start.x + start.y * roomAm.x].doors[i] && possible[j])
							calcNewRoom(j, start.x, start.y, false, generated, usedExistingRoom);
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
			bool usedExistingRoom = false;
			if (rooms[x + y * roomAm.x].doors[i] && i != StartDirection)
			{
				calcNewRoom(i, x, y, CanClose, generated, usedExistingRoom);
				if (!generated)
				{
					if (!usedExistingRoom)
					{
						std::cout << "Did Not Use Existing Room " << x + y * roomAm.x + 1 << " " << i << "\n";
						rooms[x + y * roomAm.x].doors[i] = false;
					}
					else std::cout << "USED Existing Room " << x + y * roomAm.x + 1 << " " << i << "\n";
					possible[i] = false;
					if (!k || !CanClose)
					{
						for (int j = 0; j < 4; j++)
						{
							usedExistingRoom = false;
							if (!rooms[start.x + start.y * roomAm.x].doors[i] && possible[j])
								calcNewRoom(j, x, y, CanClose, generated, usedExistingRoom);
							if (generated || usedExistingRoom)
							{
								rooms[x + y * roomAm.x].doors[j] = true;
								break;
							}
							else possible[j] = false;
						}
					}
				}
				else if (usedExistingRoom)
					std::cout << "GENERATED + USED Existing Room " << x + y * roomAm.x + 1<< " " << i << "\n";
			}
		}
		rooms[x + y * roomAm.x].changeDoorLayout(false);
		actualRooms++;
		generatedOrder[actualRooms] = x + y * roomAm.x;
	}

	void MapManager::generateNextRooms()
	{		
		//std::cout << "GenerateNextRooms NewRooms: " << newRooms << std::endl;
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
			if (goBack > 5)
				goodMap = false;
			else if (goBack > 1)
			{
				for (int i = aux[goBack - 2]; i < newRooms; i++)
				{
					exists[nextRooms[i][0] + nextRooms[i][1] * roomAm.x] = false;
					rooms[nextRooms[i][0] + nextRooms[i][1] * roomAm.x].resetDoors();
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
					actualRooms--;
				}
				goBack--;
				currentGen = 0;
				newRooms = aux[goBack];
				generateNextRooms();
			}
			else
			{
				goodMap = false;
			}	
		}
		else
		{
			calculateRoute(start.x + start.y * roomAm.x);
			goodMap = true;
		}
	}

	Room* MapManager::switchRoom(int x, int y)
	{
		std::cout << x + y * roomAm.x + 1 << std::endl;
		if (player->currentRoom->getItems().size())
			if (player->currentRoom->getItems()[0]->getType() == 2)
				player->currentRoom->removeItem(player->currentRoom->getItems()[0]);
		calculateRoute(x + y * roomAm.x);
		return &rooms[x + y * roomAm.x];
	}

}