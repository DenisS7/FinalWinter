#pragma once

#include "../surface.h"
#include "../template.h"

class Spritesheet
{
public:
    Spritesheet(char* path, int row, int column, GameSpace::Sprite* newSprite);
    ~Spritesheet();

    void changeSpritesheet(char* path, int row, int column, GameSpace::Sprite* newSprite);
    void setFrameTime(float newFrameTime);
    void setDirection(int newRow);
    void freezeFrame(int frame, bool isFreezed);
    void calculateNextFrame();
    void changeVisiblity(bool visible);
    void drawNextSprite(float deltaTime, GameSpace::Surface* screen, GameSpace::vec2 drawLocf);
   // void Init(char* path, int row, int column);

    GameSpace::Surface image{"assets/Player/player_run.png"};
private:
    
    GameSpace::Sprite* sprite;
    int visible = true;
    int currentRow = 1;
    float frameTime = 0, currentTime = 0;
    int currentFrame = 0;
    int rows = 0;
    int columns = 0;
    int freezedRow = 0, freezedColumn = 1;
};
