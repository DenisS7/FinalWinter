#include "EnemyBase.h"
#include "../MapManager.h"

namespace Character
{
	void EnemyBase::Init(int newType)
	{
		data.type = currentRoom->manager->enemyTypes[newType].type;
		data.health= currentRoom->manager->enemyTypes[newType].health;
		data.damagePerAttack = currentRoom->manager->enemyTypes[newType].damagePerAttack;
		data.damageOnCol = currentRoom->manager->enemyTypes[newType].damageOnCol;
		data.speed = currentRoom->manager->enemyTypes[newType].speed;
		data.col.collisionBox = currentRoom->manager->enemyTypes[newType].col.collisionBox;
		data.spritesheetsNr = currentRoom->manager->enemyTypes[newType].spritesheetsNr;
		for(int i = 0; i < data.spritesheetsNr; i++)
			data.epaths[i] = currentRoom->manager->enemyTypes[newType].epaths[i];
	}

	void EnemyBase::takeDamage(int damage)
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
		int lf = 1, rt = 1;
		int x = (int)locf.x / currentRoom->tilesize;
		int y = (int)locf.y / currentRoom->tilesize;
		int nrTiles = currentRoom->size.x * currentRoom->size.y;
		
	}

}
