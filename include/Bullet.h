#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject {
    public:
        void update();
        void render();
        void load(int, int, int, int, float, float, string);
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
        float speed;
};

#endif
