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

        void setCollisionLayers(vector<TileLayer*>* cl)
        { collisionLayers = cl; };

        void addPlayerBullet(int,int,float,string, int = 0);
        void addEnemyBullet(int,int,float,string);

        vector<Bullet*> getPlayerBullets()
        { return playerBullets; };

    private:
        BulletHandler(){};
        static BulletHandler* theInstance;
        vector<TileLayer*>* collisionLayers;
        vector<Bullet*> playerBullets;
        vector<Bullet*> enemyBullets;
        const float BULLET_SPEED = 2000.0f;
        const float MISSILE_SPEED = 3000.0f;
        const float CANNONBALL_SPEED = 1500.0f;
        const float FIST_SPEED = 2500.0f;
        const int BULLET_SIZE = 6;
        const int MISSILE_WIDTH = 32;
        const int MISSILE_HEIGHT = 16;
        const int CANNONBALL_SIZE = 32;
        const int FIST_SIZE = 16;

        void updatePlayerBullets();
        void renderPlayerBullets();
        void updateEnemyBullets();
        void renderEnemyBullets();
};

#endif
