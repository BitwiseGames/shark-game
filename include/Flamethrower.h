#ifndef FLAMETHROWER_H
#define FLAMETHROWER_H

#include "Bullet.h"

class Flamethrower : public Bullet {
    public:
        void load(int, int, int, int, int, float, string);

        void update();
    private:
        int time;

};

#endif
