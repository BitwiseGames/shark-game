#ifndef PISTOLSHRIMP_H
#define PISTOLSHRIMP_H

#include "Enemy.h"
#include "GameObjectFactory.h"

class PistolShrimp : public Enemy{
    public:
        PistolShrimp();
        void update();
        void setHealth(int newHealth){
            health = newHealth;
            if (health <= 0){
                dead = true;
            }
        }

    private:
        int shotCoolDown;
        int maxCoolDown;
};

class PistolShrimpCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new PistolShrimp();
    }
};

#endif
