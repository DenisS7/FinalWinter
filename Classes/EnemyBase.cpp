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
		data.range = currentRoom->manager->getEnemyType(data.type).range;
		data.col.offset.x = currentRoom->manager->getEnemyType(data.type).col.collisionBox.x;
		data.col.offset.y = currentRoom->manager->getEnemyType(data.type).col.collisionBox.y;

		data.col.collisionBox.width = currentRoom->manager->getEnemyType(data.type).col.collisionBox.width;
		data.col.collisionBox.height = currentRoom->manager->getEnemyType(data.type).col.collisionBox.height;

		data.spritesheetsNr = currentRoom->manager->getEnemyType(data.type).spritesheetsNr;
		for(int i = 0; i < data.spritesheetsNr; i++)
			data.epaths[i] = currentRoom->manager->getEnemyType(data.type).epaths[i];
			
		
		locf.x = (float)IRand((currentRoom->getSize().x - sprite->GetWidth() / currentRoom->tilesize - 1) * currentRoom->tilesize);
		locf.y = (float)IRand((currentRoom->getSize().y - sprite->GetHeight() / currentRoom->tilesize - 1) * currentRoom->tilesize);

		data.col.collisionBox.x = data.col.offset.x + (int)locf.x;
		data.col.collisionBox.y = data.col.offset.y + (int)locf.y;

		changeDrawLoc();

		tilePos = getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2));
		initOcupTile = getCurrentPos(newmath::make_ivec2(0, 0));
		finOcupTile = getCurrentPos(newmath::make_ivec2(sprite->GetWidth(), sprite->GetHeight()));

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
		currentSs.changeSpritesheet(data.epaths[x].rows, data.epaths[x].columns, newCurrentRow, sprite);
		currentSs.setFrameTime(data.epaths[x].frameTime);
	}

	void EnemyBase::findPath(newmath::ivec2 start, newmath::ivec2 newFinish, Map::Room* newRoom)
	{
		path = Pathfinder::get().findPath(start, newFinish, newRoom);
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
