#include "Campfire.h"
#include "Room.h"
#include <iostream>

namespace Item
{

	void Campfire::init()
	{
		drawLocf = locf - currentRoom->getLocation();
	}

	void Campfire::turnOn()
	{
		isOn = true;
		*sprite = *Sprites::get().campfire[1];
		currentSs.freezeFrame(0, false);
		currentSs.setFrameTime(120);
		currentSs.changeSpritesheet(1, 10, 0, sprite);
	}

	bool Campfire::heal()
	{
		if (timer >= healRefresh)
		{
			timer -= healRefresh;
			return true;
		}
		return false;
	}

	void Campfire::update(float deltaTime)
	{
		timer += deltaTime * isOn;
		newmath::clampf(timer, 0, healRefresh);
		drawLocf = locf - currentRoom->getLocation();
		draw(deltaTime);
	}

}