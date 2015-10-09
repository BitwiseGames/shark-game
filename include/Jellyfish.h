#ifndef JELLYFISH_H
#define JELLYFISH_H

#include "Enemy.h"
#include "GameObjectFactory.h"
#include "CollisionHandler.h"
#include <iostream>
#include <cmath>

class Jellyfish : public Enemy {
    public:

        Jellyfish() {
            birthTime = SDL_GetTicks();
        };

        void setHealth(int newHealth){
            health = newHealth;
            if (health <= 0){
                dead = true;
            }
        }

        void update(){
            float timeDiff = (SDL_GetTicks() - birthTime) / 100.0f;
            position.setY(spawnY + sin(timeDiff) * Game::getTheInstance()->getDeltaTime() * 1000);
        }

        void playerCollide(){
            int py = CollisionHandler::getTheInstance()->getPlayer()->Position()->Y();
            if (py > position.Y() + BELL_HEIGHT){ // player is hitting the tentacles
                int playerHealth = CollisionHandler::getTheInstance()->getPlayer()->Health() - 1;
                CollisionHandler::getTheInstance()->getPlayer()->setHealth(playerHealth);
            }
            else { // player is hitting the bell
                int px = CollisionHandler::getTheInstance()->getPlayer()->Position()->X();
                int newX;
                if (px > position.X()){ // hitting from the right
                    newX = CollisionHandler::getTheInstance()->getPlayer()->Position()->X() + PUSH_DISTANCE;
                }
                else { // from the left
                    newX = CollisionHandler::getTheInstance()->getPlayer()->Position()->X() - PUSH_DISTANCE;
                }
                CollisionHandler::getTheInstance()->getPlayer()->setPosition(Vector2D{newX, py});
            }
        }

        void load(int x, int y, int w, int h, int frames, int cID, int _health, int speed, string tID){
            position.setX(x);
            position.setY(y);
            width = w;
            height = h;
            numFrames = frames;
            callbackID = cID;
            health = _health;
            animSpeed = speed;
            textureID = tID;
            currentFrame = 0;
            currentRow = 0;
            collisionWidth = width;
            collisionHeight = height;
            spawnY = y;
}

    private:
        int birthTime;
        int spawnY;
        const int BELL_HEIGHT = 54;
        const int PUSH_DISTANCE = 50;
        SDL_Rect bell;
        SDL_Rect tentacles;
};

class JellyfishCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Jellyfish();
    }
};

#endif
