#pragma once
#include "newmath.h"
#include <limits.h>
#include <vector>

namespace Map
{
    class Room;
};

class Pathfinder
{
private:
    Pathfinder()
    {
    }

    struct Atile
    {
        bool visited = false;

        newmath::ivec2 position;
        int g = INT_MAX;
        int h = INT_MAX;
        int f = INT_MAX;

        Atile()
        {
            f = INT_MAX;
            g = INT_MAX;
            h = INT_MAX;
        }

        Atile(newmath::ivec2 newPosition, int ng)
        {
            position = newPosition;
            g = ng;
        }
    };

    Atile parents[1200];
    bool visited[1200] = {false};
    std::vector<Atile> nextTiles;
    std::vector<Atile> passedTiles;
    newmath::ivec2 finish;
    Map::Room* currentRoom;
    std::vector<newmath::ivec2> path;

    void resetAPath();
    int getClosestTile();
    int getIndex(const std::vector<Atile>& v, newmath::ivec2 pos);
    bool isTileValid(const newmath::ivec2& tilePos);
    void getAdjTile(const Atile& tile, const newmath::ivec2& nextTile);
    void getNeighbours(const Atile& tile);

public:
    Pathfinder(const Pathfinder&) = delete;

    static Pathfinder& get()
    {
        static Pathfinder instance;
        return instance;
    };


    std::vector<newmath::ivec2> findPath(newmath::ivec2 start, newmath::ivec2 newFinish, Map::Room* newRoom);
};
