#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject {
    public:
        void update();
        void render();
        void load(int, int, int, int, float, float, string, int = -1);
        void setHealth(int newHealth){
            health = newHealth;
            if (health <= 0){
                dead = true;
            }
        }

        bool tileCollisions(Vector2D); // have to overwrite it b/c it's slightly different

        void setDrawWidth(int dw)
        { drawWidth = dw; };
        void setDrawHeight(int dh)
        { drawHeight = dh; };

    private:
        int drawWidth;
        int drawHeight;
        int maxTime = 0; // some bullets will stay alive for a time period, instead of until they hit something
        float speed;
};

#endif
