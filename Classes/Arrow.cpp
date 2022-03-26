#include "Arrow.h"
#include "CollisionCheck.h"
#include "../Classes/Room.h"


namespace Weapon
{
    Arrow::~Arrow()
    {
    }

    void Arrow::drawProjectile(GameSpace::Surface* screen, float deltaTime)
    {
        sprite->Draw(screen, static_cast<int>(drawLocf.x), static_cast<int>(drawLocf.y));
    }

    void Arrow::deleteArrow()
    {
        crossbow->deleteArrow(this);
        delete this;
    }


    void Arrow::UpdatePosition(float deltaTime)
    {
        if (!isExploding)
        {
            if (CollisionCheck::isOverlapping(collision, locf, currentRoom, damage, 5, crossbow->player->screen))
            {
                isExploding = true;
                deleteArrow();
            }
            else
            {
                locf.x += speedf * deltaTime * moveDirection.x;
                locf.y += speedf * deltaTime * moveDirection.y;

                drawLocf.x = locf.x - currentRoom->getLocation().x;
                drawLocf.y = locf.y - currentRoom->getLocation().y;

                collision.collisionBox = newmath::make_Rect(static_cast<int>(locf.x), static_cast<int>(locf.y), 0, 0) +
                    crossbow->arrowCol[direction];
                sprite->Draw(crossbow->player->screen, static_cast<int>(drawLocf.x), static_cast<int>(drawLocf.y));
            }
        }
    }
}
