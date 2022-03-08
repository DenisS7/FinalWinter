#include "Potion.h"
#include "Room.h"
#include "../MapManager.h"
#include "Player.h"

namespace Item
{
	void Potion::init()
	{
		drawLocf = locf - currentRoom->getLocation();
		sprite.SetFile(currentRoom->manager->potionPath[type], 12, 0);
		currentSs.changeSpritesheet(currentRoom->manager->potionPath[type], 0, 12, 0, &sprite);
	}

	void Potion::use()
	{
		bool used = true;
		if (type == healing)
		{
			if (currentRoom->getPlayer()->getHealth() < 100)
				currentRoom->getPlayer()->takeDamage(-33);
			else used = false;
		}
		else if (type == speed)
		{
			if (!currentRoom->getPlayer()->isPotionUsed(speed))
				currentRoom->getPlayer()->speedBoost();
			else used = false;
		}
		else if (type == firerate)
		{
			if (!currentRoom->getPlayer()->isPotionUsed(firerate))
				currentRoom->getPlayer()->firerateBoost();
			else used = false;
		}
		else if (type == shield)
		{
			if (!currentRoom->getPlayer()->isPotionUsed(shield))
				currentRoom->getPlayer()->createShield();
			else used = false;
		}
		else if (type == damage)
		{
			if (!currentRoom->getPlayer()->isPotionUsed(damage))
				currentRoom->getPlayer()->damageBoost();
			else used = false;
		}
		if (used)
			deleteItem();
	}

}
