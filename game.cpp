#include "game.h"
#include "Classes/Room.h"

#include "Classes/Snowball.h"
#include "../Classes/CollisionCheck.h"
#include "../Classes/PrintNumber.h"

#include <fstream>


namespace GameSpace
{

    void Game::Pause()
    {
        pauseScreen->displayScreen();
    }

    // Initialize the application

    void Game::Init()
    {
        SDL_ShowCursor(false);
        startScreen->displayScreen();
        
        time_t t;
        srand(static_cast<unsigned>(time(&t)));
        manager->setPlayer(player);
        manager->setScreen(screen);
        manager->initiate();
        scoreManager.readScores();
        player->init(screen, &manager->rooms[manager->getStart().x + manager->getStart().y * manager->getRoomAm().x],
                     manager, keystate);

    }

    // Close down application

    void Game::Shutdown()
    {
        scoreManager.outputScores();
        exit(0);
    }

    void Game::DrawScreen(float deltaTime)
    {
        int newScreenType = currentScreenType;
        screen->Clear(0);
        if (isRunning)
        {
            if (isPaused && !isScoreScreen)
            {
                newScreenType = pause;
                manager->rooms[player->currentRoom->getRoomNumber()].updateMap(0);
                player->drawPausePlayer(0);
                pauseScreen->displayScreen();
            }
            else if (isScoreScreen)
            {
                newScreenType = score;
                screen->Clear(0);
                scoreScreen->displayScreen();
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
            if (!isEndScreen && !isScoreScreen)
            {
                newScreenType = start;
                screen->Clear(0);
                startScreen->displayScreen();
            }
            else if (isScoreScreen)
            {
                newScreenType = score;
                screen->Clear(0);
                scoreScreen->displayScreen();
            }
            else if (isEndScreen)
            {
                screen->Clear(0);
                newScreenType = end;
                manager->rooms[player->currentRoom->getRoomNumber()].updateMap(deltaTime);
                player->drawPausePlayer(0);
                endScreen->displayScreen(player->getWon());
            }
        }
        if (currentScreenType != newScreenType)
            isMouseDown = false, currentScreenType = newScreenType;
        if (isPathOnScreen)
            PrintNumber::printNumber(screen, manager->getLength(), screen->GetPitch() - screen->GetPitch() / 15,
                                     screen->GetHeight() / 10);
        cursor.Draw(screen, mouse.x - 8, mouse.y - 8);
    }

    void Game::StartGame()
    {
        player->currentRoom = &player->mapManager->rooms[player->mapManager->getStart().x + player->mapManager->
            getRoomAm().x * player->mapManager->getStart().y];
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

    void Game::PressButton(bool down)
    {
        int k = currentScreen->isButtonPressed(!down, vec2(static_cast<float>(mouse.x), static_cast<float>(mouse.y))); //checks if the mouse is on one of the buttons
        if (k != -1) //a button was pressed
        {
            int isPressed = currentScreen->getButtonStatus(k); //checks if the mouse was pressed (mouse button not released yet)
            if (down && !isPressed)
            {
                if (k == startButton && !isRunning)
                    StartGame();
                else if (k == quitButton)
                    Shutdown();
                else if (k == replayButton)
                {
                    outputScore = false;
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
                else if (k == scoresButton)
                {
                    currentScreen = scoreScreen;
                    isScreenFocus = true;
                    isPathOnScreen = false;
                    isScoreScreen = true;
                }
                else if (k == pathButton)
                {
                    isPathOnScreen = !isPathOnScreen;
                }
                else if (k == backButton)
                {
                    if (isEndScreen)
                        currentScreen = endScreen;
                    else currentScreen = startScreen;
                    isScreenFocus = true;
                    isScoreScreen = false;
                }
            }
        }

        //isButtonPressed = k + 1;
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
        default:
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
                PressButton(true);
            else
                player->shootProjectile(0);
            break;
        default:
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
                PressButton(false);
            else if (isRunning && !isPaused)
                player->shootProjectile(5);
            break;

        case SDL_BUTTON_RIGHT:
            player->iceExplosion(mouse.x, mouse.y);
            break;

        default:
            break;    
        }
    }

    // Main application tick function
  
    void Game::Tick(float deltaTime)
    {
        deltaTime = newmath::clampf(deltaTime, 0, 10.0f);
        DrawScreen(deltaTime);
        if ((player->getDead() && player->getCurrentFrame() % 7 == 6) || player->getWon())
        {
            if (player->getWon() && !outputScore)
                scoreManager.checkScore(player->getScore()), outputScore = true;
            isEndScreen = true;
            isScreenFocus = true;
            if (currentScreen->screenType != 4)
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
