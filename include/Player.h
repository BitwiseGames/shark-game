#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "TextureHandler.h"
#include "GameOverState.h"
#include "Game.h"

class Player : public GameObject {
    public:
        Player();
        void update();
        void setSpeed(int s)
        { speed = s;};
        void setHealth(int h){
            health = h;
            if (health <= 0){
                Game::getTheInstance()->getStateHandler()->changeState(new GameOverState);
            }
        }

    private:
        float speed;
        bool spaceKeyDown; // this is sort of hacky but it's easier than going into the inputhandler and dealing with a bunch of shit
        const int MIN_SPEED = 200;
        const int SPEED_CHANGER = 2;
        const int MAX_SPEEDS = 4;
        string currentWeapon;
        int laserCharge;
        int shotCoolDown;
        int maxCoolDown;

        void shoot();
};

class PlayerCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Player();
    }
};

#endif
