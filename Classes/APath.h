#pragma once
#include "newmath.h"
#include <vector>
#include <limits.h>

namespace Map
{
	class Room;
}

class APath
{
private:

public:

	struct Atile
	{
		bool visited = false;
		
		newmath::ivec2 position;
		int g = INT_MAX;
		int h = INT_MAX;
		int f = INT_MAX;
		Atile()
		{
			f = INT_MAX;
			g = INT_MAX;
			h = INT_MAX;
		}
		Atile( newmath::ivec2 newPosition, int ng)
		{
			position = newPosition;
			g = ng;
		}
	};

	Atile parents[1200];
	bool visited[1200] = {false};
	
	std::vector <newmath::ivec2> path;
	std::vector <Atile> nextTiles;
	std::vector <Atile> passedTiles;	
	Map::Room* currentRoom;
	newmath::ivec2 finish;

	int getClosestTile();
	int getIndex(std::vector <Atile> v, newmath::ivec2 pos);
	bool isTileValid(newmath::ivec2 tilePos);
	void getAdjTile(Atile tile, newmath::ivec2 nextTile);
	void getNeighbours(Atile tile);
	std::vector <newmath::ivec2> findPath(newmath::ivec2 start, newmath::ivec2 finish, Map::Room* newRoom);

};
