#include "MapManager.h"
#include "Classes/Room.h"
#include "Classes/Player.h"
#include <fstream>

namespace Map
{
    //restart parameters
    void MapManager::restart()
    {
        //restart rooms
        for (int i = 0; i < roomAm.x * roomAm.y; i++)
        {
            rooms[i].restart();
            generatedOrder[i] = 0;
            parentRoom[i] = 0;
            for (int j = 0; j < roomAm.x * roomAm.y; j++)
                graph[i][j] = 0;
            exists[i] = false;
            aux[i] = 0;
            p[i] = 0;
            path[i] = 0;
            nextRooms[i].x = nextRooms[i].y = nextRooms[i].startingDoor = -1;
            nextRooms[i].canClose = false;
        }

        //restart map manager
        actualRooms = 0;
        length = 0;
        goBack = 0;
        currentGen = 0;
        goingBack = false;
        newRooms = 0;

        //calculate new start and exit rooms

        start.x = IRand(roomAm.x);
        start.y = IRand(roomAm.y);

        finish.x = IRand(roomAm.x);
        finish.y = IRand(roomAm.y);


        //make sure start and final room are apart from each other

        int dist = newmath::manhattanDist(start, finish);

        if (dist <= 2)
        {
            int ax = newmath::getSign(start.x - finish.x);
            int ay = newmath::getSign(start.y - finish.y);

            start.x += ax * (abs(dist - 2));
            start.y += ay * (abs(dist - 2));

            finish.x -= ax * (abs(dist - 2));
            finish.y -= ay * (abs(dist - 2));

            start.x = newmath::clamp(start.x, 0, roomAm.x - 2);
            start.y = newmath::clamp(start.y, 0, roomAm.y - 2);

            finish.x = newmath::clamp(finish.x, 0, roomAm.x - 2);
            finish.y = newmath::clamp(finish.y, 0, roomAm.y - 2);
        }


        if (start.y == 6)
        {
            start.y = 5, finish.y--;
            finish.y = newmath::clamp(finish.y, 0, roomAm.y - 2);
        }

        // TEST SCORES MANAGER
        //start.x = start.y = 1;
        //finish.x = 1, finish.y = 2;

        rooms[0].readRoomLayout(collisionTiles, portalTiles);
        rooms[0].initiateRoom(0, this, screen);
        for (int i = 0; i < 49; i++)
        {
            rooms[i].setTileMap(rooms[0].getSize(), rooms[0].getTileMap());
            rooms[i].initiateRoom(i, this, screen);
        }

        generateFirstRoom();
        if (goodMap)
        {
            initiateEnemiesInRooms();
        }
        else restart();
    }

    void MapManager::initiate()
    {
        //set map size
        roomAm.x = 7;
        roomAm.y = 7;

        //set start room and final room

        start.x = IRand(roomAm.x);
        start.y = IRand(roomAm.y);

        finish.x = IRand(roomAm.x);
        finish.y = IRand(roomAm.y);

     

        int dist = newmath::manhattanDist(start, finish);

        //make sure start and final room are apart from each other
        if (dist <= 2)
        {
            int ax = newmath::getSign(start.x - finish.x);
            int ay = newmath::getSign(start.y - finish.y);

            start.x += ax * (abs(dist - 2));
            start.y += ay * (abs(dist - 2));

            finish.x -= ax * (abs(dist - 2));
            finish.y -= ay * (abs(dist - 2));

            start.x = newmath::clamp(start.x, 0, roomAm.x - 2);
            start.y = newmath::clamp(start.y, 0, roomAm.y - 2);
            finish.x = newmath::clamp(finish.x, 0, roomAm.x - 2);
            finish.y = newmath::clamp(finish.y, 0, roomAm.y - 2);
        }

        if (start.y == 6)
            start.y = 5;

        // TEST SCORES MANAGER
        //start.x = start.y = 1;
        //finish.x = 1, finish.y = 2;


        //reading map/enemies
        std::ifstream fin("ReadFiles/RoomLayout/Collisions.txt");
        fin >> nrColTiles;
        for (int i = 0; i < nrColTiles; i++)
        {
            int x;
            fin >> x;
            collisionTiles.push_back(x);
        }
        fin.close();

        std::ifstream pin("ReadFiles/RoomLayout/Portals.txt");
        pin >> nrPortalTiles;
        for (int i = 0; i < nrPortalTiles; i++)
        {
            int x;
            pin >> x;
            portalTiles.push_back(x);
        }
        pin.close();

        for (int i = 0; i < typesOfEnemies; i++)
        {
            std::ifstream ein(enemyPath[i]);
            ein >> enemyTypes[i].type >> enemyTypes[i].health;
            ein >> enemyTypes[i].damagePerAttack >> enemyTypes[i].damageOnCol >> enemyTypes[i].speed >> enemyTypes[i].
                points >> enemyTypes[i].range;
            int x, y, h, w;
            ein >> x >> y >> h >> w;
            enemyTypes[i].col.collisionBox = newmath::make_Rect(x, y, h, w);
            ein >> enemyTypes[i].spritesheetsNr;
            for (int j = 0; j < enemyTypes[i].spritesheetsNr; j++)
            {
                ein >> enemyTypes[i].epaths[j].rows;
                ein >> enemyTypes[i].epaths[j].columns;
                ein >> enemyTypes[i].epaths[j].frameTime;
            }
        }

        //set a room's layout
        rooms[0].readRoomLayout(collisionTiles, portalTiles);
        rooms[0].initiateRoom(0, this, screen);

        //set all other rooms' layouts
        for (int i = 0; i < 49; i++)
        {
            rooms[i].setTileMap(rooms[0].getSize(), rooms[0].getTileMap());
            rooms[i].initiateRoom(i, this, screen);
        }

        //generate map
        generateFirstRoom();

        //check if the map is working
        if (goodMap)
        {
            initiateEnemiesInRooms();
        }
        else restart();
    }

    void MapManager::setPlayer(Character::Player* newPlayer)
    {
        player = newPlayer;
    }

    void MapManager::addToNextRooms(int x, int y, int startingDoor, bool canClose)
    {
        //add to map generating queue
        nextRooms[newRooms].x = x;
        nextRooms[newRooms].y = y;
        nextRooms[newRooms].startingDoor = startingDoor;
        nextRooms[newRooms].canClose = canClose;
        exists[x + y * roomAm.x] = true;
        newRooms++;
    }

    bool MapManager::canCreateNewRoom(int x, int y)
    {
        //is in map bounds
        if (x < 0 || x >= roomAm.x || y < 0 || y >= roomAm.y) // not in map bounds
        {
            return false;
        }
        return true;
    }

    void MapManager::initiateEnemiesInRooms()
    {
        for (int i = 0; i < roomAm.x * roomAm.y; i++)
            if (i != start.x + start.y * roomAm.x)
                rooms[i].initiateEnemies();
        //open starting room's portals
        rooms[start.x + start.y * roomAm.x].openPortals();
    }

    void MapManager::calcNewRoom(int i, int x, int y, bool canClose, bool& generated, bool& usedExistingRoom)
    {
        const int useExistingChance = 4, generatedChance = 4;

        
        if (i % 2 == 0)
        {
            if (canCreateNewRoom(x, y - i + 1))
            {
                //if there's a connection to the next generating room from the current room
                if (graph[x + (y - i + 1) * roomAm.x][x + y * roomAm.x])
                {
                    rooms[x + y * roomAm.x].doors[i] = true;
                    generated = true;
                    usedExistingRoom = true;
                }
                else
                {
                    //if the map exists but the 2 rooms are not connected
                    if (exists[x + (y - i + 1) * roomAm.x]) //the room was already generated
                    {
                        if (!IRand(useExistingChance))
                        {
                            rooms[x + (y - i + 1) * roomAm.x].nrdoors++;
                            rooms[x + (y - i + 1) * roomAm.x].doors[(i + 2) % 4] = true;
                            rooms[x + (y - i + 1) * roomAm.x].changeDoorLayout(false);
                            if (IRand(generatedChance))
                                generated = true;
                            graph[x + y * roomAm.x][x + (y - i + 1) * roomAm.x] = graph[x + (y - i + 1) * roomAm.x][x +
                                y * roomAm.x] = 1;
                            usedExistingRoom = true;
                        }
                    }
                    //if the new generating room was not generated before
                    else
                    {
                        graph[x + y * roomAm.x][x + (y - i + 1) * roomAm.x] = graph[x + (y - i + 1) * roomAm.x][x + y *
                            roomAm.x] = 1;
                        parentRoom[x + (y - i + 1) * roomAm.x] = x + y * roomAm.x;
                        addToNextRooms(x, y - i + 1, (i + 2) % 4, false);
                        generated = true;
                        usedExistingRoom = false;
                    }
                }
            }
        }
        else if (i % 2 == 1)
        {
            if (canCreateNewRoom(x + i - 2, y))
            {
                //if there's a connection to the next generating room from the current room
                if (graph[x + i - 2 + y * roomAm.x][x + y * roomAm.x])
                {
                    rooms[x + y * roomAm.x].doors[i] = true;

                    generated = true;
                    usedExistingRoom = true;
                }
                else
                {
                    //if the map exists but the 2 rooms are not connected
                    if (exists[x + i - 2 + y * roomAm.x])
                    {
                        if (!IRand(useExistingChance))
                        {
                            rooms[x + i - 2 + y * roomAm.x].nrdoors++;
                            rooms[x + i - 2 + y * roomAm.x].doors[(i + 2) % 4] = true;
                            rooms[x + i - 2 + y * roomAm.x].changeDoorLayout(false);
                            if (IRand(generatedChance))
                                generated = true;
                            graph[x + y * roomAm.x][x + i - 2 + y * roomAm.x] = graph[x + i - 2 + y * roomAm.x][x + y *
                                roomAm.x] = 1;
                            usedExistingRoom = true;
                        }
                    }
                    //if the new generating room was not generated before
                    else
                    {
                        graph[x + y * roomAm.x][x + i - 2 + y * roomAm.x] = graph[x + i - 2 + y * roomAm.x][x + y *
                            roomAm.x] = 1;

                        parentRoom[x + i - 2 + y * roomAm.x] = x + y * roomAm.x;
                        addToNextRooms(x + i - 2, y, (i + 2) % 4, false);
                        generated = true;
                        usedExistingRoom = false;
                    }
                }
            }
        }
    }

    void MapManager::calculateRoute(int room)
    {
        int lf, rt;

        int t[100] = {0};
        int q[100] = {0};
        t[room] = -1;
        lf = rt = 1;
        q[1] = room;

        int dist = 0;
    
        //BFS
        while (lf <= rt)
        {
            int k = q[lf];
            for (int i = 0; i < roomAm.x * roomAm.y; i++)
            {
                if (t[i] == 0 && graph[k][i] == 1)
                {
                    t[i] = k + 1;
                    q[++rt] = i;
                }
            }
            lf++;
        }
        int j = finish.x + finish.y * roomAm.x;

        //There's always a path to the exit
        while (j != room && dist < roomAm.x * roomAm.y)
        {
            j = t[j] - 1;
            dist++;
        }

        //rooms left until the exit one
        length = dist;
    }

    void MapManager::generateFirstRoom()
    {
        //mark as generated
        exists[start.x + start.y * roomAm.x] = true;

        //generate random portal positions
        rooms[start.x + start.y * roomAm.x].calculateDoors(2, true);

        //possible checks if there can be a room in that direction
        // 0 - down, 1 - left, 2 - up, 3 - right
        bool possible[4] = {true, true, true, true};

        for (int i = 0; i < 4; i++)
        {
            bool generated = false;
            bool usedExistingRoom = false;

            //if there's a portal that way
            if (rooms[start.x + start.y * roomAm.x].doors[i])
            {
                calcNewRoom(i, start.x, start.y, false, generated, usedExistingRoom);

                //first room will not be using already generated rooms
                if (!generated)
                {
                    rooms[start.x + start.y * roomAm.x].nrdoors--;
                    rooms[start.x + start.y * roomAm.x].doors[i] = false;

                    //a room that way is not possible
                    possible[i] = false;
                    
                    //try to find a substitute so the number of doors doesn't change
                    for (int j = 0; j < 4; j++)
                    {
                        if (!rooms[start.x + start.y * roomAm.x].doors[i] && possible[j])
                            calcNewRoom(j, start.x, start.y, false, generated, usedExistingRoom);
                        if (generated)
                        {
                            rooms[start.x + start.y * roomAm.x].nrdoors++;
                            rooms[start.x + start.y * roomAm.x].doors[j] = true;
                            break;
                        }
                        possible[j] = false;
                    }
                }
            }
        }

        //add portals to the layout
        rooms[start.x + start.y * roomAm.x].changeDoorLayout(false);

        generatedOrder[0] = start.x + start.y * roomAm.x;
        
        //start recursive generation
        generateNextRooms();
    }

    void MapManager::generate(int x, int y, int StartDirection, bool CanClose)
    {
        //mark as generated
        exists[x + y * roomAm.x] = true;

        //generate random portal positions
        rooms[x + y * roomAm.x].calculateDoors(StartDirection, CanClose);

        //possible checks if there can be a room in that direction
        // 0 - down, 1 - left, 2 - up, 3 - right
        bool possible[4] = {true, true, true, true};

        for (int i = 0; i < 4; i++)
        {
            bool generated = false;
            bool usedExistingRoom = false;


            //if there's a portal that way
            //and don't try to generate a room where the "parent" of the room is
            if (rooms[x + y * roomAm.x].doors[i] && i != StartDirection)
            {
                calcNewRoom(i, x, y, CanClose, generated, usedExistingRoom);

                //if the room could not be generated
                //there's also a random chance that a room was already in that direction but there wasn't a portal that way
                if (!generated)
                {
                    //if it did not use an already generated room
                    if (!usedExistingRoom)
                    {
                        rooms[x + y * roomAm.x].nrdoors--;
                        rooms[x + y * roomAm.x].doors[i] = false;
                    }

                    //a room that way is not possible
                    possible[i] = false;

                    //try to find a substitute so the number of doors doesn't become smaller
                    if (!CanClose)
                    {
                        //repeat the initial algorithm
                        for (int j = 0; j < 4; j++)
                        {
                            usedExistingRoom = false;
                            if (!rooms[x + y * roomAm.x].doors[j] && possible[j])
                            {
                                calcNewRoom(j, x, y, CanClose, generated, usedExistingRoom);
                                if (generated)
                                {
                                    rooms[x + y * roomAm.x].doors[j] = true;
                                    if (!usedExistingRoom)
                                        rooms[x + y * roomAm.x].nrdoors++;
                                    break;
                                }
                            }
                            else possible[j] = false;
                        }
                    }
                }
            }
        }

        //add portals to the layout
        rooms[x + y * roomAm.x].changeDoorLayout(false);

        //the number of rooms
        actualRooms++;
        generatedOrder[actualRooms] = x + y * roomAm.x;
    }

    //recursive function that generates all the rooms (other than the first one which calls this function)
    void MapManager::generateNextRooms()
    {
        //remebers how many rooms were each call
        aux[goBack] = newRooms;

        //generate the next rooms
        for (int i = currentGen; i < aux[goBack]; i++)
        {
            generate(nextRooms[i].x, nextRooms[i].y, nextRooms[i].startingDoor, nextRooms[i].canClose);
        }

        //if there was at least a new room added
        if (newRooms != aux[goBack])
        {
            goingBack = false;
            currentGen = aux[goBack];
            //how many generations were generated
            goBack++;
            generateNextRooms();
        }
        //no new rooms were added, but it did not reach the final room
        else if (!exists[finish.x + finish.y * roomAm.x])
        {
            //tries to go back a generation and regenarate it
            goingBack = true;
            //the chance of finding a good layout 5 generations in is quite small so it just restarts the process
            if (goBack > 5)
                goodMap = false;
            else if (goBack > 1)
            {
                //delete the last generated rooms
                for (int i = aux[goBack - 2]; i < newRooms; i++)
                {
                    exists[nextRooms[i].x + nextRooms[i].y * roomAm.x] = false;
                    rooms[nextRooms[i].x + nextRooms[i].y * roomAm.x].resetDoors();
                    actualRooms--;
                }
                goBack--;
                currentGen = aux[goBack - 1];
                newRooms = aux[goBack];
                generateNextRooms();
            }
            else if (goBack == 1)
            {
                for (int i = 0; i < newRooms; i++)
                {
                    exists[nextRooms[i].x + nextRooms[i].y * roomAm.x] = false;
                    rooms[nextRooms[i].x + nextRooms[i].y * roomAm.x].resetDoors();
                    actualRooms--;
                }
                goBack--;
                currentGen = 0;
                newRooms = aux[goBack];
                generateNextRooms();
            }
            else
            {
                //just for safety, should not be reached
                goodMap = false;
            }
        }
        //the exit room was reached
        else
        {
            calculateRoute(start.x + start.y * roomAm.x);
            goodMap = true;
        }
    }

    Room* MapManager::switchRoom(int x, int y)
    {
        //switch current room
        pastRoom = player->currentRoom;
        
        //campfire only available the first time in the room so this removes it after the player exits the room
        if (player->currentRoom->getItems().size())
            if (player->currentRoom->getItems()[0]->getType() == 2)
                player->currentRoom->removeItem(player->currentRoom->getItems()[0]);

        calculateRoute(x + y * roomAm.x);
        return &rooms[x + y * roomAm.x];
    }
}
