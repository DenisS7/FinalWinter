#include "Room.h"
#include "../template.h"
#include "../surface.h"
#include <fstream>
#include <iostream>
#include "newmath.h"
#include <algorithm>
#include <vector>
#include "../MapManager.h"
#include "Player.h"
#include "EnemyBase.h"
#include "enemy_metalbox.h"
#include "enemy_snowman.h"


namespace Map
{


void Room::initiateRoom(int number, const std::vector <int> collisionTiles, const std::vector <int> portalTiles, Map::MapManager* newManager)
{	
	roomNumber = number;
	type = Fight;
	level = 2;

	enemies = 1;
	

	manager = newManager;
	player = newManager->player;
	
	std::ifstream fin("Classes/RoomLayout/Room2.txt");
	fin >> size.x >> size.y;

	roomSize = size.x * size.y;

	for (int i = 0; i < roomSize; i++)
	{
		int x;
		fin >> x;
		if (std::find(collisionTiles.begin(), collisionTiles.end(), x) != collisionTiles.end())
			tiles.push_back(makeTile(x, collide, 0, true));
		else tiles.push_back(makeTile(x, nonCollide, 0, false));
	}

	fin.close();

	tilesPerRow = tilemap.GetPitch() / tilesize;
	moveDir.x = moveDir.y = 0;
}

void Room::inititateEnemies()
{
	for (int i = 0; i < enemies; i++)
	{
		//std::cout << roomNumber << " newEnemy" << std::endl;
		Character::enemy_snowman* newEnemy = new Character::enemy_snowman(this, 0);
		newEnemy->init();
		enemiesInRoom.push_back(newEnemy);
	}
}

void Room::removeEnemyFromTile(const Character::EnemyBase* enemy, int tileNr)
{
	std::vector<Character::EnemyBase*>::iterator position = std::find(tiles[tileNr].entitiesOnTile.begin(), tiles[tileNr].entitiesOnTile.end(), enemy);
	if (position != tiles[tileNr].entitiesOnTile.end())
		tiles[tileNr].entitiesOnTile.erase(position);
	//else std::cout << "WRONG TILE" << std::endl;
}

void Room::addEnemyToTile(Character::EnemyBase* enemy, int tileNr)
{
	if (!std::count(tiles[tileNr].entitiesOnTile.begin(), tiles[tileNr].entitiesOnTile.end(), enemy))
		tiles[tileNr].entitiesOnTile.push_back(enemy);
	//else std::cout << "ALREADY " << std::endl;
}

void Room::enemyOnTiles(Character::EnemyBase* enemy)
{
	int x = ((int)enemy->locf.x) / tilesize;
	int y = ((int)enemy->locf.y) / tilesize;
	newmath::ivec2 initTile = newmath::make_ivec2(x, y);

	x = ((int)enemy->locf.x + enemy->sprite.GetWidth()) / tilesize;
	y = ((int)enemy->locf.y + enemy->sprite.GetHeight()) / tilesize;
	newmath::ivec2 finTile = newmath::make_ivec2(x, y);

	newmath::ivec2 dif = initTile - enemy->initOcupTile;
	if (dif.x < 0)
	{
		for (int x = 0; x > dif.x; x--)
		{
			for (int y = enemy->initOcupTile.y; y <= enemy->finOcupTile.y; y++)
			{
				const int removex = enemy->finOcupTile.x - x;
				const int addx = enemy->initOcupTile.x - x;

				newmath::clamp(removex, 0, size.x - 1);
				newmath::clamp(addx, 0, size.x - 1);

				const int tileRemNr = removex + y * size.x;
				const int tileAddNr = addx + y * size.x;

				removeEnemyFromTile(enemy, tileRemNr);
				addEnemyToTile(enemy, tileAddNr);
			}
		}
	}
	else if (dif.x > 0)
	{
		for (int x = 0; x < dif.x; x++)
		{
			for (int y = enemy->initOcupTile.y; y <= enemy->finOcupTile.y; y++)
			{
				const int removex = enemy->initOcupTile.x + x;
				const int addx = enemy->finOcupTile.x + x;

				newmath::clamp(removex, 0, size.x - 1);
				newmath::clamp(addx, 0, size.x - 1);

				const int tileRemNr = removex + y * size.x;
				const int tileAddNr = addx + y * size.x;

				removeEnemyFromTile(enemy, tileRemNr);
				addEnemyToTile(enemy, tileAddNr);
			}
		}
	}
	
	if (dif.y < 0)
	{
		for (int y = 0; y > dif.y; y--)
		{
			for (int x = enemy->initOcupTile.x; x <= enemy->finOcupTile.x; x++)
			{
				const int removey = enemy->finOcupTile.y - y;
				const int addy = enemy->initOcupTile.y - y;

				newmath::clamp(removey, 0, size.y - 1);
				newmath::clamp(addy, 0, size.y - 1);

				const int tileRemNr = x + removey * size.x;
				const int tileAddNr = x + addy * size.x;

				removeEnemyFromTile(enemy, tileRemNr);
				addEnemyToTile(enemy, tileAddNr);
			}
		}
	}
	else if (dif.y > 0)
	{
		for (int y = 0; y < dif.y; y++)
		{
			for (int x = enemy->initOcupTile.x; x <= enemy->finOcupTile.x; x++)
			{
				const int removey = enemy->initOcupTile.y + y;
				const int addy = enemy->finOcupTile.y + y;

				newmath::clamp(removey, 0, size.y - 1);
				newmath::clamp(addy, 0, size.y - 1);

				const int tileRemNr = x + removey * 7;
				const int tileAddNr = x + addy * 7;

				removeEnemyFromTile(enemy, tileRemNr);
				addEnemyToTile(enemy, tileAddNr);
			}
		}
	}

	enemy->initOcupTile = initTile;
	enemy->finOcupTile = finTile;

}

void Room::openPortals()
{
	changeDoorLayout(true);
}

void Room::deleteEnemy(Character::EnemyBase* enemy)
{
	
	//std::cout << "deleteEnemy" << std::endl;
	std::vector<Character::EnemyBase*>::iterator position = std::find(enemiesInRoom.begin(), enemiesInRoom.end(), enemy);
	if (position != enemiesInRoom.end())
	{
		player->modifyPoints(enemy->data.points);
		enemiesInRoom.erase(position);
		enemies--;
		
	}
	if (enemies == 0)
	{
		player->modifyPoints(100);
		openPortals();
	}
}

void Room::changeDir()
{
	//std::cout << player->move.side[0] << " " << player->move.side[1] << " " << player->move.side[2] << " " << player->move.side[3] << std::endl;
	
	moveDir.x = player->move.side[3] - player->move.side[1];
	moveDir.y = player->move.side[0] - player->move.side[2];

	if (locf.x == 0 || locf.x == (float)size.x * tilesize - 800)
		moveDir.x = 0;
	if (locf.y == 0 || locf.y == (float)size.y * tilesize - 512)
		moveDir.y = 0;
}

void Room::moveMap(int x, int y, float deltaTime)
{
	locf.x += speed * x * deltaTime;
	locf.y += speed * y * deltaTime;
	
	locf.x = newmath::clampf(locf.x, 0.0, (float)size.x * tilesize - 800);
	locf.y = newmath::clampf(locf.y, 0.0, (float)size.y * tilesize - 512);
}

void Room::changeDoorLayout(bool isOpen)
{
	int door[2] = { 40, 67 };
	int type = portalInactive;
	if (isOpen)
	{
		door[0] = manager->openDoor[0];
		door[1] = manager->openDoor[1];
		type = portalActive;
	}
	else
	{
		door[0] = manager->closedDoor[0];
		door[1] = manager->closedDoor[1];
		type = portalInactive;
	}
	if (doors[0]) //down
	{	
		tiles[size.x / 2 - 1 + (size.y - 1) * size.x].drawIndex = door[0];
		tiles[size.x / 2 - 1 + (size.y - 2) * size.x].drawIndex = door[1];

		tiles[size.x / 2 - 1 + (size.y - 1) * size.x].type = type;
		tiles[size.x / 2 - 1 + (size.y - 1) * size.x].colidable = true;
		//tiles[size.x / 2 - 1 + (size.y - 2) * size.x].type = portalActive;

		tiles[size.x / 2 - 1 + (size.y - 1) * size.x].rotate = tiles[size.x / 2 - 1 + (size.y - 2) * size.x].rotate = 2;
	}
	if (doors[2]) // up
	{
		tiles[size.x / 2 - 1 + size.x].drawIndex = door[0];
		tiles[size.x / 2 - 1 + 2 * size.x].drawIndex = door[1];

		tiles[size.x / 2 - 1 + size.x].type = type;
		tiles[size.x / 2 - 1 + size.x].colidable = true;
		//tiles[size.x / 2 - 1 + 2 * size.x].type = portalActive;
	}
	if (doors[1]) //left
	{
		tiles[(size.y / 2) * size.x].drawIndex = door[0];
		tiles[(size.y / 2) * size.x + 1].drawIndex = door[1];

		tiles[(size.y / 2) * size.x].type = type;
		tiles[(size.y / 2) * size.x].colidable = true;
		//tiles[(size.y / 2) * size.x + 1].type = portalActive;

		tiles[(size.y / 2) * size.x].rotate = tiles[(size.y / 2) * size.x + 1].rotate = 1;
	}
	if (doors[3]) //right
	{
		tiles[(size.y / 2) * size.x + size.x - 1].drawIndex = door[0];
		tiles[(size.y / 2) * size.x + size.x - 2].drawIndex = door[1];

		tiles[(size.y / 2) * size.x + size.x - 1].type = type;
		tiles[(size.y / 2) * size.x + size.x - 1].colidable = true;
		//tiles[(size.y / 2) * size.x + size.x - 2].type = portalActive;

		tiles[(size.y / 2) * size.x + size.x - 1].rotate = tiles[(size.y / 2) * size.x + size.x - 2].rotate = 3;
	}
}	

void Room::calculateDoors(int startDoor, bool CanClose, int beforeRoom)
{
	doors[startDoor] = true;
	
	//std::cout << "Calculating Doors Before " << beforeRoom << " " << roomNumber << " " << nrdoors << std::endl;

	nrdoors += IRand(4);
	if (nrdoors == 1 && CanClose == false)
		nrdoors = 2;
	
	//std::cout << "Calculating Doors After " << nrdoors << std::endl;
		
	for (int i = 0; i < nrdoors - 1; i++)
	{
		int n = IRand(4);
		while (doors[n])
			n = (n + 1) % 4;
		doors[n] = true;
	}
}

void Room::resetDoors()
{
	nrdoors = 1;
	for (int i = 0; i < 4; i++)
		doors[i] = false;
}

int Room::doorNumber()
{
	int k = 0;
	for (int i = 0; i < 4; i++)
		if (doors[i])
			k++;
	return k;
}

int Room::checkCollision(int x, int y)
{
	int xTile = x;
	int yTile = y;
	if (tiles[xTile + yTile * size.x].type == collide)
		return collide;
	else if (tiles[xTile + yTile * size.x].type == portalActive) 
		return portalActive;
	return 0;
}

void Room::drawRotatedTile(int tx, int ty, GameSpace::Surface* GameScreen, int dx, int dy, int rotate)
{
	newmath::ivec2 rot, loop, add;
	rot.x = rot.y = 0;
	loop.x = loop.y = 0;
	add.x = add.y = 0;
	int xRot = 0, yRot = 0;
	int xLoop = 1, yLoop = 0;
	int xAdd = 0, yAdd = 1;
	if (rotate == 1)
	{
		rot.x = 31;
		loop.x = 0;
		loop.y = 1;
		add.x = -1;
		add.y = 0;
	}
	else if (rotate == 2)
	{
		rot.x = rot.y = 31;
		loop.x = -1;
		loop.y = 0;
		add.x = 0;
		add.y = -1;
	}
	else if (rotate == 3)
	{
		rot.y = 31;
		loop.x = 0;
		loop.y = -1;
		add.x = 1;
		add.y = 0;
	}

	GameSpace::Pixel* src = tilemap.GetBuffer() + tx * tilesize + ty * tilesize * tilemap.GetPitch();
	GameSpace::Pixel* dst = GameScreen->GetBuffer() + dx - offset.x + (dy - offset.y) * GameScreen->GetPitch();

	int yStartOffset = dy - offset.y;

	while (yStartOffset < 0)
	{
		yStartOffset++;
		rot.y += add.y;
		rot.x += add.x;
		dst += GameScreen->GetPitch();
	}

	for (int i = 0; i < tilesize && yStartOffset <= GameScreen->GetHeight(); i++, yStartOffset++)
	{
		newmath::ivec2 rem;
		rem.x = rot.x;
		rem.y = rot.y;
		for (int j = 0; j < tilesize; j++, rem.x += loop.x, rem.y += loop.y)
			if (j + dx >= offset.x && j + dx < GameScreen->GetPitch() + offset.x)
				dst[j] = src[rem.x + rem.y * tilemap.GetPitch()];
		rot.x += add.x;
		rot.y += add.y;
		
		//src += tilemap.GetPitch() * yAdd;
		dst += GameScreen->GetPitch();
	}
}

void Room::drawTile(int tx, int ty, GameSpace::Surface* GameScreen, int dx, int dy)
{
	GameSpace::Pixel* src = tilemap.GetBuffer() + tx * tilesize + ty * tilesize * tilemap.GetPitch();
	GameSpace::Pixel* dst = GameScreen->GetBuffer() + dx - offset.x + (dy - offset.y) * GameScreen->GetPitch();

	int yStartOffset = dy - offset.y;

	while (yStartOffset < 0)
	{
		yStartOffset++;
		src += tilemap.GetPitch();
		dst += GameScreen->GetPitch();
	}

	for (int i = 0; i < tilesize && yStartOffset <= GameScreen->GetHeight(); i++, yStartOffset++)
	{
		for (int j = 0; j < tilesize; j++)
			if (j + dx >= offset.x && j + dx < GameScreen->GetPitch() + offset.x)
				dst[j] = src[j];
		src += tilemap.GetPitch(), dst += GameScreen->GetPitch();
	}
}

void Room::drawSpriteTile(int tx, int ty, GameSpace::Surface* GameScreen, int dx, int dy)
{
	GameSpace::Pixel* src = tilemap.GetBuffer() + tx * tilesize + ty * tilesize * tilemap.GetPitch();
	GameSpace::Pixel* dst = GameScreen->GetBuffer() + dx - offset.x + (dy - offset.y) * GameScreen->GetPitch();

	int yStartOffset = dy - offset.y;

	while (yStartOffset < 0)
	{
		yStartOffset++;
		src += tilemap.GetPitch();
		dst += GameScreen->GetPitch();
	}

	for (int i = 0; i < tilesize && yStartOffset <= GameScreen->GetHeight(); i++, yStartOffset++)
	{
		for (int j = 0; j < tilesize; j++)
			if (j + dx >= offset.x && j + dx < GameScreen->GetPitch() + offset.x && src[j])
				dst[j] = src[j];
		src += tilemap.GetPitch(), dst += GameScreen->GetPitch();
	}
}

void Room::drawMap(GameSpace::Surface* GameScreen)
{
	offset.x = (int)locf.x % tilesize;
	offset.y = (int)locf.y % tilesize;
	
	newmath::ivec2 start;

	start.x = (int)locf.x / tilesize;
	start.y = (int)locf.y / tilesize;
	
	if (start.x < 0)
		start.x = 0;
	
	if (start.y < 0)
		start.y = 0;
	
	for (int y = start.y; y <= 16 + start.y && y < size.y; y++)
	{
		for (int x = start.x; x <= 25 + start.x && x < size.x; x++)
		{
			int tx = (tiles[y  * 44 + x].drawIndex - 1) % tilesPerRow;
			int ty = (tiles[y  * 44 + x].drawIndex - 1) / tilesPerRow;

			int xDrawLoc = (x - start.x) * tilesize;
			int yDrawLoc = (y - start.y) * tilesize;

			if (!tiles[y * 44 + x].rotate)
			{
					drawTile(tx, ty, GameScreen, xDrawLoc, yDrawLoc);
			}
			else 
			{
				drawRotatedTile(tx, ty, GameScreen, xDrawLoc, yDrawLoc, tiles[y * 44 + x].rotate);
			}
	
		}
	}

	
}

void Room::updateEnemies()
{
	for (int i = 0; i < enemiesInRoom.size(); i++)
	{
		enemiesInRoom[i]->findPath(enemiesInRoom[i]->getCurrentPos(newmath::make_ivec2(enemiesInRoom[i]->sprite.GetWidth() / 2, enemiesInRoom[i]->sprite.GetHeight() / 2)), player->getCurrentPos());
		enemiesInRoom[i]->changeDrawLoc();
	}
}

void Room::updateTiles()
{
	for (int i = 0; i < enemiesInRoom.size(); i++)
		enemyOnTiles(enemiesInRoom[i]);
}

void Room::updateMap(float deltaTime, GameSpace::Surface* GameScreen)
{
	changeDir();
	
	//std::cout << moveDir.x << " " << moveDir.y << std::endl;
	drawMap(GameScreen);
	for (int i = 0; i < enemiesInRoom.size(); i++)
	{
		enemiesInRoom[i]->update(deltaTime);
	}
	updateTiles();
}

}