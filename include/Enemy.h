#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject {
    public:
        Enemy(){ type = "Enemy"; };

        void setHealth(int newHealth){
            health = newHealth;
            if (health <= 0){
                dead = true; // will eventually need to update this so that it calls a "doDyingAnimation" function first
            }
        }

    protected:
        int viewDistance = 300;

    private:

};

#endif
