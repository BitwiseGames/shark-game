#ifndef MANTARAY_H
#define MANTARAY_H

#include "Enemy.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "BulletHandler.h"
#include "CollisionHandler.h"
#include "Player.h"
#include "Tests.h"

class MantaRay : public Enemy {
    public:

        MantaRay(){
            speed = 50.0f;
            dx = -1;
            flip = SDL_FLIP_NONE;
            viewDistance = 100;
            attackTimer = 60; // one attack per second
            maxAttackTime = 60;
        };

        void update(){

            attackTimer--;

            if (state == "attack"){
                if (attackTimer <= 0){
                    attackTimer = maxAttackTime;
                    int px = CollisionHandler::getTheInstance()->getPlayer()->Position()->X();
                    int py = CollisionHandler::getTheInstance()->getPlayer()->Position()->Y();
                    float angle = Tests::angleBetween(position.X(), position.Y(), px, py);
                    BulletHandler::getTheInstance()->addEnemyBullet(position.X() + width / 2, position.Y() + height / 2, angle, "manta_ray_stinger");
                    if (Tests::distanceBetween(px, py, position.X(), position.Y()) > viewDistance){ // player has moved away
                        state = "idle";
                        currentFrame = 0;
                    }
                }
            }

            else if (state == "idle"){
                float newX = position.X() - (speed * Game::getTheInstance()->getDeltaTime() * dx);
                position.setX(newX);

                if (tileCollisions(position)){

                    dx *= -1;

                    if (flip == SDL_FLIP_HORIZONTAL)
                        flip = SDL_FLIP_NONE;
                    else
                        flip = SDL_FLIP_HORIZONTAL;
                }

                int px = CollisionHandler::getTheInstance()->getPlayer()->Position()->X();
                int py = CollisionHandler::getTheInstance()->getPlayer()->Position()->Y();
                if (Tests::distanceBetween(px, py, position.X(), position.Y()) <= viewDistance){
                    state = "attack";
                    currentFrame = 1;
                }
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
