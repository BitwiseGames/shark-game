#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.h"

class Explosion : public GameObject {
    public:
        Explosion(){};
        void update();
        void render();
        void load(int, int, int, int, int, string);

        void setDrawWidth(int dw)
        { drawWidth = dw; };
        void setDrawHeight(int dh)
        { drawHeight = dh; };

    private:
        int drawWidth; // these variables are necessary to resize the sprite
        int drawHeight;
};

#endif
