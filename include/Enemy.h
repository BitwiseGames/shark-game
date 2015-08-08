#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject {
    public:
        Enemy(){ type = "Enemy"; };

    protected:
        int viewDistance = 300;

    private:

};

#endif
