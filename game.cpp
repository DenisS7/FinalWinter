#include "game.h"
#include "Classes/Room.h"
#include <iostream>

#include "MapManager.h"
#include "Classes/Player.h"

#include "Classes/Spritesheet.h"
#include "Classes/Other.h"
#include "../Classes/CollisionCheck.h"


namespace GameSpace
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------

	
	Map::MapManager manager;
	Character::Player player;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	CollisionCheck collisionManager;


	void Game::Init()
	{
		vec2 s;
		time_t t;
		srand((unsigned)time(&t));
		manager.setPlayer(&player);
		manager.setScreen(screen);
		manager.Initiate();
		manager.GenerateFirstRoom();

		player.Init(screen, &manager.rooms[manager.start.x + manager.start.y * manager.roomAm.x], &manager);
		manager.initiateEnemiesInRooms();
		player.equipWeapon(5);
	}

	void Game::Input(float deltaTime)
	{
		player.moveDown(keystate[SDL_SCANCODE_DOWN], deltaTime);
		player.moveLeft(keystate[SDL_SCANCODE_LEFT], deltaTime);
		player.moveUp(keystate[SDL_SCANCODE_UP], deltaTime);
		player.moveRight(keystate[SDL_SCANCODE_RIGHT], deltaTime);
	}

	void Game::KeyDown(int key)
	{
		std::cout << key << " " << SDL_SCANCODE_R << std::endl;
		if (key != SDL_SCANCODE_DOWN && key != SDL_SCANCODE_LEFT && key != SDL_SCANCODE_UP && key != SDL_SCANCODE_RIGHT)
		{
			int x;
			if (player.isHoldingGun)
				x = 0;
			else x = 5;
			switch (key)
			{
			case SDL_SCANCODE_E:
				player.equipWeapon(x), std::cout << "E SHOOT" << std::endl;
				break;
			case SDL_SCANCODE_R:
				player.shootProjectile(5), std::cout << "R SHOOT" << std::endl;
			default:
				break;
			}
		}
	}



	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}



	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------



	void Game::Tick(float deltaTime)
	{
		Input(deltaTime);
		
		//manager.rooms[player.currentRoom->roomNumber].DrawMap(screen);
		manager.rooms[player.currentRoom->roomNumber].UpdateMap(deltaTime, screen);
		player.Update(deltaTime);

	}
};
