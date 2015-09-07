#include "ExplosionHandler.h"
#include "SoundHandler.h"

ExplosionHandler* ExplosionHandler::theInstance = nullptr;

ExplosionHandler* ExplosionHandler::getTheInstance(){
    if (theInstance == nullptr){
        theInstance = new ExplosionHandler();
    }
    return theInstance;
}

void ExplosionHandler::update(){
    for (vector<Explosion*>::iterator i = explosions.begin(); i != explosions.end();){
        if ((*i)->Dead()){
            delete *i;
            i = explosions.erase(i);
        }
        else {
            (*i)->update();
            i++;
        }
    }
}
void ExplosionHandler::render(){
    for (int i = 0; i < explosions.size(); i++){
        explosions[i]->render();
    }
}

void ExplosionHandler::addExplosion(int x, int y, int w, int h, int time, string ID){
   Explosion* e = new Explosion;
   e->load(x,y,150,150,time,ID);
   e->setDrawWidth(w);
   e->setDrawHeight(h);
   explosions.push_back(e);
}
