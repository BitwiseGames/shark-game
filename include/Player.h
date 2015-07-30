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
        void render();

    private:
        float speed;
};

class PlayerCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Player();
    }
};

#endif
