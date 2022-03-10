#include "ItemBase.h"
#include "Room.h"

namespace Item
{

	void ItemBase::deleteItem()
	{
		currentRoom->removeItem(this);
		delete this;
	}

	void ItemBase::init()
	{
		locf.x = (float)IRand((currentRoom->getSize().x - sprite->GetWidth() / currentRoom->tilesize - 4) * currentRoom->tilesize + 2 * currentRoom->tilesize);
		locf.y = (float)IRand((currentRoom->getSize().y - sprite->GetHeight() / currentRoom->tilesize - 1) * currentRoom->tilesize + 2 * currentRoom->tilesize);
		drawLocf = locf - currentRoom->getLocation();
	}

	void ItemBase::takeDamage(int damage)
	{
	}

	void ItemBase::draw(float deltaTime)
	{
		currentSs.drawNextSprite(deltaTime, screen, drawLocf);
	}

	void ItemBase::update(float deltaTime)
	{
		drawLocf = locf - currentRoom->getLocation();
		draw(deltaTime);
	}

	void ItemBase::use()
	{
	}

}
