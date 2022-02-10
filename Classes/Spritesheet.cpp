#include "Spritesheet.h"
#include "../surface.h"
#include <iostream>


Spritesheet::Spritesheet(char* path, int row, int column, GameSpace::Sprite* newSprite)
{
    image.LoadImage(path);
    //image = newimage;
    rows = row;
    columns = column;
    currentFrame = currentRow * column;
    sprite = newSprite;
    
}

Spritesheet::~Spritesheet()
{
    rows = 0;
    columns = 0;
}

void Spritesheet::changeSpritesheet(char* path, int row, int column, GameSpace::Sprite* newSprite)
{
    rows = row;
    currentFrame = currentRow * column;
    columns = column;
    //std::cout << "State Change " << row << " " << column << " " << currentFrame << std::endl;
    sprite = newSprite;
    image.LoadImage(path);
    
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
        freezedColumn = 1;
    }
}



void Spritesheet::calculateNextFrame()
{   
    currentFrame = (currentFrame + 1 * freezedColumn) % columns + columns * currentRow;
    //std::cout << currentFrame << " " << columns << " " << currentRow << std::endl;
}

void Spritesheet::changeVisiblity(bool newVisible)
{
    visible = newVisible;
}

void Spritesheet::drawNextSprite(float deltaTime, GameSpace::Surface *screen, int x, int y)
{
    if (visible)
    {
        currentTime += deltaTime;
        //std::cout << currentFrame << std::endl;
        if (currentTime >= frameTime)
        {
            //if (currentFrame < 6)
            //std::cout << currentFrame << std::endl;
            calculateNextFrame();
            currentTime -= frameTime;
            sprite->SetFrame(currentFrame);
        }
        sprite->Draw(screen, x, y);
    }
}


