#ifndef GOLDENEGG_H
#define GOLDENEGG_H

#include "GameObjectFactory.h"

class GoldenEgg : public GameObject {
    public:
        GoldenEgg() {}
        void update(){
            currentFrame = int(((SDL_GetTicks() / (1000 / animSpeed)) % numFrames));
        }

};

class GoldenEggCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new GoldenEgg();
    }
};


#endif
