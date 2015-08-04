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

        // horizontal hit tests
        if (py + ph > ey && py < ey + eh){
            if (px + pw >= ex && px <= ex){
                player->setPosition({object->Position()->X() - pw, player->Position()->Y()});
            }
            else if (px <= ex + ew && px + pw >= ex){
                player->setPosition({object->Position()->X() + ew, player->Position()->Y()});
            }
        }
        //vertical hit tests
        else if (px <= ex + ew && px + pw >= ex){
            if (py + ph >= ey && py <= ey){
                player->setPosition({player->Position()->X(), object->Position()->Y() - ph});
            }
            else if (py <= ey + eh && py + ph >= ey + eh){
                player->setPosition({player->Position()->X(), object->Position()->Y() + eh});
            }
        }
    }
}



