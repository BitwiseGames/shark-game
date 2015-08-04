#include "CollisionHandler.h"
#include "BulletHandler.h"
#include "Camera.h"
#include "Player.h"
#include "Tests.h"

CollisionHandler* CollisionHandler::theInstance = nullptr;

CollisionHandler* CollisionHandler::getTheInstance(){
    if (theInstance == nullptr){
        theInstance = new CollisionHandler();
    }
    return theInstance;
}

void CollisionHandler::update(Player* player, vector<GameObject*> gameObjects){
    PlayerBulletEnemyCollisions(gameObjects);
    playerEnemyCollisions(player, gameObjects);
}

void CollisionHandler::PlayerBulletEnemyCollisions(vector<GameObject*> gameObjects){
    for (int i = 0; i < gameObjects.size(); i++){
        GameObject* object = gameObjects[i];
        if (object->Type() != "Enemy"){
            continue;
        }
        for (int j = 0; j < BulletHandler::getTheInstance()->getPlayerBullets().size(); j++){
            Bullet* b = BulletHandler::getTheInstance()->getPlayerBullets()[j];
            int ex = object->Position()->X() - Camera::getTheInstance()->getPosition().X();
            int ey = object->Position()->Y() - Camera::getTheInstance()->getPosition().Y();
            int ew = object->Width();
            int eh = object->Height();
            int bx = b->Position()->X() - Camera::getTheInstance()->getPosition().X();
            int by = b->Position()->Y() - Camera::getTheInstance()->getPosition().Y();
            int bw = b->Width();
            int bh = b->Height();
            if (Tests::AABB(ex, ey, ew, eh, bx, by, bw, bh)){
                b->setHealth(0);
                int curHealth = object->Health();
                curHealth--;
                object->setHealth(curHealth);
            }
        }
    }
}

void CollisionHandler::playerEnemyCollisions(Player* player, vector<GameObject*> gameObjects){
    for (int i = 0; i < gameObjects.size(); i++){
        GameObject* object = gameObjects[i];
        if (object->Type() != "Enemy"){
            continue;
        }

        int ex = object->Position()->X() - Camera::getTheInstance()->getPosition().X();
        int ey = object->Position()->Y() - Camera::getTheInstance()->getPosition().Y();
        int ew = object->Width();
        int eh = object->Height();
        int px = player->Position()->X() - Camera::getTheInstance()->getPosition().X();
        int py = player->Position()->Y() - Camera::getTheInstance()->getPosition().Y();
        int pw = player->Width();
        int ph = player->Height();

        // detect collision
        // https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
        if (ex < px + pw &&
           ex + ew > px &&
           ey < py + ph &&
           eh + ey > py) {
            // collision detected
        } else {
            // collision not detected
        }
    }
}



