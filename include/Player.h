#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "TextureHandler.h"
#include "Game.h"

class Player : public GameObject {
    public:
        Player();
        void update();
        //void render();

    private:
        float speed;
        bool spaceKeyDown; // this is sort of hacky but it's easier than going into the inputhandler and dealing with a bunch of shit
        const int MIN_SPEED = 200;
        const int SPEED_CHANGER = 2;
        const int MAX_SPEEDS = 4;
};

class PlayerCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Player();
    }
};

#endif
