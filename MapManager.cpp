#include "MapManager.h"
#include "Classes/Room.h"
#include "Classes/EnemyBase.h"
#include "Classes/Player.h"
#include <iostream>
#include <fstream>

namespace Map
{
	int k[10] = { 0 };

	void MapManager::initiate()
	{
		std::ifstream fin("Classes/RoomLayout/Collisions.txt");
		fin >> nrColTiles;
		for (int i = 0; i < nrColTiles; i++)
		{
			int x;
			fin >> x;
			collisionTiles.push_back(x);
		}
		fin.close();

		std::ifstream pin("Classes/RoomLayout/Portals.txt");
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
			ein >> enemyTypes[i].damagePerAttack >> enemyTypes[i].damageOnCol >> enemyTypes[i].speed;
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

		roomAm.x = 7;
		roomAm.y = 7;

		start.x = 4;
		start.y = 5;
		finish.x = 1;
		finish.y = 1;
		for (int i = 0; i < 49; i++)
			rooms[i].initiateRoom(i, collisionTiles, portalTiles, this);
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
		if (exists[x + y * 7]) //the room was already generated
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
		for (int i = 0; i < roomAm.x * roomAm.y; i++)
			rooms[i].inititateEnemies();
	}

	void MapManager::calcNewRoom(int i, int x, int y, bool canClose, bool& generated)
	{
		if (i % 2 == 0)
		{
			if (canCreateNewRoom(x, y - i + 1))
			{
				k[newRooms] = x + y * roomAm.x;

				graph[x + y * roomAm.x][x + (y - i + 1) * roomAm.x] = graph[x + (y - i + 1) * roomAm.x][x + y * roomAm.x] = 1;
				
				parentRoom[x + (y - i + 1) * 7] = x + y * 7;
				addToNextRooms(x, y - i + 1, (i + 2) % 4, false);
				generated = true;
			}
			
		}
		else if (i % 2 == 1)
		{
			if (canCreateNewRoom(x + i - 2, y))
			{
				k[newRooms] = x + y * 7;

				graph[x + y * roomAm.x][x + i - 2 + y * roomAm.x] = graph[x + i - 2 + y * roomAm.x][x + y * roomAm.x] = 1;

				parentRoom[x + i - 2 + y * 7] = x + y * 7;
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

		std::cout << std::endl;

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
		/*int dist = 0;
		int x = finish.x + finish.y * roomAm.x;

		while (x != room)
		{
			std::cout << x << " SEARCHING" << std::endl;
			x = parentRoom[x];
			dist++;
		}*/

		std::cout << dist << std::endl;
	}

	void MapManager::generateFirstRoom()
	{
		exists[start.x + start.y * 7] = true;
		rooms[start.x + start.y * 7].calculateDoors(2, true, -1);
		bool possible[4] = { true };
		for (int i = 0; i < 4; i++)
		{
			bool generated = false;
			if (rooms[start.x + start.y * 7].doors[i])
			{
				calcNewRoom(i, start.x, start.y, false, generated);
				if (!generated)
				{
					rooms[start.x + start.y * 7].doors[i] = false;
					possible[i] = false;
					for (int j = 0; j < 4; j++)
					{
						if (!rooms[start.x + start.y * 7].doors[i] && possible[j])
							calcNewRoom(j, start.x, start.y, false, generated);
						if (generated)
						{
							rooms[start.x + start.y * 7].doors[j] = true;
							break;
						}
						else possible[j] = false;
					}
				}
			}
			
		}

		rooms[start.x + start.y * 7].changeDoorLayout(false);
		
		generatedOrder[0] = start.x + start.y * 7;

		generateNextRooms();
	}

	void MapManager::generate(int x, int y, int StartDirection, bool CanClose, int kn)
	{
		exists[x + y * 7] = true;
		//if (goingBack)
			//std::cout << "Entered Generation \n";
		rooms[x + y * 7].calculateDoors(StartDirection, CanClose, kn);
		//if (goingBack)
			//std::cout << "Passed Calculate Doors \n";
		bool possible[4] = { true };
		for (int i = 0; i < 4; i++)
		{
			bool generated = false;
			if (rooms[x + y * 7].doors[i] && i != StartDirection)
			{
				calcNewRoom(i, x, y, CanClose, generated);
				if (!generated)
				{
					//std::cout << "NO ROOM" << std::endl;
					rooms[x + y * 7].doors[i] = false;
					possible[i] = false;
					if (!k || !CanClose)
					{
						for (int j = 0; j < 4; j++)
						{
							if (!rooms[start.x + start.y * 7].doors[i] && possible[j])
								calcNewRoom(j, x, y, CanClose, generated);
							if (generated)
							{
								rooms[x + y * 7].doors[j] = true;
								break;
							}
							else possible[j] = false;
						}
					}
				}
			}
		}
		//if (goingBack)
			//std::cout << "Passed For \n";
		rooms[x + y * 7].changeDoorLayout(false);
		actualRooms++;
		generatedOrder[actualRooms] = x + y * 7;
	}

	void MapManager::generateNextRooms()
	{
		//for (int i = 0; i < newRooms; i++)
			//std::cout << "New Rooms: " << i << " x: " << nextRooms[i][0] << " y: " << nextRooms[i][1] << " first door: " << nextRooms[i][2] << " can close: " << nextRooms[i][3] << std::endl;
		
		aux[goBack] = newRooms;
		
		//std::cout <<"NewRoomsNumber = " << newRooms << " " << std::endl;

	

		//newRooms = 0;
		
		//std::cout << "Before Generation goBack = " << goBack << " aux[goBack] = " << aux[goBack] << " currentGen = " << currentGen << " newRooms = " << newRooms << std::endl;
		
		for (int i = currentGen; i < aux[goBack]; i++)
		{
			//std::cout << i << " ";
			generate(nextRooms[i][0], nextRooms[i][1], nextRooms[i][2], nextRooms[i][3], k[i]);
		}
		
		//std::cout << "\n After Generation goBack = " << goBack << " aux[goBack] = " << aux[goBack] << " currentGen = " << currentGen << " newRooms = " << newRooms << std::endl;

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
			//for (int i = 0; i <= goBack; i++)
				//std::cout << aux[i] << " ";
			//std::cout << std::endl;
			//std::cout << "EXIT NOT FOUND" << std::endl;
			if (goBack > 1)
			{
				
				for (int i = aux[goBack - 2]; i < newRooms; i++)
				{
					exists[nextRooms[i][0] + nextRooms[i][1] * roomAm.x] = false;
					rooms[nextRooms[i][0] + nextRooms[i][1] * roomAm.x].resetDoors();
					actualRooms--;
				}
				goBack--;
				//std::cout << goBack << std::endl;
				currentGen = aux[goBack - 1];
				newRooms = aux[goBack];
				//std::cout << "PASSED \n";
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
				//std::cout << "PASSED GO BACK = 1 \n";
				generateNextRooms();
			}
			else
			{
				//for (int i = 0; i < 49; i++)
					//std::cout << exists[i] << std::endl;
				generateFirstRoom();
			}
			
		}

	}

	Room* MapManager::switchRoom(int x, int y)
	{
		calculateRoute(x + y * 7);
		return &rooms[x + y * roomAm.x];
	}

}