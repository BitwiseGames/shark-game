#ifndef ELECTRICEEL_H
#define ELECTRICEEL_H

#include "Enemy.h"
#include "GameObjectFactory.h"

class ElectricEel : public Enemy {
    public:
        ElectricEel();
        void update();

    private:
        int speed;
};

class ElectricEelCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new ElectricEel();
    }
};

#endif
