#include "BulletHandler.h"

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
    for (int i = 0; i < playerBullets.size(); i++){
        playerBullets[i]->update();
    }
}
void BulletHandler::renderPlayerBullets(){
    for (int i = 0; i < playerBullets.size(); i++){
        playerBullets[i]->render();
    }
}

void BulletHandler::addPlayerBullet(int x, int y, float rot){
    Bullet* b = new Bullet("playerbullet", x, y, BULLET_SIZE, BULLET_SIZE, BULLET_SPEED, rot);
    playerBullets.push_back(b);
}
