#include "Player.h"
#include "../game.h"
#include <iostream>
#include <SDL.h>
#include "../template.h"
#include "newmath.h"
#include "CollisionCheck.h"


namespace Character
{
	
	void Player::Init(GameSpace::Surface* newScreen, Map::Room* newRoom, Map::MapManager* newMapManager)
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

		collisionBox.setCollisionBox(loc.x + 14, loc.y + 14, 36, 36);
	
		weapon.Init(drawloc);
	}

	void Player::checkIdle()
	{
	
		if (currentState == idle && (move.side[0] || move.side[1] || move.side[2] || move.side[3]))
		{

			if (isHoldingGun)
				currentState = runWithGun;
			else
				currentState = run;
			
			sprite.SetFile(new GameSpace::Surface(sspaths[currentState].path), sspaths[currentState].rows * sspaths[currentState].columns, directionFacing * sspaths[currentState].columns);
			//sprite.SetFrame(directionFacing * sspaths[1].columns);
			
			currentSs.changeSpritesheet(sspaths[currentState].path, sspaths[currentState].rows, sspaths[currentState].columns, &sprite);
		}
		else if ((currentState == run || currentState == runWithGun) && !(move.side[0] || move.side[1] || move.side[2] || move.side[3]))
		{
			currentState = idle;
			sprite.SetFile(new GameSpace::Surface(sspaths[currentState].path), sspaths[currentState].rows * sspaths[currentState].columns, directionFacing * sspaths[currentState].columns);
			
			currentSs.changeSpritesheet(sspaths[currentState].path, sspaths[currentState].rows, sspaths[currentState].columns, &sprite);
		}
		else if (isHoldingGun == true && currentState == run)
		{
			currentState = runWithGun;
			sprite.SetFile(new GameSpace::Surface(sspaths[currentState].path), sspaths[currentState].rows * sspaths[currentState].columns, directionFacing * sspaths[currentState].columns);

			currentSs.changeSpritesheet(sspaths[currentState].path, sspaths[currentState].rows, sspaths[currentState].columns, &sprite);
		}
		else if (isHoldingGun == false && currentState == runWithGun && (move.side[0] || move.side[1] || move.side[2] || move.side[3]))
		{
			currentState = run;
			sprite.SetFile(new GameSpace::Surface(sspaths[currentState].path), sspaths[currentState].rows * sspaths[currentState].columns, directionFacing * sspaths[currentState].columns);

			currentSs.changeSpritesheet(sspaths[currentState].path, sspaths[currentState].rows, sspaths[currentState].columns, &sprite);
		}
	}

	void Player::checkDirection(int n)
	{
		/*if (move.side[0] || move.side[1] || move.side[2] || move.side[3])
		{
			if (n % 2 == 0) //down or up
			{
			
				if (!(move.side[1] || move.side[3]))
				{
					if (directionFacing != n)
					{
						weapon.changeDirection(n);
						currentSs.setDirection(n);
						directionFacing = n;
					}
				
				}
			}
			else if (n % 2 == 1) //left or right
			{
				
				if (directionFacing != n)
				{
					weapon.changeDirection(n);
					currentSs.setDirection(n);
					directionFacing = n;
				}
				

			}
		}*/

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

		loc.x =  middleScreen.x;
		loc.y =  middleScreen.y;

		drawloc.x = middleScreen.x ;
		drawloc.y = middleScreen.y ;
	}



	void Player::updateRoom(Map::Room* newRoom)
	{
		currentRoom = newRoom;
	}

	void Player::moveDown(bool down)
	{
		move.side[0] = down;
		if (down)
		{
			move.side[2] = false;
			addMovement(0, 1);
			checkDirection(0);
		}
		
		checkIdle();
	}

	void Player::moveLeft(bool left)
	{
		move.side[1] = left;
		if (left)
		{
			move.side[3] = false;
			addMovement(-1, 0);
			checkDirection(1);
		}
		checkIdle();
	}

	void Player::moveUp(bool up)
	{
		move.side[2] = up;
		if (up)
		{
			move.side[0] = false;
			addMovement(0, -1);
			checkDirection(2);
		}
		checkIdle();
	}

	void Player::moveRight(bool right)
	{
		move.side[3] = right;
		if (right)
		{
			move.side[1] = false;
			addMovement(1, 0);
			checkDirection(3);
		}
		
		checkIdle();
	}

	void Player::changeActionSprite(int x)
	{
		sprite.SetFile(new GameSpace::Surface(sspaths[x].path), sspaths[x].rows * sspaths[x].columns, directionFacing * sspaths[x].columns);
		currentSs.setFrameTime(sspaths[x].frameTime);
	}	

	void Player::equipWeapon(int type) //type = 0 -> no weapon    5 - crossbow   6 - snowball  7 - snowman head
	{
		std::cout << "WEAPON" << std::endl;
		if (!type)
		{
			isHoldingGun = false;
			
			weapon.changeVisibility(false);

			checkIdle();
		}
		else if (type == crossbow)
		{
			isHoldingGun = true;

			weapon.changeVisibility(true);

			checkIdle();
		}
		
	}

	void Player::addMovement(int x, int y)
	{
		int xMap = 0, yMap = 0;

		loc.x += x;
		loc.y += y;

		collisionBox.collisionBox.x += x;
		collisionBox.collisionBox.y += y;

		int nextTile = CollisionCheck::isPlayerOverlapping(this, currentRoom, screen, x, y);

		

		if (nextTile == 0) //no collision
		{
			if ((x && drawloc.x == middleScreen.x) || (y && drawloc.y == middleScreen.y))
				currentRoom->moveMap(x, y);
			
			

			drawloc.x = loc.x - currentRoom->loc.x;
			drawloc.y = loc.y - currentRoom->loc.y;
		}
		else if (nextTile == 1)
		{
			loc.x -= x;
			loc.y -= y;

			collisionBox.collisionBox.x -= x;
			collisionBox.collisionBox.y -= y;
		}
		else if (nextTile == 3)
		{
			std::cout << "PORTAL" << std::endl;
			if (x > 0 && loc.x > (currentRoom->size.x - 4) * currentRoom->tilesize)
			{
				std::cout << "Going Right: " << currentRoom->roomNumber << " New x: " << currentRoom->roomNumber % mapManager->roomAm.x + 1 << std::endl;
				currentRoom = mapManager->SwitchRoom(currentRoom->roomNumber % mapManager->roomAm.x + 1, currentRoom->roomNumber / mapManager->roomAm.x);
				std::cout << "Switched Room" << std::endl;
				currentRoom->loc.x = 0;
				currentRoom->loc.y = (currentRoom->size.y / 2) * currentRoom->tilesize + currentRoom->tilesize / 2 - screen->GetHeight() / 2;

				loc.x = currentRoom->tilesize - sprite.GetWidth() / 2 + currentRoom->tilesize / 2;
				loc.y = (currentRoom->size.y / 2) * currentRoom->tilesize - currentRoom->tilesize / 2; 

				collisionBox.collisionBox.x = loc.x + 14;
				collisionBox.collisionBox.y = loc.y + 14;

				drawloc.x = loc.x - currentRoom->loc.x;
				drawloc.y = loc.y - currentRoom->loc.y;

				std::cout << "Going Right: " << currentRoom->roomNumber << " Room x: " << currentRoom->loc.x << " Room y: " << currentRoom->loc.y << std::endl;

				//for (int i = 0; i < 4; i++)
					//std::cout << currentRoom->doors[i] << " ";
				//std::cout << std::endl;
			}
			else if (x < 0 && loc.x < 4 * currentRoom->tilesize)
			{
				std::cout << "Going Left: " << currentRoom->roomNumber << " New x: " << currentRoom->roomNumber % mapManager->roomAm.x - 1 << std::endl;
				currentRoom = mapManager->SwitchRoom(currentRoom->roomNumber % mapManager->roomAm.x - 1, currentRoom->roomNumber / mapManager->roomAm.x);
				std::cout << "Switched Room" << std::endl;
				currentRoom->loc.x = (currentRoom->size.x - screen->GetWidth() / currentRoom->tilesize) * currentRoom->tilesize;
				currentRoom->loc.y = (currentRoom->size.y / 2) * currentRoom->tilesize + currentRoom->tilesize / 2 - screen->GetHeight() / 2;

				loc.x = (currentRoom->size.x - 1) * currentRoom->tilesize - sprite.GetWidth() / 2 - currentRoom->tilesize / 2;
				loc.y = (currentRoom->size.y / 2) * currentRoom->tilesize - currentRoom->tilesize / 2; 

				collisionBox.collisionBox.x = loc.x + 14;
				collisionBox.collisionBox.y = loc.y + 14;

				drawloc.x = loc.x - currentRoom->loc.x;
				drawloc.y = loc.y - currentRoom->loc.y;
				std::cout << "Going Left: " << currentRoom->roomNumber << " Room x: " << currentRoom->loc.x << " Room y: " << currentRoom->loc.y << std::endl;

				//for (int i = 0; i < 4; i++)
					//std::cout << currentRoom->doors[i] << " ";
				//std::cout << std::endl;
			}
			else if (y > 0 && loc.y > (currentRoom->size.y - 4) * currentRoom->tilesize)
			{
				std::cout << "Going Down: " << currentRoom->roomNumber << " New y: " << currentRoom->roomNumber / mapManager->roomAm.x + 1 << std::endl;
				currentRoom = mapManager->SwitchRoom(currentRoom->roomNumber % mapManager->roomAm.x, currentRoom->roomNumber / mapManager->roomAm.x + 1);
				std::cout << "Switched Room" << std::endl;
				currentRoom->loc.x = (currentRoom->size.x / 2 - (currentRoom->size.x + 1) % 2) * currentRoom->tilesize + currentRoom->tilesize / 2 - screen->GetWidth() / 2;
				currentRoom->loc.y = 0;

				loc.x = (currentRoom->size.x / 2 - (currentRoom->size.x + 1) % 2) * currentRoom->tilesize - currentRoom->tilesize / 2;
				loc.y = 2 * currentRoom->tilesize - sprite.GetHeight() / 2 + currentRoom->tilesize / 2;

				collisionBox.collisionBox.x = loc.x + 14;
				collisionBox.collisionBox.y = loc.y + 14;

				drawloc.x = loc.x - currentRoom->loc.x;
				drawloc.y = loc.y - currentRoom->loc.y;


				std::cout << "Going Down: " << currentRoom->roomNumber << " Player x: " << loc.x << " Player y: " << loc.y << " Room: " <<  currentRoom->roomNumber << " Room x: " << currentRoom->loc.x << " Room y: " << currentRoom->loc.y << std::endl;

				//for (int i = 0; i < 4; i++)
					//std::cout << currentRoom->doors[i] << " ";
				//std::cout << std::endl;
			}
			else if (y < 0 && loc.y < 4 * currentRoom->tilesize)
			{
				std::cout << "Going Up: " << currentRoom->roomNumber << " New y: " << currentRoom->roomNumber / mapManager->roomAm.x - 1 << std::endl;
				currentRoom = mapManager->SwitchRoom(currentRoom->roomNumber % mapManager->roomAm.x, currentRoom->roomNumber / mapManager->roomAm.x - 1);
				std::cout << "Switched Room" << std::endl;
				currentRoom->loc.x = (currentRoom->size.x / 2 - (currentRoom->size.x + 1) % 2) * currentRoom->tilesize + currentRoom->tilesize / 2 - screen->GetWidth() / 2;
				currentRoom->loc.y = (currentRoom->size.y - screen->GetHeight() / currentRoom->tilesize) * currentRoom->tilesize;

				loc.x = (currentRoom->size.x / 2 - (currentRoom->size.x + 1) % 2) * currentRoom->tilesize - currentRoom->tilesize / 2;
				loc.y = (currentRoom->size.y - 1) * currentRoom->tilesize - sprite.GetHeight() / 2 - currentRoom->tilesize / 2; 

				collisionBox.collisionBox.x = loc.x + 14;
				collisionBox.collisionBox.y = loc.y + 14;

				drawloc.x = loc.x - currentRoom->loc.x;
				drawloc.y = loc.y - currentRoom->loc.y;

				std::cout << "Going Up: " << currentRoom->roomNumber << " Player x: " << loc.x << " Player y: " << loc.y << " Room: " << currentRoom->roomNumber << " Room x: " << currentRoom->loc.x << " Room y: " << currentRoom->loc.y << std::endl;

				//for (int i = 0; i < 4; i++)
					//std::cout << currentRoom->doors[i] << " ";
				//std::cout << std::endl;
			}
			else
			{
				if ((x && drawloc.x == middleScreen.x) || (y && drawloc.y == middleScreen.y))
					currentRoom->moveMap(x, y);



				drawloc.x = loc.x - currentRoom->loc.x;
				drawloc.y = loc.y - currentRoom->loc.y;
			}
			//std::cout << "Entered PORTAL" << std::endl;
		}	

	}

	

	void Player::drawPlayer()
	{
		
		
	}


	void Player::Update(float deltaTime)
	{
		//std::cout << directionFacing << std::endl;

		if (directionFacing == 0)
		{
			currentSs.drawNextSprite(deltaTime, screen, drawloc.x, drawloc.y);
			if (weapon.visible)
				weapon.sprite.Draw(screen, drawloc.x, drawloc.y);
			screen->Box(collisionBox.collisionBox.x - currentRoom->loc.x, collisionBox.collisionBox.y - currentRoom->loc.y, collisionBox.collisionBox.x + collisionBox.collisionBox.width - currentRoom->loc.x, collisionBox.collisionBox.y + collisionBox.collisionBox.height - currentRoom->loc.y, 0xff0000);
		
			screen->Box(drawloc.x, drawloc.y, drawloc.x + 64, drawloc.y + 64, 0xff0000);

		}
		else
		{
			if (weapon.visible)
				weapon.sprite.Draw(screen, drawloc.x, drawloc.y);
			currentSs.drawNextSprite(deltaTime, screen, drawloc.x, drawloc.y);
			screen->Box(collisionBox.collisionBox.x - currentRoom->loc.x, collisionBox.collisionBox.y - currentRoom->loc.y, collisionBox.collisionBox.x + collisionBox.collisionBox.width - currentRoom->loc.x, collisionBox.collisionBox.y + collisionBox.collisionBox.height - currentRoom->loc.y, 0xff0000);
		
			screen->Box(drawloc.x, drawloc.y, drawloc.x + 64, drawloc.y + 64, 0xff0000);
		}
	}
	
}