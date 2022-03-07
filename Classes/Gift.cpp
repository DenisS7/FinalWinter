#include "Gift.h"
#include "Potion.h"
#include "Room.h"

namespace Item
{
	void Gift::init()
	{
		drawLocf = locf - currentRoom->getLocation();
	}

	void Gift::open()
	{
		currentRoom->addItem(potion, locf + 16);
		currentRoom->removeItem(this);
		delete this;
	}

	void Gift::takeDamage(float damage)
	{
		health -= damage;
		if (health <= 0)
			open(), isColidable = false;
	}

}
