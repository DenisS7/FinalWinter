#include "Room.h"
#include "../template.h"
#include "../surface.h"
#include <fstream>
#include <iostream>
#include "newmath.h"
#include <algorithm>
#include <vector>




namespace Map
{


void Room::InitiateRoom(int number, const std::vector <int> collisionTiles, const std::vector <int> portalTiles)
{	
	roomNumber = number;
	type = Fight;
	level = 2;

	std::ifstream fin("Classes/RoomLayout/Room2.txt");
	fin >> size.x >> size.y;

	roomSize = size.x * size.y;

	for (int i = 0; i < roomSize; i++)
	{
		int x;
		fin >> x;
		layout[i] = x;
		if (std::find(collisionTiles.begin(), collisionTiles.end(), x) != collisionTiles.end())
			tiles.push_back(makeTile(x, collide, 0, true));
		else if (std::find(portalTiles.begin(), portalTiles.end(), x) != portalTiles.end())
			tiles.push_back(makeTile(x, portalInactive, 0, true));
		else tiles.push_back(makeTile(x, nonCollide, 0, false));
	}

	fin.close();

	tilesPerRow = tilemap.GetPitch() / tilesize;
}

void Room::addToRotatedTiles(int x, int rotation)
{
	rotatedTiles[rTilesNr] = x;
	tileRotation[rTilesNr] = rotation;
	rTilesNr++;
}

void Room::moveMap(int x, int y)
{
	loc.x += x;
	loc.y += y;
	if (!newmath::inRange(loc.x, 0, size.x * tilesize - 800) || !newmath::inRange(loc.y, 0, size.y * tilesize * 512))
		moved = false;
	else moved = true;
	newmath::clamp(loc.x, 0, size.x * tilesize - 800);
	newmath::clamp(loc.y, 0, size.y * tilesize - 512);
}

void Room::ChangeDoorLayout()
{
	

	//std::cout << roomNumber << std::endl;
	if (doors[0]) //down
	{	
			//std::cout << roomNumber << " " << "DOWN" << std::endl;
		layout[size.x / 2 - 1 + (size.y - 1) * size.x] = 164; // Replace 164 with const portal
		layout[size.x / 2 - 1 + (size.y - 2) * size.x] = 191;

		tiles[size.x / 2 - 1 + (size.y - 1) * size.x].drawIndex = 164;
		tiles[size.x / 2 - 1 + (size.y - 2) * size.x].drawIndex = 191;

		tiles[size.x / 2 - 1 + (size.y - 1) * size.x].type = portalInactive;
		tiles[size.x / 2 - 1 + (size.y - 2) * size.x].type = portalInactive;

		tiles[size.x / 2 - 1 + (size.y - 1) * size.x].rotate = tiles[size.x / 2 - 1 + (size.y - 2) * size.x].rotate = 2;



	}
	if (doors[2]) // up
	{
		
			//std::cout << roomNumber << " " << "UP" << std::endl;
		layout[size.x / 2 - 1 + size.x] = 164;
		layout[size.x / 2 - 1 + 2 * size.x] = 191;

		tiles[size.x / 2 - 1 + size.x].drawIndex = 164;
		tiles[size.x / 2 - 1 + 2 * size.x].drawIndex = 191;

		tiles[size.x / 2 - 1 + size.x].type = portalInactive;
		tiles[size.x / 2 - 1 + 2 * size.x].type = portalInactive;
	}
	if (doors[1]) //left
	{
		
			//std::cout << roomNumber << " " << "LEFT" << std::endl;
	

		tiles[(size.y / 2) * size.x].drawIndex = 164;
		tiles[(size.y / 2) * size.x + 1].drawIndex = 191;

		tiles[(size.y / 2) * size.x].type = portalInactive;
		tiles[(size.y / 2) * size.x + 1].type = portalInactive;

		tiles[(size.y / 2) * size.x].rotate = tiles[(size.y / 2) * size.x + 1].rotate = 1;


	}
	if (doors[3]) //right
	{
		
			//std::cout << roomNumber << " " << "RIGHT" << std::endl;
	

		tiles[(size.y / 2) * size.x + size.x - 1].drawIndex = 164;
		tiles[(size.y / 2) * size.x + size.x - 2].drawIndex = 191;

		tiles[(size.y / 2) * size.x + size.x - 1].type = portalInactive;
		tiles[(size.y / 2) * size.x + size.x - 2].type = portalInactive;

		tiles[(size.y / 2) * size.x + size.x - 1].rotate = tiles[(size.y / 2) * size.x + size.x - 2].rotate = 3;
		
		
	}
	
	//for (int i = 0; i < 4; i++)
		//std::cout << roomNumber << " " << doors[0] << " " << doors[1] << " " << doors[2] << " " << doors[3] << std::endl;
}	

void Room::CalculateDoors(int startDoor, bool CanClose, int beforeRoom)
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

void Room::ResetDoors()
{
	nrdoors = 1;
	for (int i = 0; i < 4; i++)
		doors[i] = false;
}

int Room::DoorNumber()
{
	int k = 0;
	for (int i = 0; i < 4; i++)
		if (doors[i])
			k++;
	return k;
}

int Room::CheckCollision(int x, int y)
{
	int xTile = x;
	int yTile = y;
	if (tiles[xTile + yTile * size.x].type == collide)
		return collide;
	else if (tiles[xTile + yTile * size.x].type == portalInactive) //n
		return portalInactive;
	return 0;
}

void Room::DrawRotatedTile(int tx, int ty, GameSpace::Surface* GameScreen, int dx, int dy, int rotate)
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

void Room::DrawTile(int tx, int ty, GameSpace::Surface* GameScreen, int dx, int dy)
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

void Room::DrawSpriteTile(int tx, int ty, GameSpace::Surface* GameScreen, int dx, int dy)
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

void Room::DrawMap(GameSpace::Surface* GameScreen)
{
	offset.x = loc.x % tilesize;
	offset.y = loc.y % tilesize;
	
	newmath::ivec2 start;

	start.x = loc.x / tilesize;
	start.y = loc.y / tilesize;
	
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
				DrawTile(tx, ty, GameScreen, xDrawLoc, yDrawLoc);
			else
			{
				DrawRotatedTile(tx, ty, GameScreen, xDrawLoc, yDrawLoc, tiles[y * 44 + x].rotate);
			}
	
		}
	}

	
}

void Room::UpdateMap(int x, int y)
{
	
}

}