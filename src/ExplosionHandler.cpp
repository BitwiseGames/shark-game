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

void ExplosionHandler::addInkblot(int x, int y, int w, int h, int time, string ID){
   Inkblot* i = new Inkblot;
   i->load(x,y,250,250,time,ID);
   i->setDrawWidth(w);
   i->setDrawHeight(h);
   explosions.push_back(i);
}
