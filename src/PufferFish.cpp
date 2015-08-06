#include "PufferFish.h"

PufferFish::PufferFish(){
    blownUp = false;
}

void PufferFish::update(){
    if (health < 3){ // 3 = max health
        if (currentFrame == numFrames-1){ // we've reached the end of the animation
            blownUp = true;
        }
        else {
            currentFrame = int(((SDL_GetTicks() / (1000 / animSpeed)) % numFrames));
        }
    }


    if (dying){
        currentFrame = 0;
        dead = true;
    }
}
