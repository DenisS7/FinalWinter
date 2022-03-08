#include "EnemyBase.h"
#include "../MapManager.h"
#include <limits.h>
#include <iostream>
#include "Player.h"
#include "../surface.h"

namespace Character
{
	newmath::ivec2 EnemyBase::getCurrentPos(newmath::ivec2 posToGet)
	{
		int x = ((int)locf.x + posToGet.x) / currentRoom->tilesize;
		int y = ((int)locf.y + posToGet.y) / currentRoom->tilesize;
		return newmath::make_ivec2(x, y);
	}

	void EnemyBase::changeDrawLoc()
	{
		drawLocf = locf - currentRoom->getLocation();
	}

	void EnemyBase::triggerFollowPlayer()
	{

	}

	void EnemyBase::init(int type)
	{
		screen = currentRoom->getPlayer()->screen;
		data.type = type;
		data.health= currentRoom->manager->getEnemyType(data.type).health;
		data.damagePerAttack = currentRoom->manager->getEnemyType(data.type).damagePerAttack;
		data.damageOnCol = currentRoom->manager->getEnemyType(data.type).damageOnCol;
		data.speed = currentRoom->manager->getEnemyType(data.type).speed;
		data.points = currentRoom->manager->getEnemyType(data.type).points;
		data.col.offset.x = currentRoom->manager->getEnemyType(data.type).col.collisionBox.x;
		data.col.offset.y = currentRoom->manager->getEnemyType(data.type).col.collisionBox.y;

		data.col.collisionBox.width = currentRoom->manager->getEnemyType(data.type).col.collisionBox.width;
		data.col.collisionBox.height = currentRoom->manager->getEnemyType(data.type).col.collisionBox.height;

		data.spritesheetsNr = currentRoom->manager->getEnemyType(data.type).spritesheetsNr;
		for(int i = 0; i < data.spritesheetsNr; i++)
			data.epaths[i] = currentRoom->manager->getEnemyType(data.type).epaths[i];
			
		
		locf.x = (float)IRand((currentRoom->getSize().x - sprite.GetWidth() / currentRoom->tilesize - 1) * currentRoom->tilesize);
		locf.y = (float)IRand((currentRoom->getSize().y - sprite.GetHeight() / currentRoom->tilesize - 1) * currentRoom->tilesize);

		data.col.collisionBox.x = data.col.offset.x + (int)locf.x;
		data.col.collisionBox.y = data.col.offset.y + (int)locf.y;

		changeDrawLoc();

		tilePos = getCurrentPos(newmath::make_ivec2(sprite.GetWidth() / 2, sprite.GetHeight() / 2));

		initOcupTile = getCurrentPos(newmath::make_ivec2(0, 0));
		finOcupTile = getCurrentPos(newmath::make_ivec2(sprite.GetWidth(), sprite.GetHeight()));

		for (int x = initOcupTile.x; x <= finOcupTile.x && x < currentRoom->getSize().x; x++)
		{
			for (int y = initOcupTile.y; y <= finOcupTile.y && y < currentRoom->getSize().y; y++)
			{
				int tileNr = x + y * currentRoom->getSize().x;
				currentRoom->addEnemyToTile(this, tileNr);
			}
		}

		currentSs.setDirection(0);

	}

	void EnemyBase::changeActionSprite(int x, int newCurrentRow)
	{
		sprite.SetFile(data.epaths[x].path, data.epaths[x].rows * data.epaths[x].columns, directionFacing * data.epaths[x].columns);
		currentSs.changeSpritesheet(data.epaths[x].path, data.epaths[x].rows, data.epaths[x].columns, newCurrentRow, &sprite);
		currentSs.setFrameTime(data.epaths[x].frameTime);
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
		if (tilePos.x >= 0 && tilePos.x < currentRoom->getSize().x)
			if (tilePos.y >= 0 && tilePos.y < currentRoom->getSize().y)
			{
				
				if (!currentRoom->getTile(tilePos.x + tilePos.y * currentRoom->getSize().x).colidable)
					return true;
			}
		return false;
	}

	void EnemyBase::getAdjTile(const Atile& tile, const newmath::ivec2& nextTile)
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

	void EnemyBase::changeDirection(int newDirection)
	{
		if (directionFacing != newDirection)
		{
			if (move.side[newDirection] && !move.side[directionFacing])
			{
				currentSs.setDirection(newDirection);
				directionFacing = newDirection;
			}
		}
	}

	void EnemyBase::takeDamage(const int damage)
	{
		data.health -= damage;
		
		if (data.health <= 0)
			isDead = true;

		if (!isFollowingPlayer && !isDead)
			triggerFollowPlayer();
	}

	void EnemyBase::die()
	{
		//increase score
		data.col.setCollisionBox(0, 0, 0, 0);
		currentRoom->deleteEnemy(this);
		delete this;
	}

	void EnemyBase::followPlayer()
	{

	}

	void EnemyBase::drawEnemy(float deltaTime)
	{
		currentSs.drawNextSprite(deltaTime, currentRoom->manager->screen, drawLocf);
	}

	void EnemyBase::addMovement(float deltaTime)
	{
		
	}

	void EnemyBase::update(float deltaTime)
	{
		drawEnemy(deltaTime);
	}



}
