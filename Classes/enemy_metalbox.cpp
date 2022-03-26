#include "enemy_metalbox.h"
#include "Player.h"
#include "CollisionCheck.h"


namespace Character
{
    void enemy_metalbox::init()
    {
        EnemyBase::init(0);
        tilePos = getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2));
    }

    void enemy_metalbox::changeActionSprite(int x, int newCurrentRow)
    {
        Sprites::get().metalgift[x]->SetFrame(directionFacing * data.epaths[x].columns);
        *sprite = *Sprites::get().metalgift[x];
        EnemyBase::changeActionSprite(x, newCurrentRow);
    }

    void enemy_metalbox::explode()
    {
        directionFacing = 0;
        changeActionSprite(2, 0);
    }

    void enemy_metalbox::triggerFollowPlayer()
    {
        if (!isFollowingPlayer)
            changeActionSprite(1, directionFacing);
        isFollowingPlayer = true;
        isAttacking = false;
    }

    void enemy_metalbox::addMovement(float deltaTime)
    {
        newmath::ivec2 currentPos = getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2));
        if (path.size()) //there's at least one more tile until this enemy reaches the player
        {
            newmath::ivec2 nextPos = *path.begin();
            newmath::ivec2 dir(nextPos.x - currentPos.x, nextPos.y - currentPos.y);
            if (currentPos != nextPos) //this enemy did not reach the next tile yet
            {
                float div = 1.0f;
                if (dir.x && dir.y)
                    div = 2.0f / 3.0f;

                locf.x += static_cast<float>(dir.x * data.speed * deltaTime * div);
                locf.y += static_cast<float>(dir.y * data.speed * deltaTime * div);

                data.col.collisionBox.x = static_cast<int>(locf.x) + data.col.offset.x;
                data.col.collisionBox.y = static_cast<int>(locf.y) + data.col.offset.y;

                drawLocf.x = locf.x - currentRoom->getLocation().x;
                drawLocf.y = locf.y - currentRoom->getLocation().y;
            }
            else // this enemy reached the next tile and is ready to head towards the next one
            {
                path.erase(path.begin());
                if (path.size()) // there are still other tiles to move to besides the one that was deleted
                {
                    newmath::ivec2 nextPos = *path.begin();
                    dir.x = nextPos.x - currentPos.x;
                    dir.y = nextPos.y - currentPos.y;

                    float div = 1.0f;
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
            
            //check direction
            if (dir.x)
            {
                move.side[dir.x + 2] = true;
                move.side[(dir.x + 4) % 4] = false;
            }
            else move.side[1] = move.side[3] = false;

            if (dir.y)
            {
                move.side[(dir.y + 3) % 4] = true;
                move.side[dir.y + 1] = false;
            }
            else move.side[0] = move.side[2] = false;

            if (dir.x)
                EnemyBase::changeDirection(dir.x + 2); // x = -1 || x = 1; left = 1, right = 3
            if (dir.y)
                EnemyBase::changeDirection((dir.y + 3) % 4); // y = 1 (down) || y = -1 (up); down = 0, up = 2
        }
    }

    void enemy_metalbox::update(float deltaTime)
    {
        EnemyBase::update(deltaTime);

        if ((path.size() <= 1 || isDead) && !isAttacking) //is close to player or died
        {
            isAttacking = true;
            explode();
        }
        else if ((isFollowingPlayer || path.size() <= 8) && !isAttacking) // start following the player when it gets in range
        {
            findPath(getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2)), currentRoom->getPlayer()->getCurrentPos(), currentRoom);
            data.speed += static_cast<float>(0.000002) * deltaTime;
            triggerFollowPlayer();
            addMovement(deltaTime);
            isFollowingPlayer = true;
        }
        else //keep looking for player
        {
            findPath(getCurrentPos(newmath::make_ivec2(sprite->GetWidth() / 2, sprite->GetHeight() / 2)), currentRoom->getPlayer()->getCurrentPos(), currentRoom);
            drawLocf = locf - currentRoom->getLocation();
        }

        if (isAttacking) //update animations and damage when it's exploding
        {
            if (currentSs.getCurrentFrame() == 8 && !exploded)
            {
                exploded = true;
                data.col.extendCollision(explosionRange, explosionRange);
                if (CollisionCheck::areColliding(this->data.col, currentRoom->getPlayer()->getCollision()))
                    currentRoom->getPlayer()->takeDamage(data.damagePerAttack);
            }
            if (currentSs.getCurrentFrame() == 12) //die when it reaches the last frame of the explode animation
                die();
        }
    }
}
