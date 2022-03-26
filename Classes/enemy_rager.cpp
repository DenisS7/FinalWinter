#include "enemy_rager.h"
#include "Player.h"

#include "CollisionCheck.h"

namespace Character
{
    void enemy_rager::init()
    {
        EnemyBase::init(2);

        EnemyBase::changeActionSprite(0, 0);
        currentState = 0;
        drawLocf = locf - currentRoom->getLocation();
    }

    void enemy_rager::changeActionSprite(int x, int newCurrentRow)
    {
        Sprites::get().rager[x]->SetFrame(directionFacing * data.epaths[x].columns);
        *sprite = *Sprites::get().rager[x];
        EnemyBase::changeActionSprite(x, newCurrentRow);
    }

    void enemy_rager::attack()
    {
        changeActionSprite(2, directionFacing);
    }

    void enemy_rager::changeDirection(int newDirection)
    {
        currentSs.setDirection(newDirection);
        directionFacing = newDirection;
    }

    void enemy_rager::triggerFollowPlayer()
    {
        if (!isFollowingPlayer)
            changeActionSprite(1, directionFacing);
        isFollowingPlayer = true;
    }

    void enemy_rager::addMovement(float deltaTime)
    {
        newmath::ivec2 currentPos = getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2));
        if (path.size())
        {
            const newmath::ivec2 nextPos = *path.begin();
            newmath::ivec2 dir(nextPos.x - currentPos.x, nextPos.y - currentPos.y);
            if (currentPos != nextPos)
            {
                float div = 1;
                if (dir.x && dir.y)
                    div = 2.0f / 3.0f;

                locf.x += static_cast<float>(dir.x * data.speed * deltaTime * div);
                locf.y += static_cast<float>(dir.y * data.speed * deltaTime * div);

                data.col.collisionBox.x = static_cast<int>(locf.x) + data.col.offset.x;
                data.col.collisionBox.y = static_cast<int>(locf.y) + data.col.offset.y;

                drawLocf.x = locf.x - currentRoom->getLocation().x;
                drawLocf.y = locf.y - currentRoom->getLocation().y;
            }
            else
            {
                path.erase(path.begin());
                if (path.size())
                {
                    newmath::ivec2 nextPos = *path.begin();
                    dir.x = nextPos.x - currentPos.x;
                    dir.y = nextPos.y - currentPos.y;

                    float div = 1;
                    if (dir.x && dir.y)
                        div = 2.0f / 3.0f;

                    locf.x += static_cast<float>(dir.x * data.speed * deltaTime * div);
                    locf.y += static_cast<float>(dir.y * data.speed * deltaTime * div);

                    data.col.collisionBox.x = static_cast<int>(locf.x) + data.col.offset.x;
                    data.col.collisionBox.y = static_cast<int>(locf.y) + data.col.offset.y;

                    drawLocf.x = locf.x - currentRoom->getLocation().x;
                    drawLocf.y = locf.y - currentRoom->getLocation().y;
                }
            }
            if (dir.x)
            {
                move.side[dir.x + 2] = true;
                move.side[(dir.x + 4) % 4] = false;
            }
            else move.side[1] = move.side[3] = false;

            //this enemy has only left and right sprites
            if (dir.x == -1)
                changeDirection(0); // x = -1 || x = 1; left = 1, right = 3
            else if (dir.x == 1)
                changeDirection(1);
        }
    }

    void enemy_rager::update(float deltaTime)
    {
        EnemyBase::update(deltaTime);
        if (isDead) //play death animation
        {
            drawLocf = locf - currentRoom->getLocation();
            if (currentState != 3) // change spritesheet to death if it's not already
            {
                changeActionSprite(3, directionFacing);
                currentState = 3;
                currentSs.setFrame(1 + directionFacing * data.epaths->columns);
            }
            else if (currentSs.getCurrentFrame() % 8 == 7) // die on the last frame of the death animation
                die();
        }
        else
        {
            drawLocf = locf - currentRoom->getLocation();
            if (path.size() <= 1 && !isAttacking) // player is in range to attack
            {
                currentState = 2;
                isAttacking = true;
                attack();
            }
            else if ((isFollowingPlayer || path.size() <= 9) && !isAttacking) // player is in range to start following it
            {
                findPath(getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2)),
                         currentRoom->getPlayer()->getCurrentPos(), currentRoom);
                currentState = 1;
                data.speed += static_cast<float>(0.000001) * deltaTime; //increase speed overtime
                triggerFollowPlayer();
                addMovement(deltaTime);
                isFollowingPlayer = true;
            }
            else if (isAttacking)
            {
                if (currentSs.getCurrentFrame() % 12 == 11) //stop attacking when reaches the last frame of the attack animation
                {
                    dealDamage = false;
                    currentState = 1;
                    changeActionSprite(1, directionFacing);
                    isAttacking = false;
                    findPath(getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2)),
                             currentRoom->getPlayer()->getCurrentPos(), currentRoom);
                }
                else if (currentSs.getCurrentFrame() % 12 > 7 && !dealDamage) //deal damage to the player from the 7th frame onwards, but only once
                {
                    CollisionComponent attackCollision = *attackCol;
                    attackCollision.collisionBox.x += data.col.collisionBox.x + directionFacing * 50;
                    attackCollision.collisionBox.y += data.col.collisionBox.y;
                    if (CollisionCheck::areColliding(attackCollision, currentRoom->getPlayer()->getCollision()))
                    {
                        dealDamage = true;
                        currentRoom->getPlayer()->takeDamage(data.damagePerAttack);
                    }
                }
            }
            else
            {
                findPath(getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2)),
                         currentRoom->getPlayer()->getCurrentPos(), currentRoom);

                drawLocf = locf - currentRoom->getLocation();
            }
        }
    }
}
