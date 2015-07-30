#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject {
    public:
        Bullet(string, int, int, int, int, float, float);
        void update();

    private:
        float speed;
};

#endif
