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
	StartScreen* startScreen;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	//Font font{ "assets/Font/font.png", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.:,;'|(!?)+-*/="};
	Sprite score{new Surface( "assets/Font/newFont-blue.png"), 1};
	

	void Game::Restart()
	{

	}

	void Game::Init()
	{
		std::cout << "\n START \n";
		startScreen = new StartScreen(screen);
			startScreen->displayScreen();
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
		//StartGame();
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		exit(1);
	}

	void Game::StartGame()
	{
		
		player.currentRoom = &player.mapManager->rooms[player.mapManager->start.x + player.mapManager->roomAm.x * player.mapManager->start.y];
		isRunning = true;
	}

	void Game::StopGame()
	{
		isRunning = false;
	}

	void Game::Input(float deltaTime)
	{
		//PressButton();
			player.input(deltaTime);
			player.mouseLoc(mouse.x, mouse.y);
	
	}

	void Game::PressButton(bool down)
	{
		int k = startScreen->isButtonPressed(vec2(mouse.x, mouse.y));
		if (k != -1)
		{
			std::cout << "\n BUTTON PRESSED \n";
			if (k == 0 && !isRunning && down)
				StartGame();
			else if (k == 1 && down)
				Shutdown();
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
			if (!isRunning)
				PressButton(true);
			else
				player.shootProjectile(0);
			break;
		}
	}

	void Game::MouseDown(int button)
	{
		switch (button)
		{
		case SDL_BUTTON_LEFT:
			if (!isRunning)
				PressButton(false);
			else
				player.shootProjectile(5);
			break;
		}
	}



	

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------

	//Surface explosion{ "assets/Font/Essentle4.otf" };

	//Surface* th = new Surface("assets/Thumbnail/thumbnail.png", 1920, 1080);
	//GameSpace::Sprite thumbnail{ th, 1 };
	std::ofstream fout("Scores/scores.txt");
	Sprite gameOver(new Surface("assets/Font/game_over.png"), 1);
	Surface* image = new Surface("assets/Thumbnail/thumbnailUP.png");

	void Game::Tick(float deltaTime)
	{
		//std::cout << "\n Height: " << screen->GetHeight() << '\n';
		//screen->Resize(image);
		//std::cout << screen->GetHeight() << std::endl;;
		//thumbnail.Draw(screen, 0, 0);
		//std::cout << mouse.x << " " << mouse.y << "\n";
		if (!isRunning)
		{
			screen->Clear(0);
			startScreen->displayScreen();
		}
		if (player.isDead && player.currentSs.getCurrentFrame() % 7 == 6)
		{
			//screen->Clear(0);
			//player.currentSs.drawNextSprite(deltaTime, screen, player.drawLocf);
			////gameOver.Draw(screen, screen->GetPitch() / 2 - gameOver.GetSurface()->GetPitch() / 2, screen->GetHeight() / 2 - gameOver.GetSurface()->GetHeight() / 2);
		//	manager.rooms[player.currentRoom->roomNumber].drawMap(screen);
			//if ()
			{
				std::cout << "\n STOP \n";
				player.restart();
				StopGame();
				std::cout << "\n Restart \n";
			}
		}
		else if (isRunning)
		{
			//std::cout << "RUNS";
			
			screen->Clear(0);
			Input(deltaTime);

			std::cout << player.isDead << std::endl;
			manager.rooms[player.currentRoom->roomNumber].updateMap(deltaTime, screen);
			
			player.update(deltaTime);
			if (player.isDead)
			{
				gameOver.Draw(screen, screen->GetPitch() / 2 - gameOver.GetSurface()->GetPitch() / 2, screen->GetHeight() / 2 - gameOver.GetSurface()->GetHeight() / 2);
				if (player.isDead && player.currentSs.getCurrentFrame() % 7 == 6)
				{
					std::cout << "\n STOP \n";
					player.restart();
					StopGame();
					std::cout << "\n Restart \n";
				}
			}
		}	}

};
