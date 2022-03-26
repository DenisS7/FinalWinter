#include "IceExplosion.h"
#include "Player.h"
#include "CollisionCheck.h"

namespace Weapon
{
    void IceExplosion::init()
    {
        currentRoom = player->currentRoom;
        locf += drawLocf + currentRoom->getLocation();
        currentSs.setDirection(0);
    }

    void IceExplosion::destroy()
    {
        player->deleteExplosion(this);
        delete this;
    }

    void IceExplosion::update(float deltaTime)
    {
        pastFrame = currentSs.getCurrentFrame();
        if (currentRoom != player->currentRoom)
            currentSs.changeVisiblity(false);
        else if (!currentSs.getVisibility())
            currentSs.changeVisiblity(true);
        currentSs.drawNextSprite(deltaTime, player->screen, drawLocf);
        drawLocf = locf - currentRoom->getLocation();
        if (currentSs.getCurrentFrame() == 11)
        {
            destroy();
        }
        else if (currentSs.getCurrentFrame() >= 6) // deal damage per frame and not time
        {
            if (!dealtDamage)
            {
                int colType = CollisionCheck::isOverlapping(col, locf, currentRoom, damage, 5, player->screen);
                if (colType)
                    col.setCollisionBox(0, 0, 0, 0);
            }
            if (pastFrame != currentSs.getCurrentFrame())
            {
                col.setCollisionBox(col.offset.x + static_cast<int>(locf.x), col.offset.y + static_cast<int>(locf.y), col.size.y, col.size.x);
                dealtDamage = false;
            }
        }
    }
}
