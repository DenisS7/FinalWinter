#include "EnemyBase.h"
#include "../MapManager.h"
#include <limits.h>
#include <iostream>
#include "Player.h"
#include "../surface.h"

namespace Character
{
	newmath::ivec2 EnemyBase::getCurrentPos()
	{
		int x = ((int)locf.x + 64) / currentRoom->tilesize;
		int y = ((int)locf.y + 64) / currentRoom->tilesize;
		newmath::ivec2 pos = newmath::make_ivec2(x, y);
		return pos;
	}

	void EnemyBase::Init()
	{
		screen = currentRoom->player->screen;
		data.health= currentRoom->manager->enemyTypes[data.type].health;
		data.damagePerAttack = currentRoom->manager->enemyTypes[data.type].damagePerAttack;
		data.damageOnCol = currentRoom->manager->enemyTypes[data.type].damageOnCol;
		data.speed = currentRoom->manager->enemyTypes[data.type].speed;
		data.col.collisionBox = currentRoom->manager->enemyTypes[data.type].col.collisionBox;
		data.spritesheetsNr = currentRoom->manager->enemyTypes[data.type].spritesheetsNr;
		for(int i = 0; i < data.spritesheetsNr; i++)
			data.epaths[i] = currentRoom->manager->enemyTypes[data.type].epaths[i];
		tilePos = getCurrentPos();
		
	}

	void EnemyBase::changeActionSprite(int x)
	{
		sprite.SetFile(new GameSpace::Surface(data.epaths[x].path), data.epaths[x].rows * data.epaths[x].columns, directionFacing * data.epaths[x].columns);
		currentSs.changeSpritesheet(data.epaths[x].path, data.epaths[x].rows, data.epaths[x].columns, &sprite);
		currentSs.setFrameTime(data.epaths[x].frameTime);
	}

	void EnemyBase::changeDrawLoc()
	{
		drawLocf = locf - currentRoom->locf;
	}

	void EnemyBase::resetAPath()
	{
		nextTiles.clear();
		passedTiles.clear();
		std::fill(std::begin(visited), std::end(visited), false);
	}

	int EnemyBase::getClosestTile()
	{
		int index = 0;
		int minf = INT_MAX;

		for (int i = 0; i < nextTiles.size(); i++)
		{
			//std::cout << minf << " " << nextTiles[i].position.x << " " << nextTiles[i].position.y << " " << nextTiles[i].f << " " << nextTiles[i].g << " " << nextTiles[i].h << std::endl;
			if (nextTiles[i].f <= minf)
				index = i, minf = nextTiles[i].f;
		}
		
		return index;
	}

	int EnemyBase::getIndex(const std::vector<Atile>& v, newmath::ivec2 pos)
	{
		for (int i = 0; i < v.size(); i++)
			if (pos == v[i].position)
				return i;
		return -1;
	}

	bool EnemyBase::isTileValid(const newmath::ivec2& tilePos)
	{
		if (tilePos.x >= 0 && tilePos.x <= currentRoom->size.x)
			if (tilePos.y >= 0 && tilePos.y <= currentRoom->size.y)
			{
				
				if (!currentRoom->tiles[tilePos.x + tilePos.y * currentRoom->size.x].colidable)
					return true;
				//else std::cout << "COLIDABLE: " << tilePos.x << " " << tilePos.y << std::endl;
			}
		//std::cout << tilePos.x + tilePos.y * 44 << std::endl;
		return false;
	}

	void EnemyBase::getAdjTile(const Atile& tile, const newmath::ivec2& nextTile)
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

	void EnemyBase::getNeighbours(const Atile& tile)
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

	std::vector<newmath::ivec2> EnemyBase::findPath(newmath::ivec2 start, newmath::ivec2 newFinish)
	{
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
			//std::cout << std::endl << "NEW PATH: " << std::endl;
			//for (int i = 0; i < path.size(); i++)
			{
				//std::cout << path[i].x << " " << path[i].y << std::endl;
				//currentRoom->player->screen->Box(path[i].x * 32, path[i].y * 32, path[i].x * 32 + 32, path[i].y * 32 + 32, 0xff0000);
			}
		}
		resetAPath();
		return path;
	}

	void EnemyBase::changeDirection(int newDirection)
	{
		if (directionFacing != newDirection)
		{
			if (move.side[newDirection] && !move.side[directionFacing])
			{
				currentSs.setDirection(newDirection);
				directionFacing = newDirection;
				std::cout << "Direction Changed" << std::endl;
			}
		}
	}

	void EnemyBase::takeDamage(const int damage)
	{
		data.health -= damage;
		if (data.health <= 0)
			die();
	}

	void EnemyBase::die()
	{

	}

	void EnemyBase::followPlayer()
	{

	}

	void EnemyBase::addMovement(float deltaTime)
	{
		
	}

	void EnemyBase::update(float deltaTime)
	{
		currentSs.drawNextSprite(deltaTime, currentRoom->manager->screen, drawLocf);
	}



}
