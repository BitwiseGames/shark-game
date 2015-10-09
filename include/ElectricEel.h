#ifndef ELECTRICEEL_H
#define ELECTRICEEL_H

#include "Enemy.h"
#include "GameObjectFactory.h"
#include "CollisionHandler.h"
#include "Player.h"

class ElectricEel : public Enemy {
    public:
        ElectricEel();
        void update();

        void playerCollide(){
            int playerHealth = CollisionHandler::getTheInstance()->getPlayer()->Health() - 1;
            CollisionHandler::getTheInstance()->getPlayer()->setHealth(playerHealth);
        }

    private:
        int speed;
};

class ElectricEelCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new ElectricEel();
    }
};

#endif
