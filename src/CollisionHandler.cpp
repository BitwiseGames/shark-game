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


        //vertical hit tests
        if (player->Position()->X() < object->Position()->X() + object->CollisionWidth() && player->Position()->X() + player->CollisionWidth() > object->Position()->X()){
            //hitting the top
            if ( player->Position()->Y() + player->CollisionHeight() > object->Position()->Y() && player->Position()->Y() < object->Position()->Y()){
                player->setPosition({player->Position()->X(), object->Position()->Y() - player->CollisionHeight()});
            }
            //hitting the bottom
            else if (player->Position()->Y() < object->Position()->Y() + object->CollisionHeight() && player->Position()->Y() + player->CollisionHeight() > object->Position()->Y() + object->CollisionHeight()){
                player->setPosition({player->Position()->X(), object->Position()->Y() + object->CollisionHeight()});
            }
        }
        // horizontal hit tests
        if (player->Position()->Y() < object->Position()->Y() + object->CollisionHeight() && player->Position()->Y() + player->CollisionHeight() > object->Position()->Y()){
            //hitting the left side
            if ( player->Position()->X() + object->CollisionWidth() > object->Position()->X() && player->Position()->X() < object->Position()->X()){
                player->setPosition({object->Position()->X() - player->Width(), player->Position()->Y()});
            }
            //hitting the right side
            else if ( player->Position()->X() < object->Position()->X() + object->CollisionWidth() && player->Position()->X() + player->CollisionWidth() > object->Position()->X()){
                player->setPosition({object->Position()->X() + object->CollisionWidth(), player->Position()->Y()});
            }
        }
    }
}



