#ifndef BULLETHANDLER_H
#define BULLETHANDLER_H

#include <vector>
#include "Bullet.h"

using namespace std;

class BulletHandler{
    public:
        static BulletHandler* getTheInstance();

        void update();
        void render();

        void addPlayerBullet(int,int,float);

    private:
        BulletHandler(){};
        static BulletHandler* theInstance;
        vector<Bullet*> playerBullets;
        const float BULLET_SPEED = 500.0f;
        const int BULLET_SIZE = 6;

        void updatePlayerBullets();
        void renderPlayerBullets();
};

#endif
