#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject {
    public:
        Bullet(){};
        void update();
        void load(int, int, int, int, float, float, string);
        void setHealth(int newHealth){
            health = newHealth;
            if (health <= 0){
                dead = true;
            }
        }

    private:
        float speed;
};

#endif
