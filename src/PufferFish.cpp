#include "PufferFish.h"
#include <cmath>
#include "Game.h"

PufferFish::PufferFish(){
    blownUp = false;
    birthTime = SDL_GetTicks() + rand() % 100; // rand so they're not moving totally in sync
}

void PufferFish::update(){

    float timeDiff = (SDL_GetTicks() - birthTime) / 100.0f;
    position.setY(spawnY + sin(timeDiff) * Game::getTheInstance()->getDeltaTime() * 100);

    if (health < 3){ // 3 = max health
        blowUp();
    }


    if (dying){
        currentFrame = 0;
        dead = true;
    }
}

void PufferFish::playerCollide(){
    blowUp();
}

void PufferFish::load(int x, int y, int w, int h, int frames, int cID, int _health, int speed, string tID){
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

void PufferFish::blowUp(){
    if (currentFrame == numFrames-1){ // we've reached the end of the animation
        blownUp = true;
    }
    else {
        currentFrame = int(((SDL_GetTicks() / (1000 / animSpeed)) % numFrames));
    }
}
