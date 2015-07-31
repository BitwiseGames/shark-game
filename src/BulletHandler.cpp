#include "BulletHandler.h"
#include "SoundHandler.h"

BulletHandler* BulletHandler::theInstance = nullptr;

BulletHandler* BulletHandler::getTheInstance(){
    if (theInstance == nullptr){
        theInstance = new BulletHandler();
    }
    return theInstance;
}

void BulletHandler::update(){
    updatePlayerBullets();
}
void BulletHandler::render(){
    renderPlayerBullets();
}

void BulletHandler::updatePlayerBullets(){
    for (vector<Bullet*>::iterator i = playerBullets.begin(); i != playerBullets.end();){
        if ((*i)->Dead()){
            delete *i;
            i = playerBullets.erase(i);
        }
        else {
            (*i)->update();
            i++;
        }
    }
}
void BulletHandler::renderPlayerBullets(){
    for (int i = 0; i < playerBullets.size(); i++){
        playerBullets[i]->render();
    }
}

void BulletHandler::addPlayerBullet(int x, int y, float rot){
    SoundHandler::getTheInstance()->playSound("gunshot", 0);
    Bullet* b = new Bullet();
    b->load(x, y, BULLET_SIZE, BULLET_SIZE, BULLET_SPEED, rot, "playerbullet");
    b->setCollisionLayers(collisionLayers);
    playerBullets.push_back(b);
}
