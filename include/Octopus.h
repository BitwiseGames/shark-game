#ifndef OCTOPUS_H
#define OCTOPUS_H

#include "Enemy.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "ExplosionHandler.h"
#include <cmath>

class Octopus : public Enemy {
    public:
        Octopus(){ birthTime = SDL_GetTicks() + rand() % 100; };
        void update(){
            float timeDiff = (SDL_GetTicks() - birthTime) / 100.0f;
            position.setY(spawnY + sin(timeDiff) * Game::getTheInstance()->getDeltaTime() * 100);
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

        void setHealth(int newHealth){
            health = newHealth;
            if (health <= 0){
                dead = true;
            }
        }

        void playerCollide(){
            ExplosionHandler::getTheInstance()->addInkblot(position.X(), position.Y(), 300, 300, 600, false);
        }

    private:
    int spawnY;
    int birthTime;
};

class OctopusCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Octopus();
    }
};

#endif
