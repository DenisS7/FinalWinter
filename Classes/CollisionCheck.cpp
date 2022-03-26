#include "CollisionCheck.h"
#include "newmath.h"
#include <vector>
#include "EnemyBase.h"
#include "Campfire.h"

#include "../surface.h"


int CollisionCheck::isOverlapping(CollisionComponent actorCollision, GameSpace::vec2 actorPosition,
                                  Map::Room* currentRoom, int damage, int damageType, GameSpace::Surface* screen)
{
    int collisionType = 0;
    bool isEnemy = false;


    const int radius = 1;

    newmath::ivec2 roomPos;

    roomPos.x = static_cast<int>(actorPosition.x) / currentRoom->tilesize + 1;
    roomPos.y = static_cast<int>(actorPosition.y) / currentRoom->tilesize + 1;

    std::vector<Character::EnemyBase*> enemiesHit;

    newmath::ivec2 startPos;

    startPos.x = newmath::clamp(roomPos.x, radius, currentRoom->getSize().x - radius - 1);
    startPos.y = newmath::clamp(roomPos.y, radius, currentRoom->getSize().y - radius - 1);


    if (damageType != player)
    {
        if (areColliding(actorCollision, currentRoom->getPlayer()->getCollision()))
        {
            currentRoom->getPlayer()->takeDamage(damage);
            return collide;
        }
    }

    const int gift = 0, potion = 1;
    for (int i = 0; i < currentRoom->getItems().size(); i++)
        if (areColliding(actorCollision, currentRoom->getItems()[i]->getCollision()))
        {
            if (currentRoom->getItems()[i]->getType() == gift)
            {
                collisionType = collide;
                currentRoom->getItems()[i]->takeDamage(damage);
            }
        }

    for (int y = startPos.y - radius; y <= startPos.y + radius; y++)
    {
        for (int x = startPos.x - radius; x <= startPos.x + radius; x++)
        {
            const int tilepos = x + y * currentRoom->getSize().x;
            if (currentRoom->getTile(tilepos).colidable)
            {
                CollisionComponent tileCol;
                tileCol.collisionBox = newmath::make_Rect(x * 32, y * 32, 32, 32);
                if (areColliding(actorCollision, tileCol))
                    collisionType = currentRoom->getTile(tilepos).type;
            }

            if (!currentRoom->getTile(tilepos).enemiesOnTile.empty() && damageType == 5)
            {
                for (int i = 0; i < currentRoom->getTile(tilepos).enemiesOnTile.size(); i++)
                    if (areColliding(actorCollision, currentRoom->getTile(tilepos).enemiesOnTile[i]->getData().col) && !
                        std::count(enemiesHit.begin(), enemiesHit.end(),
                                   currentRoom->getTile(tilepos).enemiesOnTile[i]))
                    {
                        currentRoom->getTile(tilepos).enemiesOnTile[i]->takeDamage(damage);
                        enemiesHit.push_back(currentRoom->getTile(tilepos).enemiesOnTile[i]);
                        isEnemy = true;
                    }
            }
        }
    }

    if (isEnemy)
        return enemy;
    return collisionType;

    return 0;
}

int CollisionCheck::isPlayerOverlapping(Character::Player* player, Map::Room* currentRoom)
{
    bool isPortal = false;
    int collisionType = 0;

    const int nonCollide = 0;
    const int collide = 1;
    const int portalInactive = 2;
    const int portalActive = 3;

    const int gift = 0, potion = 1, campfire = 2;
    const int radius = 3;

    newmath::ivec2 roomPos;

    roomPos.x = static_cast<int>(player->getLocation().x) / currentRoom->tilesize + 1;
    roomPos.y = static_cast<int>(player->getLocation().y) / currentRoom->tilesize + 1;

    std::vector<int> enemyTiles;

    newmath::ivec2 startPos;

    bool isEnemy = false;

    startPos.x = newmath::clamp(roomPos.x, radius, currentRoom->getSize().x - radius - 1);
    startPos.y = newmath::clamp(roomPos.y, radius, currentRoom->getSize().y - radius - 1);

    for (int y = startPos.y - radius; y <= startPos.y + radius; y++)
    {
        for (int x = startPos.x - radius; x <= startPos.x + radius; x++)
        {
            const int tilepos = x + y * currentRoom->getSize().x;
            if (currentRoom->getTile(tilepos).colidable)
            {
                CollisionComponent actor2Col;
                actor2Col.collisionBox = newmath::make_Rect(x * 32, y * 32, 32, 32);

                if (areColliding(player->getCollision(), actor2Col))
                    collisionType = currentRoom->getTile(tilepos).type;

                if (collisionType == portalActive)
                    isPortal = true;
            }
            if (!currentRoom->getTile(tilepos).enemiesOnTile.empty())
            {
                for (int i = 0; i < currentRoom->getTile(tilepos).enemiesOnTile.size(); i++)
                    if (areColliding(player->getCollision(),
                                     currentRoom->getTile(tilepos).enemiesOnTile[i]->getData().col))
                    {
                        if (currentRoom->getTile(tilepos).enemiesOnTile[i]->getData().type == 1)
                            isEnemy = true;
                    }
            }
        }
    }

    for (int i = 0; i < currentRoom->getItems().size(); i++)
    {
        if (areColliding(player->getCollision(), currentRoom->getItems()[i]->getCollision()))
        {
            if (currentRoom->getItems()[i]->getType() == gift || currentRoom->getItems()[i]->getType() == campfire)
                collisionType = collide;
            else if (currentRoom->getItems()[i]->getType() == potion)
                currentRoom->getItems()[i]->use();
        }
    }


    /*if (areEnemies)
    {
        int damageTaken = 0;
        for (int i = 0; i < enemyTiles.size(); i++)
        {
            newmath::ivec2 playerCentrePos;
            playerCentrePos.x = player->loc.x + 32;
            playerCentrePos.y = player->loc.y + 32;
            for (int j = 0; j < currentRoom->tiles[enemyTiles[i]].enemiesOnTile.size(); j++)
                if (checkEnemyCollision(player->collisionBox, currentRoom->tiles[enemyTiles[i]].enemiesOnTile[j]->collisionBox))
                    damageTaken += currentRoom->tiles[enemyTiles[i]].enemiesOnTile[j]->damageOnCollision;
        }
    }*/

    if (isPortal)
        return portalActive;
    if (isEnemy)
        collisionType = 1;
    return collisionType;
}

void CollisionCheck::campfireHeal(Character::Player* player, Map::Room* currentRoom)
{
    const int campfire = 2;
    if (currentRoom->getItems().size())
    {
        if (currentRoom->getItems()[0]->getType() == campfire)
        {
            auto campfireP = dynamic_cast<Item::Campfire*>(currentRoom->getItems()[0]);
            if (player->getHealth() < 70 && areColliding(player->getCollision(), campfireP->getHealBox()) && campfireP->
                heal())
            {
                player->takeDamage(-campfireP->getHealAmount());
                if (player->getHealth() > 70)
                    player->takeDamage(player->getHealth() - 70);
            }
        }
    }
}

bool CollisionCheck::areColliding(CollisionComponent actor1, CollisionComponent actor2)
{
    if (actor1.collisionBox.x < actor2.collisionBox.x + actor2.collisionBox.width &&
        actor1.collisionBox.x + actor1.collisionBox.width > actor2.collisionBox.x &&
        actor1.collisionBox.y < actor2.collisionBox.y + actor2.collisionBox.height &&
        actor1.collisionBox.y + actor1.collisionBox.height > actor2.collisionBox.y)
    {
        return true;
    }
    return false;
}
