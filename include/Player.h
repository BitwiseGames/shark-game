#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "GameObjectFactory.h"

class Player : public GameObject {

};

class PlayerCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Player();
    }
};

#endif
