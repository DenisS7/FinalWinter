#include "game.h"
#include "Classes/Room.h"
#include <iostream>
#include "Classes/Snowball.h"
#include "../Classes/CollisionCheck.h"
#include "../Classes/PrintNumber.h"
#include "../Classes/CollisionComponent.h"

#include <fstream>


namespace GameSpace
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------

	
	
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
		SDL_ShowCursor(false);
		startScreen->displayScreen();
		vec2 s;
		time_t t;
		srand((unsigned)time(&t));
		manager->setPlayer(player);
		manager->setScreen(screen);
		manager->initiate();
		
		player->init(screen, &manager->rooms[manager->getStart().x + manager->getStart().y * manager->getRoomAm().x], manager, keystate);
		
		
		//player->equipWeapon(5);
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
		int newScreenType = currentScreenType;
		screen->Clear(0);
		if (isRunning)
		{
			if (isPaused)
			{	
				newScreenType = pause;
				manager->rooms[player->currentRoom->getRoomNumber()].updateMap(0);
				player->drawPausePlayer(0);
				pauseScreen->displayScreen();
			}
			else
			{
				newScreenType = play;
				Input(deltaTime);
				manager->rooms[player->currentRoom->getRoomNumber()].updateMap(deltaTime);
				player->update(deltaTime);
			}
		}
		else
		{
			if (!isEndScreen)
			{
				newScreenType = start;
				screen->Clear(0);
				startScreen->displayScreen();
			}
			else
			{
				newScreenType = end;
				manager->rooms[player->currentRoom->getRoomNumber()].updateMap(deltaTime);
				player->drawPausePlayer(0);
				endScreen->displayScreen(player->getWon());
			}
		}
		if (currentScreenType != newScreenType)
			isMouseDown = false, currentScreenType = newScreenType;
		if (isPathOnScreen)
			PrintNumber::printNumber(screen, manager->getLength(), screen->GetPitch() - screen->GetPitch() / 15, screen->GetHeight() / 10);
		cursor.Draw(screen, mouse.x - 8, mouse.y - 8);
	 }

	void Game::StartGame()
	{
		player->currentRoom = &player->mapManager->rooms[player->mapManager->getStart().x + player->mapManager->getRoomAm().x * player->mapManager->getStart().y];
		isRunning = true;
		isScreenFocus = false;
	}

	void Game::StopGame()
	{
		isRunning = false;
	}

	void Game::Input(float deltaTime)
	{
		player->mouseLoc(mouse.x, mouse.y);
		player->input(deltaTime);
	}

	void Game::PressButton(bool down, UI::ScreenBase* currentScreen)
	{
		int k = currentScreen->isButtonPressed(vec2((float)mouse.x, (float)mouse.y));
		if (k != -1)
		{
			if (k == startButton && !isRunning && down)
				StartGame();
			else if (k == quitButton && down)
				Shutdown();
			else if (k == replayButton && down)
			{
				isPathOnScreen = false;
				isPaused = true;
				isRunning = false;
				player->restart();
				isScreenFocus = false;
				isEndScreen = false;
				isPaused = false;
				isRunning = true;
				won = false;
			}
			else if (k == pathButton && down)
			{
				isPathOnScreen = !isPathOnScreen;
			}
		}
	}

	void Game::KeyDown(int key)
	{

		int x;
		if (player->getHoldingGun())
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
				player->equipWeapon(x);
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
			if (isScreenFocus && isMouseDown)
				PressButton(true, currentScreen);
			else
				player->shootProjectile(0, 0, 0);
		
			break;
		}
		isMouseDown = false;
	}

	void Game::MouseDown(int button)
	{
		isMouseDown = true;
		switch (button)
		{
		case SDL_BUTTON_LEFT:
			if (isScreenFocus)
				PressButton(false, currentScreen);
			else if (isRunning && !isPaused)
				player->shootProjectile(5, mouse.x, mouse.y);
			break;

		case SDL_BUTTON_RIGHT:
			player->iceExplosion(mouse.x, mouse.y);
		}
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------

	std::ofstream fout("Scores/scores.txt");


	void Game::Tick(float deltaTime)
	{		
		deltaTime = newmath::clampf(deltaTime, 0, 10.0f);
		DrawScreen(deltaTime);
		if ((player->getDead() && player->getCurrentFrame() % 7 == 6) || player->getWon())
		{
			isEndScreen = true;
			isScreenFocus = true;
			currentScreen = endScreen;
			StopGame();
		}
		else if (isRunning && !isPaused)
		{
			
			if (player->getDead())
			{
				won = false;
				isEndScreen = true;
			}
		}	
	}

};
