#include "Spritesheet.h"
#include "../surface.h"
#include <iostream>
#include "../template.h"


Spritesheet::Spritesheet(GameSpace::Surface* newImage, int row, int column, GameSpace::Sprite* newSprite)
{
    image = newImage;
    
    rows = row;
    columns = column;
    currentFrame = (currentRow * column) % (row * column);
    sprite = newSprite;
    int ok = 0;
    if (ok == 0)
        ok = 0;
}

Spritesheet::~Spritesheet()
{
    rows = 0;
    columns = 0;
}

void Spritesheet::changeSpritesheet(GameSpace::Surface* newImage, int row, int column, int newCurrentRow, GameSpace::Sprite* newSprite)
{
    currentTime = 0;
    rows = row;
    currentRow = newCurrentRow;
    currentFrame = currentRow * column;
    columns = column;
    //std::cout << "State Change " << row << " " << column << " " << currentFrame << std::endl;
    sprite = newSprite;
    image = newImage;
}

void Spritesheet::setFrameTime(float newFrameTime)
{
    frameTime = newFrameTime;
}

void Spritesheet::setDirection(int newRow)
{
    currentFrame = newRow * columns + currentFrame;
    //std::cout << "New Direction " << newRow << " " << currentFrame << std::endl;
    currentRow = newRow;
}

void Spritesheet::freezeFrame(int frame, bool isFreezed)
{
    if (isFreezed)
    {
        currentFrame = frame;
        freezedColumn = 0;
        currentRow = frame / columns;
    }
    else
    {
       // currentTime = 0.0f;
        freezedColumn = 1;
    }
}



void Spritesheet::calculateNextFrame()
{   
    //if (columns == 10)
        //std::cout << currentRow << std::endl;
    currentFrame = (currentFrame + 1 * freezedColumn) % columns + columns * currentRow;
}

void Spritesheet::changeVisiblity(bool newVisible)
{
    visible = newVisible;
}

void Spritesheet::drawNextSprite(float deltaTime, GameSpace::Surface *screen, GameSpace::vec2 drawLocf)
{
    if (visible)
    {
        currentTime += deltaTime * freezedColumn;
        //std::cout << currentFrame << std::endl;
        if (currentTime >= frameTime)
        {
            //if (currentFrame < 6)
            //std::cout << currentFrame << std::endl;
            calculateNextFrame();
            currentTime -= frameTime;
            sprite->SetFrame(currentFrame);
        }
        sprite->Draw(screen, (int)drawLocf.x, (int)drawLocf.y);
    }
}


