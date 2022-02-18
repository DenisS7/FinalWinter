#include "game.h"
#include "Classes/Room.h"
#include <iostream>

#include "MapManager.h"
#include "Classes/Player.h"

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
		manager.initiate();
		manager.generateFirstRoom();

		player.init(screen, &manager.rooms[manager.start.x + manager.start.y * manager.roomAm.x], &manager, keystate);
		manager.initiateEnemiesInRooms();
		player.equipWeapon(5);
	}

	void Game::Input(float deltaTime)
	{
		player.input(deltaTime);
	}

	void Game::KeyDown(int key)
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
		//std::cout << player.currentRoom->tiles[273].colidable << std::endl;
		Input(deltaTime);
		manager.rooms[player.currentRoom->roomNumber].drawMap(screen);
		manager.rooms[player.currentRoom->roomNumber].updateMap(deltaTime, screen);
		player.update(deltaTime);

	}
};
