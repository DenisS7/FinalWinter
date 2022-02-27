#pragma once
#include "../template.h"

namespace GameSpace
{
    class Surface;
    class Sprite;
}

class Spritesheet
{
public:
    Spritesheet(char* path, int row, int column, GameSpace::Sprite* newSprite);
    ~Spritesheet();

    void changeSpritesheet(char* path, int row, int column, int newCurrentRow, GameSpace::Sprite* newSprite);
    void setFrame(int frame) { if (frame < rows * columns) currentFrame = frame; }
    void setFrameTime(float newFrameTime);
    void setDirection(int newRow);
    void freezeFrame(int frame, bool isFreezed);
    void calculateNextFrame();
    void changeVisiblity(bool visible);
    void drawNextSprite(float deltaTime, GameSpace::Surface* screen, GameSpace::vec2 drawLocf);
    bool getVisibility() { return visible; };
    int getCurrentFrame() { return currentFrame; };

    GameSpace::Surface* image;
private:

    GameSpace::Sprite* sprite;
    bool visible = true;
    int currentRow = 1;
    float frameTime = 0, currentTime = 0;
    int currentFrame = 0;
    int rows = 0;
    int columns = 0;
    int freezedRow = 0, freezedColumn = 1;
};