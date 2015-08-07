#ifndef JELLYFISH_H
#define JELLYFISH_H

#include "Enemy.h"
#include "GameObjectFactory.h"
#include <cmath>

class Jellyfish : public Enemy {
    public:
        Jellyfish() { birthTime = SDL_GetTicks();};
        void update(){
            float timeDiff = (SDL_GetTicks() - birthTime) / 100.0f;
            position.setY(spawnY + sin(timeDiff) * Game::getTheInstance()->getDeltaTime() * 1000);
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
};

class JellyfishCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Jellyfish();
    }
};

#endif
