#include "Pathfinder.h"
#include "Room.h"

void Pathfinder::resetAPath()
{
	nextTiles.clear();
	passedTiles.clear();
	std::fill(std::begin(visited), std::end(visited), false);
}

int Pathfinder::getClosestTile()
{
	int index = 0;
	int minf = INT_MAX;

	for (int i = 0; i < nextTiles.size(); i++)
	{
		if (nextTiles[i].f <= minf)
			index = i, minf = nextTiles[i].f;
	}

	return index;
}

int Pathfinder::getIndex(const std::vector<Atile>& v, newmath::ivec2 pos)
{
	for (int i = 0; i < v.size(); i++)
		if (pos == v[i].position)
			return i;
	return -1;
}

bool Pathfinder::isTileValid(const newmath::ivec2& tilePos)
{
	if (tilePos.x >= 0 && tilePos.x < currentRoom->getSize().x)
		if (tilePos.y >= 0 && tilePos.y < currentRoom->getSize().y)
		{

			if (!currentRoom->getTile(tilePos.x + tilePos.y * currentRoom->getSize().x).colidable)
				return true;
		}
	return false;
}

void Pathfinder::getAdjTile(const Atile& tile, const newmath::ivec2& nextTile)
{
	newmath::ivec2 newpos = tile.position + nextTile;
	int newIndex = newpos.x + newpos.y * currentRoom->getSize().x;

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
			int newgValue = tile.g + 1;
			if (index != -1)
				if (newgValue <= passedTiles[index].g)
				{
					passedTiles[index].g = newgValue;
					passedTiles[index].f = passedTiles[index].g + passedTiles[index].h;
					parents[index] = tile;
				}
		}
	}
}

void Pathfinder::getNeighbours(const Atile& tile)
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

std::vector<newmath::ivec2> Pathfinder::findPath(newmath::ivec2 start, newmath::ivec2 newFinish, Map::Room* newRoom)
{
		finish = newFinish;
		currentRoom = newRoom;
		int starth = newmath::manhattanDist(start, finish);
		
		Atile startTile(start, 0);
		startTile.h = starth;
		startTile.f = startTile.g + startTile.h;
		visited[start.x + start.y * currentRoom->getSize().x] = true;

		nextTiles.push_back(startTile);

		parents[start.x + start.y * currentRoom->getSize().x] = startTile;

		bool pathFound = false;

		int currentIndex = 0;
		Atile current = nextTiles[0];


		while (!nextTiles.empty())
		{
			currentIndex = getClosestTile();
			current = nextTiles[currentIndex];

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
				int tileIndex = current.position.x + current.position.y * currentRoom->getSize().x;
				current = parents[tileIndex];
				path.insert(path.begin(), current.position);
			}
		}
		resetAPath();
		return path;
}




