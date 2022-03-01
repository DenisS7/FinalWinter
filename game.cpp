#include "game.h"
#include "Classes/Room.h"
#include <iostream>

#include "MapManager.h"
#include "Classes/Player.h"

#include "Classes/Snowball.h"

#include "../Classes/CollisionCheck.h"
#include "../Classes/CollisionComponent.h"
#include <fstream>


namespace GameSpace
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------


	Map::MapManager manager;
	Character::Player player;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	//Font font{ "assets/Font/font.png", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.:,;'|(!?)+-*/="};
	
	void Game::Restart()
	{

	}

	void Game::Init()
	{
		vec2 s;
		time_t t;
		srand((unsigned)time(&t));
		manager.setPlayer(&player);
		manager.setScreen(screen);
		manager.initiate();
		manager.generateFirstRoom();
		std::cout << " \n Generate \n";
		player.init(screen, &manager.rooms[manager.start.x + manager.start.y * manager.roomAm.x], &manager, keystate);
		manager.initiateEnemiesInRooms();
		
		player.equipWeapon(5);
		StartGame();
	}

	void Game::StartGame()
	{
		std::cout << "\n START \n";
		isRunning = true;
	}

	void Game::StopGame()
	{
		isRunning = false;
	}

	void Game::Input(float deltaTime)
	{
		player.input(deltaTime);
		player.mouseLoc(mouse.x, mouse.y);
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
		case SDL_SCANCODE_G:
			player.shootProjectile(5), std::cout << "R SHOOT" << std::endl;
			break;
			//default:
				//break;
		}

	}

	void Game::KeyUp(int key)
	{
		switch (key)
		{
		case SDL_SCANCODE_G:
			player.shootProjectile(0);
			break;
		case SDL_SCANCODE_T:
				Shutdown();
			//default:
				//break;
		}
	}

	void Game::MouseUp(int button)
	{
		switch (button)
		{
		case SDL_BUTTON_LEFT:
			player.shootProjectile(0);
			break;
		}
	}

	void Game::MouseDown(int button)
	{
		switch (button)
		{
		case SDL_BUTTON_LEFT:
			player.shootProjectile(5);
			break;
		}
	}



	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		exit(1);
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------

	//Surface explosion{ "assets/Font/Essentle4.otf" };


	std::ofstream fout("Scores/scores.txt");

	void Game::Tick(float deltaTime)
	{
		if (player.isDead)
		{
			std::cout << "\n STOP \n";
			StopGame();
			player.restart();
			std::cout << "\n Restart \n";
			Init();
		}
		if (isRunning)
		{
			//std::cout << "RUNS";
			screen->Clear(0);
			Input(deltaTime);

			manager.rooms[player.currentRoom->roomNumber].updateMap(deltaTime, screen);
			player.update(deltaTime);
		}
		//font.Print(screen, "AAA", 10, 10, false);
	}

};
