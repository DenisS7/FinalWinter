#include "game.h"
#include "Classes/Room.h"
#include <iostream>

#include "MapManager.h"
#include "Classes/Player.h"

#include "Classes/Snowball.h"
#include "Classes/StartScreen.h"

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

	float t = 0;

	void Game::Restart()
	{

	}

	void Game::Pause()
	{
		pauseScreen->displayScreen();
	}

	void Game::Init()
	{
		startScreen->displayScreen();
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

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		exit(1);
	}

	void Game::DrawScreen(float deltaTime)
	{
		screen->Clear(0);
		if (isRunning)
		{
			if (isPaused)
			{	
				manager.rooms[player.currentRoom->roomNumber].updateMap(0, screen);
				player.drawPausePlayer(0);
				pauseScreen->displayScreen();
			}
			else
			{
				manager.rooms[player.currentRoom->roomNumber].updateMap(deltaTime, screen);
				player.update(deltaTime);
			}
		}
		else
		{
			if (!isEndScreen)
			{
				screen->Clear(0);
				startScreen->displayScreen();
			}
			else
			{
				manager.rooms[player.currentRoom->roomNumber].updateMap(deltaTime, screen);
				player.drawPausePlayer(0);
				endScreen->displayScreen(won);
			}
		}
	}

	void Game::StartGame()
	{
		player.currentRoom = &player.mapManager->rooms[player.mapManager->start.x + player.mapManager->roomAm.x * player.mapManager->start.y];
		isRunning = true;
		isScreenFocus = false;
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

	void Game::PressButton(bool down, UI::ScreenBase* currentScreen)
	{
		int k = currentScreen->isButtonPressed(vec2((float)mouse.x, (float)mouse.y));
		std::cout << k << std::endl;
		if (k != -1)
		{
			if (k == 0 && !isRunning && down)
				StartGame();
			else if (k == 1 && down)
				Shutdown();
			else if (k == 3 && down)
			{
				isPaused = true;
				isRunning = false;
				std::cout << "RESTART" << std::endl;
				player.restart();
				isScreenFocus = false;
				isEndScreen = false;
				isPaused = false;
				isRunning = true;
			}
		}
	}

	void Game::KeyDown(int key)
	{

		int x;
		if (player.isHoldingGun)
			x = 0;
		else x = 5;
		switch (key)
		{
		case SDL_SCANCODE_ESCAPE:
			if (isRunning)
			{
				isPaused = !isPaused;
				if (isPaused)
				{
					currentScreen = pauseScreen;
					isScreenFocus = true;
				}
				else
				{
					currentScreen = startScreen;
					isScreenFocus = false;
				}
			}
			break;
		case SDL_SCANCODE_E:
			if (!isPaused && isRunning)
				player.equipWeapon(x), std::cout << "E SHOOT" << std::endl;
			break;
		}

	}

	void Game::KeyUp(int key)
	{
		
	}

	void Game::MouseUp(int button)
	{
		switch (button)
		{
		case SDL_BUTTON_LEFT:
			if (isScreenFocus)
				PressButton(true, currentScreen);
			player.shootProjectile(0);
			break;
		}
	}

	void Game::MouseDown(int button)
	{
		switch (button)
		{
		case SDL_BUTTON_LEFT:
			if (isScreenFocus)
				PressButton(false, currentScreen);
			else if (isRunning && !isPaused)
				player.shootProjectile(5);
			break;
		}
	}



	

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------

	std::ofstream fout("Scores/scores.txt");
	Sprite gameOver(new Surface("assets/Font/game_over.png"), 1);
	Surface* image = new Surface("assets/Thumbnail/thumbnailUP.png");

	void Game::Tick(float deltaTime)
	{		
		deltaTime = newmath::clampf(deltaTime, 0, 10.0f);
		DrawScreen(deltaTime);
		if (player.isDead && player.currentSs.getCurrentFrame() % 7 == 6)
		{
			isScreenFocus = true;
			currentScreen = endScreen;
			StopGame();
		}
		else if (isRunning && !isPaused)
		{
			Input(deltaTime);
			if (player.isDead)
			{
				won = false;
				isEndScreen = true;
			}
		}	
	}

};
