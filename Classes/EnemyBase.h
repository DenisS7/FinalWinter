#pragma once
#include "../Classes/Spritesheet.h"
#include "../surface.h"
#include "../Classes/newmath.h"
#include "../template.h"

namespace Character
{

class EnemyBase
{
private:
	newmath::spriteData epaths[10];
	GameSpace::Surface sprite;
	GameSpace::vec2 loc, drawLoc;
	Spritesheet sheet;

public:

};

}

