#include "Player.h"
#include "../game.h"
#include <iostream>
#include <SDL.h>
#include "../template.h"
#include "newmath.h"
#include "CollisionCheck.h"



namespace Character
{
	void Player::restart()
	{
		
		locf.x = drawLocf.x = (float)middleScreen.x - 50;
		locf.y = drawLocf.y = (float)middleScreen.y - 50;
		collisionBox.setOffset(14, 14);
		collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);
		won = false;
		currentState = 1;
		directionFacing = 0;
		isHoldingGun = false;
		health = 100;
		isDead = false;
		changeActionSprite(1);
		currentSs.setFrame(0);
		for (int i = 0; i < weapon.arrows.size(); i++)
			weapon.deleteArrow(weapon.arrows[i]);
		weapon.changeDirection(0);
		mapManager->restart();
		currentRoom = &mapManager->rooms[mapManager->getStart().x + mapManager->getRoomAm().x * mapManager->getStart().y];
		points = 0;
		SDL_Delay(100);
		locf.x = drawLocf.x = (float)middleScreen.x - 50;
		locf.y = drawLocf.y = (float)middleScreen.y - 50;	
	}

	void Player::init(GameSpace::Surface* newScreen, Map::Room* newRoom, Map::MapManager* newMapManager, const Uint8* newKeystate)
	{
		currentSs.setDirection(0);
		currentSs.setFrameTime(sspaths[1].frameTime);
		updateScreen(newScreen);
		updateRoom(newRoom);
		updateMapManager(newMapManager);
		updateKeystate(newKeystate);

		move.speed = currentRoom->speed = 0.2f;
		collisionBox.setOffset(14, 14);
		collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);
		
		weapon.Init(drawLocf, this);
	}

	void Player::checkIdle()
	{
		if (currentState == idle && (move.side[0] || move.side[1] || move.side[2] || move.side[3]))
		{

			if (isHoldingGun)
				currentState = runWithGun;
			else
				currentState = run;
			
			changeActionSprite(currentState);
		}
		else if ((currentState == run || currentState == runWithGun) && !(move.side[0] || move.side[1] || move.side[2] || move.side[3]))
		{

			currentState = idle;
			changeActionSprite(currentState);
		}
		else if (isHoldingGun == true && currentState == run)
		{
			currentState = runWithGun;
			changeActionSprite(currentState);
		}
		else if (isHoldingGun == false && currentState == runWithGun && (move.side[0] || move.side[1] || move.side[2] || move.side[3]))
		{
			currentState = run;
			changeActionSprite(currentState);
		}
	}

	

	newmath::ivec2 Player::getCurrentPos()
	{
		int x = ((int)locf.x + sprite.GetWidth() / 2) / 32;
		int y = ((int)locf.y + sprite.GetHeight() / 2) / 32;
		newmath::ivec2 pos = newmath::make_ivec2(x, y);
		return pos;
	}

	void Player::speedBoost()
	{
		move.speed = 0.3f;
		currentRoom->speed = 0.3f;
		potionTimers[speed] = 9000;
	}

	void Player::damageBoost()
	{
		weapon.setDamage(35);
		potionTimers[damage] = 5000;
	
	}

	void Player::firerateBoost()
	{
		weapon.setReloadTime(100.0f);
		potionTimers[firerate] = 5000;
	
	}

	void Player::createShield()
	{
	}

	void Player::checkPotions(float deltaTime)
	{
		if (potionTimers[speed])
		{
			potionTimers[speed] -= deltaTime;
			if (potionTimers[speed] <= 0)
			{
				potionTimers[speed] = 0;
				if (isHoldingGun)
				{
					move.speed = 0.2f;
					currentRoom->speed = 0.2f;
				}
				else
				{
					move.speed = 0.25f;
					currentRoom->speed = 0.2f;
				}
			}
		}
		if (potionTimers[firerate])
		{
			potionTimers[firerate] -= deltaTime;
			if (potionTimers[firerate] <= 0)
			{
				potionTimers[firerate] = 0;
				weapon.setReloadTime(300.0f);
			}
		}
		if (potionTimers[damage])
		{
			potionTimers[damage] -= deltaTime;
			if (potionTimers[damage] <= 0)
			{
				potionTimers[damage] = 0;
				weapon.setDamage(25);
			}
		}

	}

	void Player::die()
	{
		equipWeapon(0);
		isDead = true;
		changeActionSprite(dead);
	}

	

	void Player::modifyPoints(int newPoints)
	{
		points += newPoints;
	}

	

	void Player::takeDamage(float damage)
	{
		health -= damage;
		if (health <= 0 && !isDead)
			die();
		health = newmath::clampf(health, 0, 100);
	}

	void Player::checkDirection(int n)
	{
		if (directionFacing != n)
		{
			if((move.side[n] && !move.side[directionFacing]) || weapon.isShooting)
			{ 
				
				weapon.changeDirection(n);
				currentSs.setDirection(n);
				directionFacing = n;
				weapon.reloading = weapon.reloadTime;
			}
		}
	}

	void Player::updateMapManager(Map::MapManager* newMapManager)
	{
		mapManager = newMapManager;
	}

	void Player::updateScreen(GameSpace::Surface* newScreen)
	{
		screen = newScreen;
		middleScreen.x = screen->GetWidth() / 2 - sprite.GetWidth() / 2;
		middleScreen.y = screen->GetHeight() / 2 - sprite.GetHeight() / 2;
	
		locf.x = drawLocf.x = (float)middleScreen.x - 50;
		locf.y = drawLocf.y = (float)middleScreen.y - 50;


		collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);
	}

	void Player::updateRoom(Map::Room* newRoom)
	{
		currentRoom = newRoom;
	}

	void Player::updateKeystate(const Uint8* keystate)
	{
		this->keystate = keystate;
	}

	void Player::input(float deltaTime)
	{
		if (!isDead)
		{
			moveDown(keystate[SDL_SCANCODE_S], deltaTime);
			moveLeft(keystate[SDL_SCANCODE_A], deltaTime);
			moveUp(keystate[SDL_SCANCODE_W], deltaTime);
			moveRight(keystate[SDL_SCANCODE_D], deltaTime);

			weapon.reload(deltaTime);
		}
	}

	void Player::mouseLoc(int x, int y)
	{
		mousePosition.x = (float)x;
		mousePosition.y = (float)y;
		if (weapon.isShooting)
		{
			const float distx = (float)screen->GetWidth() * ((float)y / screen->GetHeight());
			const float disty = (float)screen->GetHeight() * ((float)x / screen->GetWidth());

			const float minx = GameSpace::Min(distx, screen->GetWidth() - distx);
			const float maxx = screen->GetWidth() - minx;


			const float miny = GameSpace::Min(disty, screen->GetHeight() - disty);
			const float maxy = screen->GetHeight() - miny;


			if (x >= minx && x <= maxx)
			{
				if (y < screen->GetHeight() / 2)
					checkDirection(2);
				else checkDirection(0);
			}
			else if (y >= miny && y <= maxy)
			{
				if (x < screen->GetWidth() / 2)
					checkDirection(1);
				else checkDirection(3);
			}
		}
	}

	void Player::moveDown(bool down, float deltaTime)
	{
		move.side[0] = down;
		if (down)
		{
			//move.side[2] = false;
			addMovement(0, 1, deltaTime);
			if (!weapon.isShooting)
				checkDirection(0);
		}
		
		checkIdle();
	}

	void Player::moveLeft(bool left, float deltaTime)
	{
		move.side[1] = left;
		if (left)
		{
			//move.side[3] = false;
			addMovement(-1, 0, deltaTime);
			if (!weapon.isShooting)
				checkDirection(1);
		}
		checkIdle();
	}

	void Player::moveUp(bool up, float deltaTime)
	{
		move.side[2] = up;
		if (up)
		{
			//move.side[0] = false;
			addMovement(0, -1, deltaTime);
			if (!weapon.isShooting)
				checkDirection(2);
		}
		checkIdle();
	}

	void Player::moveRight(bool right, float deltaTime)
	{
		move.side[3] = right;
		if (right)
		{
			//move.side[1] = false;
			addMovement(1, 0, deltaTime);
			if (!weapon.isShooting)
				checkDirection(3);
		}
		
		checkIdle();
	}

	void Player::changeActionSprite(int x)
	{
		sprite.SetFile(new GameSpace::Surface(sspaths[x].path), sspaths[x].rows * sspaths[x].columns, directionFacing * sspaths[x].columns);
		currentSs.changeSpritesheet(sspaths[x].path, sspaths[x].rows, sspaths[x].columns, directionFacing, &sprite);
		currentSs.setFrameTime(sspaths[x].frameTime);
	}	

	void Player::equipWeapon(int type) //type = 0 -> no weapon    5 - crossbow   6 - snowball  7 - snowman head
	{
		if (!type)
		{
			move.speed += 0.05f;
			currentRoom->speed += 0.05f;

			isHoldingGun = false;
			
			weapon.changeVisibility(false);

			checkIdle();
		}
		else if (type && !isHoldingGun)
		{
			move.speed -= 0.05f;
			currentRoom->speed -= 0.05f;
			isHoldingGun = true;

			weapon.changeVisibility(true);

			checkIdle();
		}

	}

	void Player::shootProjectile(int type, int mousex, int mousey)
	{
		if (type)
		{
			equipWeapon(crossbow);
			weapon.shootArrows();
		}
		else
		{
			if (weapon.reloading < weapon.reloadTime / 2)
				weapon.reloading = weapon.reloadTime / 2;
			weapon.stopShooting();
		}
	}

	void Player::addMovement(int x, int y, float deltaTime)
	{
		int xMap = 0, yMap = 0;
		locf.x += move.speed * deltaTime * x;
		locf.y += move.speed * deltaTime * y;

		collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);

		int nextTile = CollisionCheck::isPlayerOverlapping(this, currentRoom);

		if (nextTile == nonCollide) //no collision
		{
			if ((x && newmath::inRangef(drawLocf.x, (float)middleScreen.x - 10, (float)middleScreen.x + 10)) || ((y && newmath::inRangef(drawLocf.y, (float)middleScreen.y - 10, (float)middleScreen.y + 10))))
				currentRoom->moveMap(x, y, deltaTime);
			
			drawLocf.x = locf.x - currentRoom->getLocation().x;
			drawLocf.y = locf.y - currentRoom->getLocation().y;
		}
		else if (nextTile == collide || nextTile == portalInactive)
		{

			locf.x -= move.speed * deltaTime * x;
			locf.y -= move.speed * deltaTime * y;

			collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);
		}
		else if (nextTile == portalActive)
		{
			GameSpace::vec2 newRoomLocation;
			Map::Room* pastRoom = currentRoom;
			if (x > 0 && locf.x > (currentRoom->getSize().x - 4) * currentRoom->tilesize)
			{
				currentRoom = mapManager->switchRoom(currentRoom->getRoomNumber() % mapManager->getRoomAm().x + 1, currentRoom->getRoomNumber() / mapManager->getRoomAm().x);
				newRoomLocation = GameSpace::vec2(0, (float)((currentRoom->getSize().y / 2) * currentRoom->tilesize + currentRoom->tilesize / 2 - screen->GetHeight() / 2));
				currentRoom->setLocation(newRoomLocation);

				currentRoom->updateEnemies();

				locf.x = (float) (currentRoom->tilesize - sprite.GetWidth() / 2 + currentRoom->tilesize / 2) + 10;
				locf.y = (float) ((currentRoom->getSize().y / 2) * currentRoom->tilesize - currentRoom->tilesize / 2); 

				collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);

				drawLocf.x = locf.x - currentRoom->getLocation().x;
				drawLocf.y = locf.y - currentRoom->getLocation().y;


				for (int i = 0; i < weapon.arrows.size(); i++)
					weapon.arrows[i]->deleteArrow();
				weapon.arrows.clear();
			}
			else if (x < 0 && locf.x < 4 * currentRoom->tilesize)
			{
				currentRoom = mapManager->switchRoom(currentRoom->getRoomNumber() % mapManager->getRoomAm().x - 1, currentRoom->getRoomNumber() / mapManager->getRoomAm().x);
				newRoomLocation = GameSpace::vec2((float)((currentRoom->getSize().x - screen->GetWidth() / currentRoom->tilesize) * currentRoom->tilesize), (float)((currentRoom->getSize().y / 2) * currentRoom->tilesize + currentRoom->tilesize / 2 - screen->GetHeight() / 2));
				currentRoom->setLocation(newRoomLocation);

				currentRoom->updateEnemies();

				locf.x = (float)((currentRoom->getSize().x - 1) * currentRoom->tilesize - sprite.GetWidth() / 2 - currentRoom->tilesize / 2);
				locf.y = (float)((currentRoom->getSize().y / 2) * currentRoom->tilesize - currentRoom->tilesize / 2);

				collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);

				drawLocf.x = locf.x - currentRoom->getLocation().x;
				drawLocf.y = locf.y - currentRoom->getLocation().y;

				for (int i = 0; i < weapon.arrows.size(); i++)
					weapon.arrows[i]->deleteArrow();
				weapon.arrows.clear();
			}
			else if (y > 0 && locf.y > (currentRoom->getSize().y - 4) * currentRoom->tilesize)
			{
				currentRoom = mapManager->switchRoom(currentRoom->getRoomNumber() % mapManager->getRoomAm().x, currentRoom->getRoomNumber() / mapManager->getRoomAm().x + 1);
				newRoomLocation = GameSpace::vec2((float)((currentRoom->getSize().x / 2 - (currentRoom->getSize().x + 1) % 2) * currentRoom->tilesize + currentRoom->tilesize / 2 - screen->GetWidth() / 2), 0);
				currentRoom->setLocation(newRoomLocation);

				currentRoom->updateEnemies();

				locf.x = (float)((currentRoom->getSize().x / 2 - (currentRoom->getSize().x + 1) % 2) * currentRoom->tilesize - currentRoom->tilesize / 2);
				locf.y = (float)(2 * currentRoom->tilesize - sprite.GetHeight() / 2 + currentRoom->tilesize / 2) + 10;

				collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);

				drawLocf.x = locf.x - currentRoom->getLocation().x;
				drawLocf.y = locf.y - currentRoom->getLocation().y;

				for (int i = 0; i < weapon.arrows.size(); i++)
					weapon.arrows[i]->deleteArrow();
				weapon.arrows.clear();
			}
			else if (y < 0 && locf.y < 4 * currentRoom->tilesize)
			{
				currentRoom = mapManager->switchRoom(currentRoom->getRoomNumber() % mapManager->getRoomAm().x, currentRoom->getRoomNumber() / mapManager->getRoomAm().x - 1);
				newRoomLocation = GameSpace::vec2((float)((currentRoom->getSize().x / 2 - (currentRoom->getSize().x + 1) % 2) * currentRoom->tilesize + currentRoom->tilesize / 2 - screen->GetWidth() / 2), (float)((currentRoom->getSize().y - screen->GetHeight() / currentRoom->tilesize) * currentRoom->tilesize));
				currentRoom->setLocation(newRoomLocation);

				currentRoom->updateEnemies();

				locf.x = (float)((currentRoom->getSize().x / 2 - (currentRoom->getSize().x + 1) % 2) * currentRoom->tilesize - currentRoom->tilesize / 2);
				locf.y = (float)((currentRoom->getSize().y - 1) * currentRoom->tilesize - sprite.GetHeight() / 2 - currentRoom->tilesize / 2);

				collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);

				drawLocf.x = locf.x - currentRoom->getLocation().x;
				drawLocf.y = locf.y - currentRoom->getLocation().y;

				for (int i = 0; i < weapon.arrows.size(); i++)
					weapon.arrows[i]->deleteArrow();
				weapon.arrows.clear();
			}
			if (currentRoom->getRoomNumber() == mapManager->getFinish())
			{
				currentSs.changeVisiblity(false);
				weapon.changeVisibility(false);
				won = true;
				currentRoom = pastRoom;
			}
			currentRoom->speed = move.speed;
		}	

	}


	void Player::drawUI()
	{
		healthbar.drawHealthbar((int)health, screen);
		score.printScore(screen, screen->GetPitch() - screen->GetPitch() / 40, screen->GetHeight() / 45, points);
	}

	void Player::drawPausePlayer(float deltaTime)
	{
		drawUI();
		if (directionFacing == 0)
		{
			currentSs.drawNextSprite(0, screen, drawLocf);
			if (weapon.visible)
				weapon.drawWeapon(0);
			for (int i = 0; i < weapon.arrows.size(); i++)
				weapon.arrows[i]->drawProjectile(screen, 0);
		}
		else
		{
			if (weapon.visible)
				weapon.drawWeapon(0);
			for (int i = 0; i < weapon.arrows.size(); i++)
				weapon.arrows[i]->drawProjectile(screen, 0);
			currentSs.drawNextSprite(0, screen, drawLocf);
		}
	}

	void Player::update(float deltaTime)
	{
		checkPotions(deltaTime);
		drawUI();
		if (directionFacing == 0)
		{
			currentSs.drawNextSprite(deltaTime, screen, drawLocf);
			if (weapon.visible)
				weapon.update(deltaTime);
			for (int i = 0; i < weapon.arrows.size(); i++)
				weapon.arrows[i]->UpdatePosition(deltaTime);
		}
		else
		{
			if (weapon.visible)
				weapon.update(deltaTime);
			for (int i = 0; i < weapon.arrows.size(); i++)
				weapon.arrows[i]->UpdatePosition(deltaTime);
			currentSs.drawNextSprite(deltaTime, screen, drawLocf);
		}
	}
	
}