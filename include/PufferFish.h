#ifndef PUFFERFISH_H
#define PUFFERFISH_H

#include "Enemy.h"
#include "GameObjectFactory.h"

class PufferFish : public Enemy {
    public:
        PufferFish();
        void update();
        void setHealth(int newHealth){
            if (newHealth < health){ // hurt
                blownUp = true;
            }
            health = newHealth;
            if (health <= 0){
                dying = true;
            }
        }

        void setBlownUp(bool b)
        { blownUp = b;};
        bool isBlownUp()
        { return blownUp; };

    private:
        bool blownUp;
};

class PufferFishCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new PufferFish();
    }
};

#endif
