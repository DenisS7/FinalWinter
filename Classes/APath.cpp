#include "APath.h"
#include "Room.h"
#include <iostream>
#include <vector>
#include <limits.h>


int APath::getClosestTile()
{
	int index = 0;
	int minf = INT_MAX;
	
	for (int i = 0; i < nextTiles.size(); i++)
	{
		std::cout << minf << " " << nextTiles[i].position.x << " " << nextTiles[i].position.y << " " << nextTiles[i].f << std::endl;
		if (nextTiles[i].f <= minf)
			index = i, minf = nextTiles[i].f;
	}
	std::cout << index << std::endl;
	return index;
}

int APath::getIndex(std::vector <Atile> v, newmath::ivec2 pos)
{
	for (int i = 0; i < v.size(); i++)
		if (v[i].position == pos)
			return i;
	return -1;
}

bool APath::isTileValid(newmath::ivec2 tilePos)
{
	if (tilePos.x >= 0 && tilePos.x <= currentRoom->size.x)
		if (tilePos.y >= 0 && tilePos.y <= currentRoom->size.y)
		{
			if (!currentRoom->tiles[tilePos.x + tilePos.y * currentRoom->size.x].colidable)
				return true;
			//else std::cout << "COLIDABLE: " << tilePos.x << " " << tilePos.y << std::endl;
		}

	return false;
}




void APath::getAdjTile(Atile tile, newmath::ivec2 nextTile)
{
	newmath::ivec2 newpos = tile.position + nextTile;
	int newIndex = newpos.x + newpos.y * currentRoom->size.x;
	//std::cout << newpos.x << " " << newpos.y << " " << newIndex << std::endl;
	
	if (isTileValid(newpos))
	{
		if (!visited[newIndex])
		{
			visited[newIndex] = true;
			parents[newIndex] = tile;
			Atile neighbour(newpos, tile.g + 1);
			neighbour.h = newmath::manhattanDist(neighbour.position, finish);
			neighbour.f = neighbour.g + neighbour.h;
			nextTiles.push_back(neighbour);
		}
		else if (visited[newIndex])
		{
			int index = getIndex(passedTiles, newpos);
			//std::cout << "visited index: " << newpos.x << " " << newpos.y << " " << visited[newIndex] << " " << index << std::endl;
			int newgValue = tile.g + 1;
			if (index != -1)
				if (newgValue <= passedTiles[index].g)
				{
					passedTiles[index].g = newgValue;
					passedTiles[index].f = passedTiles[index].g + passedTiles[index].h;
					parents[index] = tile;
				}
			//if (index == -1)
				//std::cout << "visited index: " << newpos.x << " " << newpos.y << " " << visited[newIndex] << " " << index << std::endl;
		}
	}
}

void APath::getNeighbours(Atile tile)
{
	getAdjTile(tile, newmath::make_ivec2(-1, -1));
	getAdjTile(tile, newmath::make_ivec2(-1, 0));
	getAdjTile(tile, newmath::make_ivec2(-1, 1));
	getAdjTile(tile, newmath::make_ivec2(0, -1));
	getAdjTile(tile, newmath::make_ivec2(0, 1));
	getAdjTile(tile, newmath::make_ivec2(1, -1));
	getAdjTile(tile, newmath::make_ivec2(1, 0));
	getAdjTile(tile, newmath::make_ivec2(1, 1));

}

std::vector <newmath::ivec2> APath::findPath(newmath::ivec2 start, newmath::ivec2 newFinish, Map::Room* newRoom)
{
	currentRoom = newRoom;
	finish = newFinish;
	
	int starth = newmath::manhattanDist(start, finish);
	
	Atile startTile(start, 0);
	startTile.h = starth;
	startTile.f = startTile.g + startTile.h;
	visited[start.x + start.y * currentRoom->size.x] = true;
	
	nextTiles.push_back(startTile);
	
	parents[start.x + start.y * currentRoom->size.x] = startTile;

	bool pathFound = false;

	int currentIndex = 0;
	Atile current = nextTiles[0];
	

	while (!nextTiles.empty())
	{
		currentIndex = getClosestTile();
		current = nextTiles[currentIndex];
		
		
		//std::cout << current.position.x << " " << current.position.y << " " << currentIndex << std::endl;
		//std::cout << "F: " << current.f << " G: " << current.g << " H: " << current.h << std::endl << std::endl;

		nextTiles.erase(nextTiles.begin() + currentIndex);
		passedTiles.push_back(current);

		getNeighbours(current);

		if (current.position == finish)
		{
			pathFound = true;
			break;
		}

		
	
	}

	path.clear();
	
	if (pathFound)
	{
		newmath::ivec2 currentPos = current.position;
		path.push_back(currentPos);
		
		while (current.position != startTile.position)
		{
			//std::cout << current.position.x << " " << current.position.y << std::endl;
			int tileIndex = current.position.x + current.position.y * currentRoom->size.x;
			current = parents[tileIndex];
			path.insert(path.begin(), current.position);
		}
	}
	
	return path;
}