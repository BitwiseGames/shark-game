#ifndef MANTARAY_H
#define MANTARAY_H

#include "Enemy.h"
#include "Game.h"
#include "GameObjectFactory.h"

class MantaRay : public Enemy {
    public:

        MantaRay(){
            speed = 500.0f;
            dx = -1;
            flip = SDL_FLIP_NONE;
        };

        void update(){
            float newX = position.X() - (speed * Game::getTheInstance()->getDeltaTime() * dx);
            position.setX(newX);

            if (tileCollisions(position)){

                dx *= -1;

                if (flip == SDL_FLIP_HORIZONTAL)
                    flip = SDL_FLIP_NONE;
                else
                    flip = SDL_FLIP_HORIZONTAL;
            }

        }

    private:
        int dx;
        float speed;
};

class MantaRayCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new MantaRay();
    }
};

#endif
