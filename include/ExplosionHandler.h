#ifndef EXPLOSIONHANDLER_H
#define EXPLOSIONHANDLER_H

#include <vector>
#include "Explosion.h"
#include "Inkblot.h"

using namespace std;

class ExplosionHandler{
    public:
        static ExplosionHandler* getTheInstance();

        void update();
        void render();

        void addExplosion(int,int,int,int,int,string);
        void addInkblot(int,int,int,int,int,string);

        vector<Explosion*> getExplosions()
        { return explosions; };

    private:
        ExplosionHandler(){};
        static ExplosionHandler* theInstance;
        vector<Explosion*> explosions;

        void updateExplosions();
        void renderExplosions();
};

#endif
