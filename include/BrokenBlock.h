#ifndef BROKENBLOCK_H
#define BROKENBLOCK_H

#include "Enemy.h"
#include "GameObjectFactory.h"

class BrokenBlock : public Enemy{
    public:
        BrokenBlock(){};
        virtual ~BrokenBlock(){};
        void setHealth(int newHealth){ // no fancy dying animation or anything, just want it to go away
            if (newHealth < health){ // got hurt
                currentFrame++;
            }
            health = newHealth;
            if (health <= 0){
                dead = true;
            }
        }

};

class BrokenBlockCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new BrokenBlock();
    }
};

#endif
