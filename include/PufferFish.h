#ifndef PUFFERFISH_H
#define PUFFERFISH_H

#include "Enemy.h"
#include "GameObjectFactory.h"

class PufferFish : public Enemy {
    public:
        PufferFish();
        void update();
        void load(int, int, int, int, int, int, int, int, string); // have to overload it b/c it's slightly different
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
        int spawnY;
        int birthTime;
        bool blownUp;
};

class PufferFishCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new PufferFish();
    }
};

#endif
