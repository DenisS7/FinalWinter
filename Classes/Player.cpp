#include "Player.h"
#include "../game.h"
#include <iostream>
#include <SDL.h>
#include "../template.h"
#include "newmath.h"
#include "CollisionCheck.h"


namespace Character
{
	
	void Player::init(GameSpace::Surface* newScreen, Map::Room* newRoom, Map::MapManager* newMapManager, const Uint8* newKeystate)
	{
		sspaths[1].path = "assets/Player/player_idle.png";
		sspaths[1].columns = 6;
		sspaths[1].frameTime = 100.0f;

		sspaths[2].path = "assets/Player/player_run.png";
		sspaths[2].columns = 8;
		sspaths[2].frameTime = 100.0f;

		sspaths[3].path = "assets/Player/player_dead.png";
		sspaths[3].columns = 7;
		sspaths[3].frameTime = 100.0f;

		sspaths[4].path = "assets/Player/player_run_body.png";
		sspaths[4].columns = 8;
		sspaths[4].frameTime = 100.0f;

		sspaths[1].rows = sspaths[2].rows = sspaths[3].rows = sspaths[4].rows = sspaths[5].rows = 4;
		currentSs.setDirection(0);
		currentSs.setFrameTime(sspaths[1].frameTime);
		updateScreen(newScreen);
		updateRoom(newRoom);
		updateMapManager(newMapManager);
		updateKeystate(newKeystate);

		collisionBox.setOffset(14, 12);
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
		int x = ((int)locf.x + 32) / currentRoom->tilesize;
		int y = ((int)locf.y + 32) / currentRoom->tilesize;
		newmath::ivec2 pos = newmath::make_ivec2(x, y);
		return pos;
	}

	void Player::checkDirection(int n)
	{
		if (directionFacing != n)
		{
			if(move.side[n] && !move.side[directionFacing])
			{ 
				weapon.changeDirection(n);
				currentSs.setDirection(n);
				directionFacing = n;
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

		locf.x = (float)middleScreen.x;
		locf.y = (float)middleScreen.y;

		drawLocf.x = (float)middleScreen.x;
		drawLocf.y = (float)middleScreen.y;

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
		moveDown(keystate[SDL_SCANCODE_DOWN], deltaTime);
		moveLeft(keystate[SDL_SCANCODE_LEFT], deltaTime);
		moveUp(keystate[SDL_SCANCODE_UP], deltaTime);
		moveRight(keystate[SDL_SCANCODE_RIGHT], deltaTime);

		weapon.reload(deltaTime);
	}

	void Player::moveDown(bool down, float deltaTime)
	{
		move.side[0] = down;
		if (down)
		{
			//move.side[2] = false;
			addMovement(0, 1, deltaTime);
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
			isHoldingGun = false;
			
			weapon.changeVisibility(false);

			checkIdle();
		}
		else if (type)
		{
			isHoldingGun = true;
			isHoldingProjectile = false;

			weapon.changeVisibility(true);

			checkIdle();
		}
		else if (type == snowball)
		{
			isHoldingGun = false;
			isHoldingProjectile = true;

			weapon.changeVisibility(false);

			checkIdle();
		}
		else if (type == snowman)
		{
			isHoldingGun = false;
			isHoldingProjectile = true;

			weapon.changeVisibility(false);

			checkIdle();
		}
	}

	void Player::shootProjectile(int type)
	{
		if (type)
		{
			equipWeapon(crossbow);
			weapon.shootArrows();
			std::cout << "SHOOT";
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

		if (nextTile == 0) //no collision
		{
			//
			if ((x && newmath::inRangef(drawLocf.x, (float)middleScreen.x - 4, (float)middleScreen.x + 4)) || ((y && newmath::inRangef(drawLocf.y, (float)middleScreen.y - 4, (float)middleScreen.y + 4))))
				currentRoom->moveMap(x, y, deltaTime);
			
			drawLocf.x = locf.x - currentRoom->locf.x;
			drawLocf.y = locf.y - currentRoom->locf.y;
		}
		else if (nextTile == 1)
		{

			locf.x -= move.speed * deltaTime * x;
			locf.y -= move.speed * deltaTime * y;

			
			collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);
		}
		else if (nextTile == 3)
		{
			//std::cout << "PORTAL" << std::endl;
			if (x > 0 && locf.x > (currentRoom->size.x - 4) * currentRoom->tilesize)
			{
				//std::cout << "Going Right: " << currentRoom->roomNumber << " New x: " << currentRoom->roomNumber % mapManager->roomAm.x + 1 << std::endl;
				currentRoom = mapManager->switchRoom(currentRoom->roomNumber % mapManager->roomAm.x + 1, currentRoom->roomNumber / mapManager->roomAm.x);
				//std::cout << "Switched Room" << std::endl;
				currentRoom->locf.x = 0;
				currentRoom->locf.y = (float) ((currentRoom->size.y / 2) * currentRoom->tilesize + currentRoom->tilesize / 2 - screen->GetHeight() / 2);

				currentRoom->updateEnemies();

				locf.x = (float) (currentRoom->tilesize - sprite.GetWidth() / 2 + currentRoom->tilesize / 2);
				locf.y = (float) ((currentRoom->size.y / 2) * currentRoom->tilesize - currentRoom->tilesize / 2); 

				collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);

				drawLocf.x = locf.x - currentRoom->locf.x;
				drawLocf.y = locf.y - currentRoom->locf.y;

				//std::cout << "Going Right: " << currentRoom->roomNumber << " Room x: " << currentRoom->locf.x << " Room y: " << currentRoom->locf.y << std::endl;

				for (int i = 0; i < weapon.arrows.size(); i++)
					weapon.arrows[i]->deleteArrow();
				weapon.arrows.clear();
				//for (int i = 0; i < 4; i++)
					//std::cout << currentRoom->doors[i] << " ";
				//std::cout << std::endl;
			}
			else if (x < 0 && locf.x < 4 * currentRoom->tilesize)
			{
				//std::cout << "Going Left: " << currentRoom->roomNumber << " New x: " << currentRoom->roomNumber % mapManager->roomAm.x - 1 << std::endl;
				currentRoom = mapManager->switchRoom(currentRoom->roomNumber % mapManager->roomAm.x - 1, currentRoom->roomNumber / mapManager->roomAm.x);
				//std::cout << "Switched Room" << std::endl;
				currentRoom->locf.x = (float)((currentRoom->size.x - screen->GetWidth() / currentRoom->tilesize) * currentRoom->tilesize);
				currentRoom->locf.y = (float)((currentRoom->size.y / 2) * currentRoom->tilesize + currentRoom->tilesize / 2 - screen->GetHeight() / 2);

				currentRoom->updateEnemies();

				locf.x = (float)((currentRoom->size.x - 1) * currentRoom->tilesize - sprite.GetWidth() / 2 - currentRoom->tilesize / 2);
				locf.y = (float)((currentRoom->size.y / 2) * currentRoom->tilesize - currentRoom->tilesize / 2);

				collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);

				drawLocf.x = locf.x - currentRoom->locf.x;
				drawLocf.y = locf.y - currentRoom->locf.y;
				//std::cout << "Going Left: " << currentRoom->roomNumber << " Room x: " << currentRoom->locf.x << " Room y: " << currentRoom->locf.y << std::endl;

				for (int i = 0; i < weapon.arrows.size(); i++)
					weapon.arrows[i]->deleteArrow();
				weapon.arrows.clear();
				//for (int i = 0; i < 4; i++)
					//std::cout << currentRoom->doors[i] << " ";
				//std::cout << std::endl;
			}
			else if (y > 0 && locf.y > (currentRoom->size.y - 4) * currentRoom->tilesize)
			{
				//std::cout << "Going Down: " << currentRoom->roomNumber << " New y: " << currentRoom->roomNumber / mapManager->roomAm.x + 1 << std::endl;
				currentRoom = mapManager->switchRoom(currentRoom->roomNumber % mapManager->roomAm.x, currentRoom->roomNumber / mapManager->roomAm.x + 1);
				//std::cout << "Switched Room" << std::endl;
				currentRoom->locf.x = (float)((currentRoom->size.x / 2 - (currentRoom->size.x + 1) % 2) * currentRoom->tilesize + currentRoom->tilesize / 2 - screen->GetWidth() / 2);
				currentRoom->locf.y = 0;

				currentRoom->updateEnemies();

				locf.x = (float)((currentRoom->size.x / 2 - (currentRoom->size.x + 1) % 2) * currentRoom->tilesize - currentRoom->tilesize / 2);
				locf.y = (float)(2 * currentRoom->tilesize - sprite.GetHeight() / 2 + currentRoom->tilesize / 2);

				collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);

				drawLocf.x = locf.x - currentRoom->locf.x;
				drawLocf.y = locf.y - currentRoom->locf.y;

				for (int i = 0; i < weapon.arrows.size(); i++)
					weapon.arrows[i]->deleteArrow();
				weapon.arrows.clear();
				//std::cout << "Going Down: " << currentRoom->roomNumber << " Player x: " << locf.x << " Player y: " << locf.y << " Room: " <<  currentRoom->roomNumber << " Room x: " << currentRoom->locf.x << " Room y: " << currentRoom->locf.y << std::endl;

				//for (int i = 0; i < 4; i++)
					//std::cout << currentRoom->doors[i] << " ";
				//std::cout << std::endl;
			}
			else if (y < 0 && locf.y < 4 * currentRoom->tilesize)
			{
				//std::cout << "Going Up: " << currentRoom->roomNumber << " New y: " << currentRoom->roomNumber / mapManager->roomAm.x - 1 << std::endl;
				currentRoom = mapManager->switchRoom(currentRoom->roomNumber % mapManager->roomAm.x, currentRoom->roomNumber / mapManager->roomAm.x - 1);
				//std::cout << "Switched Room" << std::endl;
				currentRoom->locf.x = (float)((currentRoom->size.x / 2 - (currentRoom->size.x + 1) % 2) * currentRoom->tilesize + currentRoom->tilesize / 2 - screen->GetWidth() / 2);
				currentRoom->locf.y = (float)((currentRoom->size.y - screen->GetHeight() / currentRoom->tilesize) * currentRoom->tilesize);

				currentRoom->updateEnemies();

				locf.x = (float)((currentRoom->size.x / 2 - (currentRoom->size.x + 1) % 2) * currentRoom->tilesize - currentRoom->tilesize / 2);
				locf.y = (float)((currentRoom->size.y - 1) * currentRoom->tilesize - sprite.GetHeight() / 2 - currentRoom->tilesize / 2);

				collisionBox.setCollisionBox((int)locf.x + collisionBox.offset.x, (int)locf.y + collisionBox.offset.y, 36, 36);

				drawLocf.x = locf.x - currentRoom->locf.x;
				drawLocf.y = locf.y - currentRoom->locf.y;

				for (int i = 0; i < weapon.arrows.size(); i++)
					weapon.arrows[i]->deleteArrow();
				weapon.arrows.clear();
				//std::cout << "Going Up: " << currentRoom->roomNumber << " Player x: " << locf.x << " Player y: " << locf.y << " Room: " << currentRoom->roomNumber << " Room x: " << currentRoom->locf.x << " Room y: " << currentRoom->locf.y << std::endl;

				//for (int i = 0; i < 4; i++)
					//std::cout << currentRoom->doors[i] << " ";
				//std::cout << std::endl;
			}
			else
			{
				if ((x && (int) drawLocf.x == middleScreen.x) || (y && (int)drawLocf.y == middleScreen.y))
					currentRoom->moveMap(x, y, deltaTime);

				drawLocf.x = locf.x - currentRoom->locf.x;
				drawLocf.y = locf.y - currentRoom->locf.y;
			}
			//std::cout << "Entered PORTAL" << std::endl;
		}	

	}

	void Player::update(float deltaTime)
	{
		//std::cout << directionFacing << std::endl;
		//std::cout << "DOWN: " << move.side[0] << " UP: " << move.side[2] << " RIGHT: " << move.side[3] << " LEFT: " << move.side[1] << std::endl;
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